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

#ifndef CSVPACKETPARSER_H_
#define CSVPACKETPARSER_H_

#include "PacketParser.h"

class CSVPacketParser: public PacketParser {
public:
    CSVPacketParser() : rowsDisgarded(0) { }
    virtual void parse(const char *path);  // contract from PacketParser

    // A reference is returned here so it can be used as a WATCH variable.
    virtual unsigned int& getRowsDisgarded() { return rowsDisgarded; }

protected:
    unsigned int rowsDisgarded;

    virtual void parseData(const char *path);
    virtual std::string trimString(std::string str);

};

#endif /* CSVPACKETPARSER_H_ */
