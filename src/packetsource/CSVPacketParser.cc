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

#include <fstream>
#include <vector>

#include "CSVPacketParser.h"

void CSVPacketParser::parse(const char *path) {
    parseData(path);
}

void CSVPacketParser::parseData(const char *path) {
    std::string delims(",");  // split based on commas

    std::ifstream infile(path);

    if (!infile) {
        // couldn't open the file
        std::string errMsg = std::string("File: ") + path + " failed to open.  Does the file exist?";
        throw cRuntimeError(errMsg.c_str());
    }

    std::string line;
    std::size_t lineNum = 0;

    // for each line in the CSV
    while (std::getline(infile, line)) {
        ++lineNum;
        std::vector<std::string> tokens;

        std::size_t tokenStart = 0;
        std::size_t pos;
        while ((pos = line.find_first_of(delims, tokenStart)) != std::string::npos) {
            if (tokenStart < pos) {
                // non-empty token: we assume the data will be complete; no tokens of zero-length
                tokens.push_back(trimString(line.substr(tokenStart, pos-tokenStart)));
                //EV << trimString(line.substr(tokenStart, pos-tokenStart)) << ",";
            }
            tokenStart = pos + 1;
        }

        if (tokenStart < line.length()) {
            // catch the last token
            tokens.push_back(trimString(line.substr(tokenStart, line.length() - tokenStart)));
            //EV << trimString(line.substr(tokenStart, line.length() - tokenStart)) << ",";
        }
        //EV << "\n";

        // check to make sure the number of tokens equals the expected number.  The expected number of tokens is equal
        // to the number of fieldTypes present in the PacketParserContract given.  We do not consider a mismatch of
        // tokens to be a Contract violation, since large input datasets may have lines that need to be thrown away.
        // Instead we print the line to the console in question, and increment a WATCH variable for the sum of lines
        // thrown away.
        if (tokens.size() != _contract.getFieldSize()) {
            EV << "[BasicPacketSource]: parsing: number of elements does not match expected number (line "
                    << lineNum << ").  Token count: " << tokens.size() << ", expected count: " << _contract.getFieldSize() << ".\n";
            ++rowsDisgarded;
            continue;
        }

        // Now that we have a row of data, parse it according to the PacketParserContract given.
        FieldData data;

        for (unsigned int index = 0; index < tokens.size(); ++index) {
            if (_contract.getFieldAt(index) == PacketParserContract::FIELD_TIMESTAMP_MS) {
                // we assume the input data is in milliseconds
                double tsMilli = std::stod(tokens[index]) / 1000.0;
                data.setTimestamp(SimTime(tsMilli));
            }
            else if (_contract.getFieldAt(index) == PacketParserContract::FIELD_TIMESTAMP_S) {
                // we assume the input data is in seconds
                data.setTimestamp(SimTime(std::stod(tokens[index])));
            }
            else if (_contract.getFieldAt(index) == PacketParserContract::FIELD_DOUBLE) {
                data.addValue(std::stod(tokens[index]));
            }
            else if (_contract.getFieldAt(index) == PacketParserContract::FIELD_INT) {
                data.addValue(std::stoi(tokens[index]));
            }
            else if (_contract.getFieldAt(index) == PacketParserContract::FIELD_STRING) {
                data.addValue(tokens[index]);
            }
        }

        push(data);
    }
}

std::string CSVPacketParser::trimString(std::string str) {
    std::string whitespace("\n\r\t ");
    std::size_t startPos = 0;
    std::size_t endPos = str.length();

    //remove from both ends
    // left side
    for(std::size_t i = 0; i < str.length(); ++i) {
        bool isWhitespace = false;
        for (std::size_t j = 0; j < whitespace.length(); ++j) {
            if (str[i] == whitespace[j]) {
                // found whitespace
                ++startPos;
                isWhitespace = true;
                break;
            }
        }

        if (!isWhitespace) {
            break;
        }
    }

    // right side
    for(std::size_t i = str.length() - 1; i > startPos;  --i) {
        bool isWhitespace = false;
        for (std::size_t j = 0; j < whitespace.length(); ++j) {
            if (str[i] == whitespace[j]) {
                // found whitespace
                --endPos;
                isWhitespace = true;
                break;
            }
        }

        if (!isWhitespace) {
            break;
        }
    }

    return str.substr(startPos, endPos - startPos);
}
