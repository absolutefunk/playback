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

#ifndef FIELDDATA_H_
#define FIELDDATA_H_

#include <string>
#include <vector>

#include <omnetpp.h>

#include "PacketParserContract.h"

// Holds all the field data for a PacketSourceData message.
class FieldData {
public:
    struct Field {
        PacketParserContract::FieldType fieldType;
        double doubleValue;
        int intValue;
        std::string stringValue;

        // flags
        bool isTimeStamp;
    };

    virtual void setTimestamp(simtime_t timestamp) { _timestamp = timestamp; }
    virtual simtime_t getTimestamp() { return _timestamp; }

    virtual std::size_t getFieldSize() { return _fields.size(); }

    //value setters
    virtual void addValue(double val);
    virtual void addValue(int val);
    virtual void addValue(std::string val);

    // value getters
    virtual double doubleValueAt(unsigned int index);
    virtual int intValueAt(unsigned int index);
    virtual std::string stringValueAt(unsigned int index);

    virtual Field getFieldAt(unsigned int index);

protected:
    std::vector<Field> _fields;
    simtime_t _timestamp;
};

#endif /* FIELDDATA_H_ */
