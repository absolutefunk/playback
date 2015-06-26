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

#ifndef PACKETINJECTOR_H_
#define PACKETINJECTOR_H_

#include <map>
#include <string>

#include <omnetpp.h>

class PacketSource;

class PacketInjector : public cSimpleModule {
public:
    // callback for the PacketSource
    virtual void receivePacketData(cMessage *pktData) = 0;
    virtual std::size_t getSubscribedCount() { return subscriptions.size(); }

protected:
    unsigned int subscribedCount = 0;  // WATCH variable
    std::map<std::string, PacketSource *> subscriptions;  // list of our current subscriptions

    virtual void subscribeToPacketSource(const char *packetSourceName);
    virtual void unsubscribeFromPacketSource(const char *packetSourceName);
};

#endif /* PACKETINJECTOR_H_ */
