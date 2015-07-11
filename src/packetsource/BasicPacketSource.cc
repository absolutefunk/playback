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

#include "BasicPacketSource.h"

#include "CSVPacketParser.h"

Define_Module(BasicPacketSource);

void BasicPacketSource::initialize() {
    ScheduledPacketSource::initialize();  // call this first

    // get the parser type and instantiate
    std::string parserName = par("packetParser").stdstringValue();
    // TODO:  Lookup valid parsers that match the name instead of just hardcoding it here.  The method
    // should return a pointer to the correct parser, if it exists, and NULL otherwise.
    if (parserName.compare("CSVPacketParser") == 0) {
        _parser = new CSVPacketParser();
        // TODO: this WATCH variable should be in the base class
        unsigned int &datasetRowsDisgarded = dynamic_cast<CSVPacketParser *>(_parser)->getRowsDisgarded();
        WATCH(datasetRowsDisgarded);
    }
    else {
        // if the input PacketParser (from omnetpp.ini / NED) is unrecognized
        error("Unrecognized PacketParser type: %s", par("packetParser").stringValue());
    }

    // add the fieldsTypes for the contract
    _parser->addContractField(PacketParserContract::FIELD_TIMESTAMP_MS);    // timestamp (milliseconds)
    _parser->addContractField(PacketParserContract::FIELD_STRING);          // Src IP
    _parser->addContractField(PacketParserContract::FIELD_INT);             // Src port
    _parser->addContractField(PacketParserContract::FIELD_STRING);          // Dst IP
    _parser->addContractField(PacketParserContract::FIELD_INT);             // Dst port
    _parser->addContractField(PacketParserContract::FIELD_INT);             // SeqNo
    _parser->addContractField(PacketParserContract::FIELD_INT);             // Window Size

    // parse the CSV file
    // Note that this can throw cRuntimeErrors, as the error() convenience method is only available
    // for cSimpleModules
    try {
        _parser->parse(par("sourceFile").stringValue());
    }
    catch (cRuntimeError &ex) {
        error(ex.what());
    }

    // initial size of the data
    currentDataRowSize = _parser->getSize();
    WATCH(currentDataRowSize);

    // schedule the first pktData
    scheduleNext();
}

void BasicPacketSource::scheduleNext() {
    // This will keep scheduling the next pktData until the list is empty
    if(_parser->getSize() > 0) {
        // create the message for the subscribed injectors
        BasicPacketSourceData *pktData = new BasicPacketSourceData("BasicPacketSource");
        FieldData fields = _parser->pop();

        // cRuntimeErrors can be thrown here
        try {
            // Note how the indices match with the ordering of the contract fieldTypes, except the timestamp which is
            // stored separately.
            pktData->setTimestamp(fields.getTimestamp());  // timestamp
            pktData->setSrcAddress(fields.stringValueAt(0).c_str());  // source address
            pktData->setSrcPort(fields.intValueAt(1));  // source port
            pktData->setDestAddress(fields.stringValueAt(2).c_str());  // destination address
            pktData->setDestPort(fields.intValueAt(3));  // destination port
            pktData->setSeqNo(fields.intValueAt(4));  // sequence number
            pktData->setWindowSize(fields.intValueAt(5));  // window size
        }
        catch (cRuntimeError &ex) {
            error(ex.what());
        }

        scheduleToDispatch(pktData);
        currentDataRowSize = _parser->getSize();  // should be decremented by 1
    }
}
