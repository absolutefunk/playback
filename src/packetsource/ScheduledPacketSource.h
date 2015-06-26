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

#ifndef SCHEDULEDPACKETSOURCE_H_
#define SCHEDULEDPACKETSOURCE_H_

#include "PacketSource.h"

// Base class for packet sources which schedule new packet data through the event queue (should be most of them).
// While this is a simple module, it is not meant to be instantiated on its own (hence why there is no Define_Module()
// or a NED definition for this class).
class ScheduledPacketSource: public PacketSource, public cSimpleModule {
protected:
    virtual void scheduleToDispatch(cMessage *pktData);
    virtual void scheduleNext() = 0;  // this is called after a current packet has been dispatched

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

private:
    cMessage *scheduledPktDataTimer;  // scheduling selfMsg

    // statistics
    simsignal_t scheduledPkSignal;
    simsignal_t dispatchedPkSignal;
};

#endif /* SCHEDULEDPACKETSOURCE_H_ */
