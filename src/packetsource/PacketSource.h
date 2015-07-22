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

#ifndef PACKETSOURCE_H_
#define PACKETSOURCE_H_

#include <set>

#include <omnetpp.h>

class PacketInjector;

// Base class for all packet sources.  This handles stuff like subscriptions to injectors.
// A packet source handles parsing of one packet type.  Multiple packet types from the same data should be handled
// by different packet sources, or by different instances of the same packet source (with say configuration changes).
// This allows for the subscriptions to be simpler.
class PacketSource {
public:
    virtual ~PacketSource() = default;

    // Adds an injector to the list of injectors receiving packets from this packet source
    virtual bool subscribe(PacketInjector *injector);

    // Removes an injector from the list of injectors receiving packets from this packet source
    virtual bool unsubscribe(PacketInjector *injector);

    virtual std::size_t getSubscriberCount() { return injectors.size(); }
    virtual bool hasSubscribers() { return ((injectors.size() > 0) ? true : false); }

protected:
    std::set<PacketInjector *> injectors;
    unsigned int subscriberCount  = 0;  // WATCH variable

    // Dispatches a new packet (data for the injector to generate a packet from) to all the injectors subscribed
    // Returns the number of injectors the input pktData was dispatched to.
    virtual int dispatch(cMessage *pktData);
};

#endif /* PACKETSOURCE_H_ */
