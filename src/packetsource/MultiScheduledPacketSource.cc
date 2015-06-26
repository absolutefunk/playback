//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// CMU MEWS Group, 2015
// @author Brian Ricks
//

#include "MultiScheduledPacketSource.h"

// schedule the input pktData
void MultiScheduledPacketSource::scheduleToDispatch(cMessage *pktData) {
    // The getTimeStamp method is used to retrieve the timestamp of the pktData.  This corresponds to the absolute
    // time at which the packet needs to be sent.
    if (simTime() > pktData->getTimestamp()) {
        EV << "[MultiScheduledPacketSource]: cannot schedule packet at a time in the past.\n";
        delete pktData;

        return;
    }

    cMessage *selfMsg = new cMessage("MultiScheduledPacketSource");
    selfMsg->setContextPointer(pktData);
    timerSet.insert(selfMsg);
    scheduleAt(pktData->getTimestamp(), selfMsg);

    emit(scheduledPkSignal, 1);
    emit(setSizeSignal, getScheduledCount());
}

void MultiScheduledPacketSource::initialize() {
    // register signals
    scheduledPkSignal = registerSignal("scheduledPk");
    dispatchedPkSignal = registerSignal("dispatchedPk");
    setSizeSignal = registerSignal("setSize");

    WATCH(subscriberCount);
}

void MultiScheduledPacketSource::handleMessage(cMessage *msg) {
    if (timerSet.find(msg) != timerSet.end()) {
        // This is a selfMsg which belongs to us
        // dispatch the pktData to all injectors subscribed to this packet source
        // We already know what the contextPointer is, so this is safe
        emit(dispatchedPkSignal, dispatch(static_cast<cMessage *>(msg->getContextPointer())));
        timerSet.erase(msg);
        delete msg;  // selfMsgs not persistent

        emit(setSizeSignal, getScheduledCount());

        postDispatch();

        return;
    }

    delete msg;  // not for us
}

void MultiScheduledPacketSource::finish() {
    // delete any currently scheduled selfMsgs
    for(std::set<cMessage *>::iterator it = timerSet.begin(); it != timerSet.end(); ++it) {
        // Note that we also need to delete the pktData pointed to by the context pointer
        delete static_cast<cMessage *>((*it)->getContextPointer());
        cancelAndDelete(*it);
    }
}

