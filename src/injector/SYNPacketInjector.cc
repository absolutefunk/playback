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

#include "InterfaceTableAccess.h"
#include "IPv4Address.h"
#include "IPv4ControlInfo.h"
#include "IPv4InterfaceData.h"

Define_Module(SYNPacketInjector);

void SYNPacketInjector::initialize(int stage) {
    if (stage == 0) {
        // Get the InterfaceTable for the host we are a part of.  This is needed to subvert the network layer
        // source address checks.  Since all we are doing is injecting packets, it is not our job to check
        // validity of the pktData itself (though other injectors may require these checks).
        interfaceTable = InterfaceTableAccess().getIfExists();

        // register signals
        sentPkSignal = registerSignal("sentSYNPk");

        WATCH(subscribedCount);
    }
    else if (stage == 1) {
        // gives the PacketSources a chance to initialize stuff at stage 0
        subscribeToPacketSource("packetSource[0]");

        // currently only IPv4 supported
        ipSocket.setOutputGate(gate("ipOut"));  // assign our IPv4 out gate
        ipSocket.registerProtocol(IP_PROT_TCP);  // register our protocol on the appropriate gate to the network layer
    }
    else if (stage == 3) {
        // Add a fake interface if using IPv4.  This is needed if the src address does not match the one on the interface
        // We do this in stage 3 to make sure we aren't conflicting with any autoconfigurators which may throw
        // exceptions in the presence of this fake interface :-)
        // 1337 h4x0r m0d3
        InterfaceEntry *fakeInterface = new InterfaceEntry(NULL);
        fakeInterface->setName("fk0");
        fakeInterface->setLoopback(true);  // We don't want other protocols to think this is a public interface

        IPv4InterfaceData *ipv4Data = new IPv4InterfaceData();
        ipv4Data->setIPAddress(IPv4Address());
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

TCPSegment* SYNPacketInjector::generateSyn(BasicPacketSourceData *pktData) {
    TCPSegment *synPkt = new TCPSegment("SYNPacketInjector");

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

void SYNPacketInjector::sendSyn(TCPSegment *synPkt, BasicPacketSourceData *pktData) {
    EV << "[SYNPacketInjector]: Preparing to inject a new SYN packet...\n";

    IPv4ControlInfo *controlInfo = new IPv4ControlInfo();
    controlInfo->setProtocol(IP_PROT_TCP);
    controlInfo->setSrcAddr(IPv4Address(pktData->getSrcAddress()));
    // The IPv4 network layer checks for valid source addresses and throws an exception if no interface is assigned
    // to a source address given.  So to avoid hacking the IP protocol, change the fake interface address to the one
    // we just generated.
    interfaceTable->getInterfaceByName("fk0")->ipv4Data()->setIPAddress(controlInfo->getSrcAddr());

    controlInfo->setDestAddr(IPv4Address(pktData->getDestAddress()));
    synPkt->setControlInfo(controlInfo);

    send(synPkt, "ipOut");

    emit(sentPkSignal, synPkt);
}
