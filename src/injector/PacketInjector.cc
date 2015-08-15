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

#include <string>
#include <utility>

#include "PacketInjector.h"

#include "PacketSource.h"

void PacketInjector::subscribeToPacketSource(cPar &packetSourceName) {
    subscribeToPacketSource(packetSourceName.stringValue());
}

void PacketInjector::subscribeToPacketSource(const char *packetSourceName) {

    PacketSource *pktSource = NULL;

    // prepend the path search criteria to the packetSourceName
    //TODO: Maybe follow the inet standard and put the path directly into the NED instead of
    // concatenating it here
    std::string modPath("^.");
    modPath.append(packetSourceName);

    try {
        pktSource = dynamic_cast<PacketSource *>(getModuleByPath(modPath.c_str()));
    }
    catch(cRuntimeError &ex) {
        error(ex.what());
    }

    if (!pktSource) {
        std::string errMsg = std::string("PacketSource: ") + packetSourceName +
                " not found when attempting to subscribe";
        error(errMsg.c_str());
    }

    if (!pktSource->subscribe(this)) {
        std::string errMsg = std::string("PacketSource: ") + packetSourceName +
                " returned false when attempting to subscribe";
        error(errMsg.c_str());
    }

    subscriptions.insert(std::pair<std::string, PacketSource *>(std::string(packetSourceName), pktSource));
    subscribedCount = getSubscribedCount();
}

void PacketInjector::unsubscribeFromPacketSource(cPar &packetSourceName) {
    unsubscribeFromPacketSource(packetSourceName.stringValue());
}

void PacketInjector::unsubscribeFromPacketSource(const char *packetSourceName) {

    if (subscriptions.find(std::string(packetSourceName)) == subscriptions.end()) {
        // we either already unsubscribed, or was never subscribed in the first place
        EV << "[PacketInjector]: PacketSource: " << packetSourceName <<
                " when attempting to unsubscribe, does not have a subscription record.  We may have already unsubscribed.\n";
        return;
    }

    if (!(subscriptions.at(std::string(packetSourceName))->unsubscribe(this))) {
        std::string errMsg = std::string("PacketSource: ") + packetSourceName +
                    " returned false when attempting to unsubscribe";
        error(errMsg.c_str());
    }

    subscriptions.erase(packetSourceName);
    subscribedCount = getSubscribedCount();
}
