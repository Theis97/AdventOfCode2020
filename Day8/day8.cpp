#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../Utilities/StringUtils.h"

int main() {
    std::ifstream inputFile;
    inputFile.open("day8.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    // the boolean indicates whether we've seen this instruction already
    std::vector<std::pair<std::string, bool>> instructions;

    std::string line;
    while (std::getline(inputFile, line)) {
        instructions.push_back(std::pair<std::string, bool>(line, false));
    }

    bool firstRun = true;
    int accumulator = 0;
    int instructionPointer = 0;
    // stores the state of the program at each jmp/nop from the first run
    // first is instruction pointer, second is accumulator value
    std::vector<std::pair<int, int>> programStates;
    bool terminated = false;

    while (!terminated) {
        bool loopDetected = false;
        while (!loopDetected && !terminated) {
            if (instructionPointer >= instructions.size()) {
                terminated = true;
                break;
            }

            std::pair<std::string, bool> instruction = instructions[instructionPointer];
            if (instruction.second) {
                loopDetected = true;
                break;
            }
            instructions[instructionPointer].second = true;
            std::vector<std::string> instComponents = TokenizeString(instruction.first, ' ');

            if (instComponents[0] == "acc") {
                accumulator += std::stoi(instComponents[1]);
                instructionPointer++;
            }
            else if (instComponents[0] == "jmp") {
                if (firstRun) {
                    programStates.push_back(std::pair<int, int>(instructionPointer, accumulator));
                }
                instructionPointer += std::stoi(instComponents[1]);
            }
            else {
                if (firstRun) {
                    programStates.push_back(std::pair<int, int>(instructionPointer, accumulator));
                }
                instructionPointer++;
            }
        }

        if (firstRun) {
            std::cout << "Accumulator value before looping: " << accumulator << "\n";
            firstRun = false;
        }

        if (!terminated) {
            // reset and try again
            // we don't reset the "seen" booleans, if we hit an instruction we've tried before
            // even in a different run we know it won't work
            std::pair<int, int> state = programStates.back();
            programStates.pop_back();

            accumulator = state.second;

            std::vector<std::string> instComponents = TokenizeString(instructions[state.first].first, ' ');
            if (instComponents[0] == "jmp") {
                // treat it like a nop this time
                instructionPointer = state.first + 1;
            }
            else if (instComponents[0] == "nop") {
                // treat it like a jmp this time
                instructionPointer = state.first + std::stoi(instComponents[1]);
            }
        }
    }

    std::cout << "Accumulator value after fixed code terminates: " << accumulator << "\n";
}