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

package cmu.sv.mews.playback;

import cmu.sv.mews.playback.packetsource.IPacketSource;
import inet.node.inet.StandardHost;
import ned.IdealChannel;

//
// TODO auto-generated type
//
module PlaybackHost extends StandardHost
{
    parameters:
        int numPacketSources = default(1);
        
        numRadios = default(1);

        @display("i=device/palm");

    submodules:
        packetSource[numPacketSources]: <default("")> like IPacketSource {
            @display("p=147,287");
        }
}
