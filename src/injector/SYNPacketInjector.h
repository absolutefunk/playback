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

#ifndef SYNPACKETINJECTOR_H_
#define SYNPACKETINJECTOR_H_

#include "BasicPacketSourceData_m.h"
#include "PacketInjector.h"

#include "inet/networklayer/common/IPSocket.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/transportlayer/tcp_common/TCPSegment.h"

class SYNPacketInjector: public PacketInjector {
public:
    virtual void receivePacketData(cMessage *pktData);  // contract from PacketInjector

protected:
    virtual void initialize(int stage);
    virtual int numInitStages() const { return 16; }
    virtual void handleMessage(cMessage *msg);

private:
    inet::IInterfaceTable *interfaceTable = nullptr;
    inet::IPSocket ipSocket = nullptr;  // used to register the injector

    // statistics
    simsignal_t sentPkSignal;

    inet::tcp::TCPSegment* generateSyn(BasicPacketSourceData *pktData);  // generates a SYN packet
    void sendSyn(inet::tcp::TCPSegment *synPkt, BasicPacketSourceData *pktData);  // sends out a SYN packet
};

#endif /* SYNPACKETINJECTOR_H_ */
