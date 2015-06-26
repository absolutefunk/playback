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

#ifndef MULTISCHEDULEDPACKETSOURCE_H_
#define MULTISCHEDULEDPACKETSOURCE_H_

#include <set>

#include "PacketSource.h"

// Base class for PacketSources which need to schedule multiple packets concurrently, such as bulk loading
// PacketSources.
class MultiScheduledPacketSource: public PacketSource, public cSimpleModule {
public:
    virtual std::size_t getScheduledCount() { return timerSet.size(); }

protected:
    virtual void scheduleToDispatch(cMessage *pktData);

    virtual void postDispatch() { return; }  // If post-dispatch processing is needed, override this in a subclass

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

private:
    std::set<cMessage *> timerSet;  // Used to store timers while they are in the event queue

    // statistics
    simsignal_t scheduledPkSignal;
    simsignal_t dispatchedPkSignal;
    simsignal_t setSizeSignal;
};

#endif /* MULTISCHEDULEDPACKETSOURCE_H_ */
