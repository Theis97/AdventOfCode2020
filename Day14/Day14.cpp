#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bitset>
#include "../Utilities/StringUtils.h"

const bool partOne = false;
const int bitSize = 36;

void PartOneInstructions() {

    std::ifstream inputFile;
    inputFile.open("day14.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return;
    }

    uint64_t onesMask = 0;
    uint64_t zerosMask = ~onesMask;

    std::map<int, uint64_t> memory;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> tokens = TokenizeString(line, ' ');
        if (tokens[0] == "mask") {
            std::string newOnesMask;
            std::string newZerosMask;
            for (char c : tokens[2]) {
                if (c == '0') {
                    newOnesMask += "0";
                    newZerosMask += "0";
                }
                else if (c == '1') {
                    newOnesMask += "1";
                    newZerosMask += "1";
                }
                else {
                    newOnesMask += "0";
                    newZerosMask += "1";
                }
            }
            onesMask = std::stoull(newOnesMask, nullptr, 2);
            zerosMask = std::stoull(newZerosMask, nullptr, 2);
        }
        else {
            uint64_t value = std::stoull(tokens[2]);
            int memLocation = std::stoi(SubstrByEndpoint(tokens[0], 4, tokens[0].length() - 1));

            uint64_t maskedValue = value | onesMask;
            maskedValue = maskedValue & zerosMask;
            memory[memLocation] = maskedValue;
        }
    }

    uint64_t sum = 0;
    for (auto& m : memory) {
        sum += m.second;
    }

    std::cout << "Sum of all values remaining in memory: " << sum << "\n";
}


void StoreWithFloatingBits(std::map<unsigned long long, long long>& memory, long long value,
    std::bitset<bitSize> address, std::string mask, int index) {

    if (index >= bitSize) {
        unsigned long long a = address.to_ullong();
        memory[a] = value;
        return;
    }

    if (mask[index] != 'X') {
        StoreWithFloatingBits(memory, value, address, mask, index + 1);
    }
    else {
        StoreWithFloatingBits(memory, value, address.set(bitSize - index - 1), mask, index + 1);
        StoreWithFloatingBits(memory, value, address.reset(bitSize - index - 1), mask, index + 1);
    }
}

int main() {

    if (partOne) {
        PartOneInstructions();
        return 0;
    }

    std::ifstream inputFile;
    inputFile.open("day14.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string mask;
    std::map<unsigned long long, long long> memory;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> tokens = TokenizeString(line, ' ');
        if (tokens[0] == "mask") {
            mask = tokens[2];
        }
        else {
            long long value = std::stoull(tokens[2]);
            std::bitset<bitSize> memLocation(std::stoull(SubstrByEndpoint(tokens[0], 4, tokens[0].length() - 1)));

            for (int i = 0; i < bitSize; i++) {
                if (mask[i] == '1') {
                    memLocation.set(bitSize - i - 1);
                }
            }

            // Now for the floating bits
            int firstFloater = mask.find('X');
            if (firstFloater == std::string::npos) {
                unsigned long long address = memLocation.to_ullong();
                memory[address] = value;
            }
            else {
                StoreWithFloatingBits(memory, value, memLocation.set(bitSize - firstFloater - 1), mask, firstFloater + 1);
                StoreWithFloatingBits(memory, value, memLocation.reset(bitSize - firstFloater - 1), mask, firstFloater + 1);
            }
        }
    }

    long long sum = 0;
    for (auto &m : memory) {
        sum += m.second;
    }

    std::cout << "Sum of all values remaining in memory: " << sum << "\n";
}