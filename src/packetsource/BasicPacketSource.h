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

#ifndef BASICPACKETSOURCE_H_
#define BASICPACKETSOURCE_H_

#include <list>
#include <string>

#include "ScheduledPacketSource.h"
#include "BasicPacketSourceData_m.h"

// Basic PacketSource which accepts a comma-delim list of data:
// timestamp, source IP/port, destination IP/port
class BasicPacketSource: public ScheduledPacketSource {
protected:
    unsigned int dataSize; // WATCH variable
    std::list<BasicPacketSourceData *> data;

    virtual void scheduleNext();
    virtual void initialize();
    virtual void finish();

private:
    const unsigned int TOKEN_NUM = 7;

    void parseData(const char *fileName);
    std::string trimString(std::string str);
};

#endif /* BASICPACKETSOURCE_H_ */
