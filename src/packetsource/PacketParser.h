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

#ifndef PACKETPARSER_H_
#define PACKETPARSER_H_

#include <list>

#include "FieldData.h"
#include "PacketParserContract.h"

#include <omnetpp.h>

// Base for PacketParsers.  While not strictly required when writing PacketSources, this is useful for
// modularity of a PacketSource in terms of being compatible with multiple parsers.
class PacketParser {
public:
    virtual ~PacketParser() = default;

    // assign a new contract for this parser
    virtual void assignContract(PacketParserContract contract) { _contract = contract; }

    // return a copy of the current contract
    virtual PacketParserContract getCurrentContract() { return _contract; }

    // add a contract field to the current contract
    virtual void addContractField(PacketParserContract::FieldType field) { _contract.addField(field); }

    // get the contract field at index
    virtual PacketParserContract::FieldType getContractFieldAt(unsigned int index) { return _contract.getFieldAt(index); }

    // This method is called to load and parse the data.  The input represents the path/filename of the input file.
    virtual void parse(const char *path) = 0;

    // data retrieval methods
    virtual FieldData pop();
    virtual FieldData peek() { return _data.front(); }

    virtual std::size_t getSize() { return _data.size(); }

protected:
    // Add new fieldData.  This method forces the contract.
    virtual void push(FieldData fieldData);

    PacketParserContract _contract;  // contract for what gets parsed
    std::list<FieldData> _data; // parsed data
};

#endif /* PACKETPARSER_H_ */
