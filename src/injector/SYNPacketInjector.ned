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

package cmu.sv.mews.playback.injector;

import inet.transportlayer.contract.ITCP;

//
// TODO auto-generated type
//
simple SYNPacketInjector like ITCP
{
    parameters:
        string packetSource = default("packetSource[0]");  // PacketSource module to subscribe to
        
        @display("i=block/departure");
        @signal[sentSYNPk](type=cPacket);
        @statistic[sentSYNPk](title="packets sent"; source=sentSYNPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        
    gates:
        // ITCP contract
        input appIn[] @labels(TCPCommand/down);
        input ipIn @labels(TCPSegment,IPv4ControlInfo/up,IPv6ControlInfo/up);
        output appOut[] @labels(TCPCommand/up);
        output ipOut @labels(TCPSegment,IPv4ControlInfo/down,IPv6ControlInfo/down);
}
