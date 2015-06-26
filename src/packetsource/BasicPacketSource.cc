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

#include "BasicPacketSource.h"

Define_Module(BasicPacketSource);

void BasicPacketSource::initialize() {
    ScheduledPacketSource::initialize();  // call this first

    parseData(par("sourceFile").stringValue());  // parse the CSV
    WATCH(dataSize);

    scheduleNext();  // schedule the first pktData
}

void BasicPacketSource::scheduleNext() {
    // This will keep scheduling the next pktData until the list is empty
    if(data.size() > 0) {
        scheduleToDispatch(data.front());
        data.pop_front();  // remove the pktData ptr we just scheduled
        --dataSize;
    }
}

void BasicPacketSource::finish() {
    ScheduledPacketSource::finish();

    // we need to delete any cMessage objects we created that havn't been sent out yet.
    for(std::list<BasicPacketSourceData *>::iterator it = data.begin(); it != data.end(); ++it) {
        delete *it;
    }
}

void BasicPacketSource::parseData(const char *fileName) {
    std::string delims(",");  // split based on commas

    std::ifstream infile(fileName);

    if (!infile) {
        // couldn't open the file
        std::string errMsg = std::string("File: ") + fileName + " failed to open.  Does the file exist?";
        error(errMsg.c_str());
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

        // check to make sure the number of tokens equals the expected number
        if (tokens.size() != TOKEN_NUM) {
            EV << "[BasicPacketSource]: parsing: number of elements does not match expected number (line "
                    << lineNum << ").  Token count: " << tokens.size() << ", expected count: " << TOKEN_NUM << ".\n";
            continue;
        }

        BasicPacketSourceData *pktData = new BasicPacketSourceData("BasicPacketSourceData");
        // we want the time in milliseconds, so we need to convert first
        double tsMilli = std::stod(tokens[0]) / 1000.0;
        pktData->setTimestamp(SimTime(tsMilli));  // timestamp
        pktData->setSrcAddress(tokens[1].c_str());  // source address
        pktData->setSrcPort(std::stoi(tokens[2]));  // source port
        pktData->setDestAddress(tokens[3].c_str());  // destination address
        pktData->setDestPort(std::stoi(tokens[4]));  // destination port
        pktData->setSeqNo(std::stoi(tokens[5]));  // sequence number
        pktData->setWindowSize(std::stoi(tokens[6]));  // window size

        data.push_back(pktData);
    }

    dataSize = data.size();
}

std::string BasicPacketSource::trimString(std::string str) {
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
