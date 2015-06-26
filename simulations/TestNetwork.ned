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

package cmu.sv.mews.playback.simulations;

import cmu.sv.mews.playback.PlaybackHost;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.nodes.ethernet.Eth100M;
import inet.nodes.inet.StandardHost;
import inet.nodes.wireless.AccessPoint;
import inet.world.radio.ChannelControl;


//
// TODO auto-generated type
//
network TestNetwork
{
    submodules:
        playbackHost: PlaybackHost {
            @display("p=60,139");
        }
        accessPoint: AccessPoint {
            @display("p=248,173");
        }
        targetHost: StandardHost {
            @display("p=388,173");
        }

        channelControl: ChannelControl {
            @display("p=60,30");
        }
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = default(xmldoc("test_network.xml"));
                @display("p=150,30");
        }
    connections:
        accessPoint.ethg++ <--> Eth100M <--> targetHost.ethg++;
}
