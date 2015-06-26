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

#include "PacketSource.h"

#include "PacketInjector.h"

// returns true if the PacketInjector is subscribed, false otherwise
bool PacketSource::subscribe(PacketInjector *injector) {
    std::size_t prevSubCount = getSubscriberCount();
    injectors.insert(injector);

    // if the subscription was added, then the subscriber count should increase by one
    if (prevSubCount < getSubscriberCount()) {
        ++subscriberCount;
        return true;
    }
    else if (injectors.find(injector) != injectors.end()) {
        // if the same injector tries to subscribe multiple times
        return true;
    }

    return false;  // injector is NOT subscribed
}

// returns true if the PacketInjector is unsubscribed, false otherwise
bool PacketSource::unsubscribe(PacketInjector *injector)  {
    std::size_t prevSubCount = getSubscriberCount();
    injectors.erase(injector);

    // if the subscription was removed, then the subscriber count should decrease by one
    if (prevSubCount > getSubscriberCount()) {
        --subscriberCount;
        return true;
    }
    else if (injectors.find(injector) == injectors.end()) {
        // injector was probably removed earlier, or never was subscribed to this
        return true;
    }

    return false;  // injector is NOT unsubscribed
}

int PacketSource::dispatch(cMessage *pktData) {
    int dispatchCount = 0;

    // Dispatch the pktData to all subscribers
    for(std::set<PacketInjector *>::iterator it = injectors.begin(); it != injectors.end(); ++it) {
        // Because the pktData is a pointer, we need to make sure that ownership is not going to be messy.  Therefore,
        // each injector will get a separate copy of the pktData, which they will be responsible for.
        (*it)->receivePacketData(pktData->dup());
        ++dispatchCount;
    }

    delete pktData;  // the original copy we own (technically a derived class owns it, but the end of the road is here)

    return dispatchCount;
}
