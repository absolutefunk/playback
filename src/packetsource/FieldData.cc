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

#include "FieldData.h"

void FieldData::addValue(double val) {
    Field field;
    field.fieldType = PacketParserContract::FIELD_DOUBLE;
    field.doubleValue = val;

    _fields.push_back(field);
}

void FieldData::addValue(int val) {
    Field field;
    field.fieldType = PacketParserContract::FIELD_INT;
    field.intValue = val;

    _fields.push_back(field);
}

void FieldData::addValue(std::string val) {
    Field field;
    field.fieldType = PacketParserContract::FIELD_STRING;
    field.stringValue = val;

    _fields.push_back(field);
}

// getters
int FieldData::intValueAt(unsigned int index) {
    if (index >= _fields.size()) {
        throw cRuntimeError("Violation of Contract: Requesting int value at index greater than the number of fields.");
    }

    if (_fields[index].fieldType != PacketParserContract::FIELD_INT) {
        throw cRuntimeError("Violation of Contract: [Field %u] Requesting int value for field that is not a int.", index);
    }

    return _fields[index].doubleValue;
}

double FieldData::doubleValueAt(unsigned int index) {
    if (index >= _fields.size()) {
        throw cRuntimeError("Violation of Contract: Requesting double value at index greater than the number of fields.");
    }

    if (_fields[index].fieldType != PacketParserContract::FIELD_DOUBLE) {
        throw cRuntimeError("Violation of Contract: [Field %u] Requesting double value for field that is not a double.", index);
    }

    return _fields[index].doubleValue;
}

std::string FieldData::stringValueAt(unsigned int index) {
    if (index >= _fields.size()) {
        throw cRuntimeError("Violation of Contract: Requesting string value at index greater than the number of fields.");
    }

    if (_fields[index].fieldType != PacketParserContract::FIELD_STRING) {
        throw cRuntimeError("Violation of Contract: [Field %u] Requesting string value for field that is not a string.", index);
    }

    return _fields[index].stringValue;
}

FieldData::Field FieldData::getFieldAt(unsigned int index) {
    if (index >= _fields.size()) {
        throw cRuntimeError("Violation of Contract: Requesting field at index greater than the number of fields.");
    }

    return _fields[index];
}
