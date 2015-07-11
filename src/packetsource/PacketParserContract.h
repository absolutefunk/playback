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


#ifndef PACKETPARSERCONTRACT_H_
#define PACKETPARSERCONTRACT_H_

#include <vector>

class PacketParserContract {
public:
    enum FieldType {
        FIELD_TIMESTAMP_MS,
        FIELD_TIMESTAMP_S,
        FIELD_STRING,
        FIELD_INT,
        FIELD_DOUBLE
    };

    // shorthand for checking if a fieldType is a timestamp type
    static bool isTimestamp(FieldType t) { return (t == FIELD_TIMESTAMP_MS) || (t == FIELD_TIMESTAMP_S);}

    // return the number of fields
    virtual std::size_t getFieldSize() { return fieldTypes.size(); }

    // add a new field to the end of the array
    virtual void addField(FieldType fieldType) { fieldTypes.push_back(fieldType); }

    // get field at index
    virtual FieldType getFieldAt(unsigned int index) { return fieldTypes[index]; }

protected:
    // The field types required by the PacketSource or PacketInjector.  The ordering corresponds to field order
    // expected for parsing / processing / etc...
    std::vector<FieldType> fieldTypes;
};

#endif /* PACKETPARSERCONTRACT_H_ */
