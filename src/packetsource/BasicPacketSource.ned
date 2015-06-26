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

package cmu.sv.mews.playback.packetsource;

//
// TODO auto-generated type
//
simple BasicPacketSource like IScheduledPacketSource
{
    parameters:
        string sourceFile = default("TestData.csv");
        
        @signal[scheduledPk](type=int);
    	@signal[dispatchedPk](type=int);
    	@statistic[scheduledPk](title="pktData Scheduled"; source=scheduledPk; record=count,vector; interpolationmode=none);
    	@statistic[dispatchedPk](title="pktData Dispatched"; source=dispatchedPk; record=count,vector; interpolationmode=none);
}
