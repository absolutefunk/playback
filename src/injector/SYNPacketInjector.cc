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

#include "SYNPacketInjector.h"

#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/INetworkProtocolControlInfo.h"
#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/networklayer/ipv4/IPv4InterfaceData.h"

Define_Module(SYNPacketInjector);

void SYNPacketInjector::initialize(int stage) {
    if (stage == 0) {
        // Get the InterfaceTable for the host we are a part of.  This is needed to subvert the network layer
        // source address checks.  Since all we are doing is injecting packets, it is not our job to check
        // validity of the pktData itself (though other injectors may require these checks).
        interfaceTable = dynamic_cast<inet::IInterfaceTable *>(getModuleByPath("^.interfaceTable"));

        if(!interfaceTable) {
            error("SYNPacketInjector: Could not find the interfaceTable module!");
        }

        // register signals
        sentPkSignal = registerSignal("sentSYNPk");

        WATCH(subscribedCount);
    }
    else if (stage == 1) {
        // gives the PacketSources a chance to initialize stuff at stage 0
        subscribeToPacketSource(par("packetSource"));  // INET3 change: passing cPar directly due to ModuleAccess structure changing

        // currently only IPv4 supported
        ipSocket.setOutputGate(gate("ipOut"));  // assign our IPv4 out gate
        ipSocket.registerProtocol(inet::IP_PROT_TCP);  // register our protocol on the appropriate gate to the network layer
    }
    else if (stage == 15) {
        // Add a fake interface if using IPv4.  This is needed if the src address does not match the one on the interface
        // We do this in stage 3 to make sure we aren't conflicting with any autoconfigurators which may throw
        // exceptions in the presence of this fake interface :-)
        // 1337 h4x0r m0d3

        // INET3: The autoconfigurator now configures nodes at the 14th stage.  So thus we need to do this
        // at the 15th stage...

        // TODO: don't assume using IPv4
        inet::InterfaceEntry *fakeInterface = new inet::InterfaceEntry(this);
        fakeInterface->setName("fk0");
        fakeInterface->setLoopback(true);  // We don't want other protocols to think this is a public interface

        inet::IPv4InterfaceData *ipv4Data = new inet::IPv4InterfaceData();
        ipv4Data->setIPAddress(inet::IPv4Address());
        fakeInterface->setIPv4Data(ipv4Data);

        interfaceTable->addInterface(fakeInterface);
    }
}

void SYNPacketInjector::receivePacketData(cMessage *pktData) {
    Enter_Method_Silent(); // required as this method is callable from other modules (NotificationBoard)
    take(pktData);  // transferring ownership to us

    // have a new SYN Packet to send out
    BasicPacketSourceData *packetSourceData = check_and_cast<BasicPacketSourceData *>(pktData);
    sendSyn(generateSyn(packetSourceData), packetSourceData);

    delete pktData;  // no memory leaks here
}

void SYNPacketInjector::handleMessage(cMessage *msg) {
    // We don't handle any messages, so delete this (probably ICMP packets, which we should not receive at the
    // transport layer anyways...)
    EV << "[SYNPacketInjector]: Received message from lower layer.  Deleting...\n";

    delete msg;
}

inet::tcp::TCPSegment* SYNPacketInjector::generateSyn(BasicPacketSourceData *pktData) {
    inet::tcp::TCPSegment *synPkt = new inet::tcp::TCPSegment("SYNPacketInjector");

    // SYN PDU config
    // The default instantiation clears all flags, and sets the header length to no options.
    synPkt->setSynBit(true);  // set SYN flag
    synPkt->setSrcPort(pktData->getSrcPort());  // source port
    synPkt->setDestPort(pktData->getDestPort());  // destination port
    synPkt->setSequenceNo(pktData->getSeqNo());  // sequence number
    synPkt->setWindow(pktData->getWindowSize()); // window size

    // set the proper size of the packet (sim side - this is not a header param)
    synPkt->setByteLength(TCP_HEADER_OCTETS);

    return synPkt;
}

void SYNPacketInjector::sendSyn(inet::tcp::TCPSegment *synPkt, BasicPacketSourceData *pktData) {
    EV << "[SYNPacketInjector]: Preparing to inject a new SYN packet...\n";

    // The second param, addrType, is not used since the correct IP protocol is resolved
    // before the addrType is needed (hence just stick a -1 here).
    inet::L3Address srcAddr = inet::L3AddressResolver().resolve(pktData->getSrcAddress(), -1);
    inet::L3Address destAddr = inet::L3AddressResolver().resolve(pktData->getDestAddress(), -1);

    // INET3: generalized IP address types
    inet::IL3AddressType *addressType = destAddr.getAddressType();
    inet::INetworkProtocolControlInfo *controlInfo = addressType->createNetworkProtocolControlInfo();

    controlInfo->setTransportProtocol(inet::IP_PROT_TCP);
    controlInfo->setSourceAddress(srcAddr);

    // The IPv4 network layer checks for valid source addresses and throws an exception if no interface is assigned
    // to a source address given.  So to avoid hacking the IP protocol, change the fake interface address to the one
    // we just generated.
    interfaceTable->getInterfaceByName("fk0")->ipv4Data()->setIPAddress(controlInfo->getSourceAddress().toIPv4());

    controlInfo->setDestinationAddress(destAddr);
    // INET3: INetworkProtocolControlInfo does not inherent cObject, but whichever derived class
    // we actually pass here does.
    synPkt->setControlInfo(check_and_cast<cObject *>(controlInfo));

    send(synPkt, "ipOut");

    emit(sentPkSignal, synPkt);
}
