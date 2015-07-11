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

#include "PacketParser.h"

FieldData PacketParser::pop() {
    FieldData pktData = _data.front();
    _data.pop_front();

    return pktData;
}

void PacketParser::push(FieldData fieldData) {
    // check fieldData to make sure it abides by the contract
    unsigned int j = 0;
    for (unsigned int i = 0; i < _contract.getFieldSize(); ++i) {
        if (PacketParserContract::isTimestamp(_contract.getFieldAt(i))) {
            // We don't validate the timestamps, as they are
            continue;
        }

        if (fieldData.getFieldAt(j++).fieldType != _contract.getFieldAt(i)) {
            throw cRuntimeError("Violation of Contract: In FieldData to push: Field %u FieldType mismatch", i);
        }
    }

    _data.push_back(fieldData);
}


