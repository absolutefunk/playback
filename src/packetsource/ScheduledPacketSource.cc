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

#include "ScheduledPacketSource.h"

void ScheduledPacketSource::scheduleToDispatch(cMessage *pktData) {
    if (scheduledPktDataTimer->isScheduled()) {
        EV << "[ScheduledPacketSource]: cannot schedule packet: packet already scheduled\n";
        // delete the pktData
        delete pktData;

        return;
    }

    // The getTimeStamp method is used to retrieve the timestamp of the pktData.  This corresponds to the absolute
    // time at which the packet needs to be sent.
    if (simTime() > pktData->getTimestamp()) {
        EV << "[ScheduledPacketSource]: cannot schedule packet at a time in the past.\n";
        // delete the pktData
        delete pktData;

        return;
    }

    // Schedule the pktdata to be processed at the correct time.
    scheduledPktDataTimer->setContextPointer(pktData);
    scheduleAt(pktData->getTimestamp(), scheduledPktDataTimer);

    emit(scheduledPkSignal, 1);
}

void ScheduledPacketSource::initialize() {
    scheduledPktDataTimer = new cMessage("ScheduledPacketSourceTimer");

    // register signals
    scheduledPkSignal = registerSignal("scheduledPk");
    dispatchedPkSignal = registerSignal("dispatchedPk");

    WATCH(subscriberCount);
}

void ScheduledPacketSource::handleMessage(cMessage *msg) {
    // should only handle self messages
    if (msg == scheduledPktDataTimer) {
        // dispatch the pktData to all injectors subscribed to this packet source
        // We already know what the contextPointer is, so this is safe
        emit(dispatchedPkSignal, dispatch(static_cast<cMessage *>(msg->getContextPointer())));

        scheduleNext();  // polymorphic call

        return;
    }

    delete msg;  // not for us, delete
}

void ScheduledPacketSource::finish() {
    // also need to delete the context pointer
    if (scheduledPktDataTimer->isScheduled()) {
        // If the timer isn't scheduled, then there isn't anything the context pointer is pointing too...
        delete static_cast<cMessage *>(scheduledPktDataTimer->getContextPointer());
    }

    cancelAndDelete(scheduledPktDataTimer);
}
