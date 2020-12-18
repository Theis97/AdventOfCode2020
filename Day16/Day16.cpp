#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "../Utilities/StringUtils.h"

struct FieldRanges {
    int leftLowBound;
    int leftHighBound;
    int rightLowBound;
    int rightHighBound;
};

// This method relys on the fact that we end up with at least 1 position that has only 
// 1 possible field after analyzing all of the valid tickets.
// In the general case, we could end up with no positions with only one field but still have a solvable problem,
// which this code will fail on. TODO, someday, maybe: fix that
void NarrowOptions(int pos, std::string confirmedField, std::vector<std::set<std::string>>& candidateFieldPositions) {
    for (int i = 0; i < candidateFieldPositions.size(); i++) {
        if (i != pos && candidateFieldPositions[i].size() != 1) {
            std::set<std::string> possiblePositions = candidateFieldPositions[i];
            possiblePositions.erase(confirmedField);
            candidateFieldPositions[i] = possiblePositions;
            if (possiblePositions.size() == 1) {
                NarrowOptions(i, *possiblePositions.begin(), candidateFieldPositions);
            }
        }
    }
}

int main() {

    std::ifstream inputFile;
    inputFile.open("day16.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    // field name -> valid ranges
    std::map<std::string, FieldRanges> fields;

    std::vector<std::set<std::string>> candidateFieldPositions;
    std::set<std::string> allFieldNames;

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        std::vector<std::string> fieldTokens = TokenizeString(line, ':');
        std::string fieldName = fieldTokens[0];

        allFieldNames.insert(fieldName);

        std::vector<std::string> rangeTokens = TokenizeString(fieldTokens[1], ' ');
        std::vector<std::string> leftRanges = TokenizeString(rangeTokens[0], '-');
        std::vector<std::string> rightRanges = TokenizeString(rangeTokens[2], '-');

        FieldRanges ranges{ std::stoi(leftRanges[0]), std::stoi(leftRanges[1]),
                            std::stoi(rightRanges[0]), std::stoi(rightRanges[1]) };

        fields[fieldName] = ranges;
    }

    for (int i = 0; i < allFieldNames.size(); i++) {
        candidateFieldPositions.push_back(std::set<std::string>(allFieldNames));
    }

    std::getline(inputFile, line); // "your ticket:"

    std::getline(inputFile, line);
    std::string yourTicket = line;

    std::getline(inputFile, line); // empty string
    std::getline(inputFile, line); // "nearby tickets:"

    int invalidFieldSum = 0;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> ticketValues = TokenizeString(line, ',');

        for (int i = 0; i < ticketValues.size(); i++) {
            int value = std::stoi(ticketValues[i]);
            bool matchesAnyField = false;
            std::vector<std::string> unmatchableFields;

            for (auto &field : fields) {
                FieldRanges ranges = field.second;
                if (value >= ranges.leftLowBound && value <= ranges.leftHighBound
                 || value >= ranges.rightLowBound && value <= ranges.rightHighBound) {
                    matchesAnyField = true;
                }
                else {
                    unmatchableFields.push_back(field.first);
                }
            }
            if (!matchesAnyField) {
                invalidFieldSum += value;
            }
            else {
                for (auto &fieldName : unmatchableFields) {
                    std::set<std::string> possiblePositions = candidateFieldPositions[i];
                    possiblePositions.erase(fieldName);
                    candidateFieldPositions[i] = possiblePositions;
                }
            }
        }
    }

    std::cout << "Ticket Scanning Error Rate: " << invalidFieldSum << "\n";

    for (int i = 0; i < candidateFieldPositions.size(); i++) {
        if (candidateFieldPositions[i].size() == 1) {
            NarrowOptions(i, *candidateFieldPositions[i].begin(), candidateFieldPositions);
            break;
        }
    }

    std::cout << "Field positions:\n";
    for (int i = 0; i < candidateFieldPositions.size(); i++) {
        std::cout << i << " - ";
        for (auto &field : candidateFieldPositions[i]) {
            std::cout << field << "\n";
        }
    }
    std::cout << "\n";
}