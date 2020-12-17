#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../Utilities/StringUtils.h"


// TODO: Optimize the game simulation or figure out a way to compute 
// what number will be said on an arbitrary turn directly.
int main() {

    std::ifstream inputFile;
    inputFile.open("day15.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string line;
    std::getline(inputFile, line);
    std::vector<std::string> tokens = TokenizeString(line, ',');

    std::vector<int> startingNumbers;
    for (auto &token : tokens) {
        startingNumbers.push_back(std::stoi(token));
    }

    const int turnMax = 2020;
    // first is previous last turn spoken, second is most recent turn spoken
    std::map<int, std::pair<int, int>> lastTurnsSpoken;
    int turnCount = 1;
    int previousNum = -1;
    
    while (turnCount <= startingNumbers.size()) {
        lastTurnsSpoken[startingNumbers[turnCount-1]] = std::pair<int, int>(-1, turnCount);
        previousNum = startingNumbers[turnCount-1];
        turnCount++;
    }

    for (; turnCount <= turnMax; turnCount++) {
        if (turnCount % 100000 == 0) {
            std::cout << turnCount << "\n";
        }
        std::pair<int, int> lastTurn = lastTurnsSpoken[previousNum];
        if (lastTurn.first == -1) {
            int previousLastTurn = lastTurnsSpoken.find(0) == lastTurnsSpoken.end() ? -1 : lastTurnsSpoken[0].second;
            lastTurnsSpoken[0] = std::pair<int, int>(previousLastTurn, turnCount);
            previousNum = 0;
        }
        else {
            int n = turnCount-1 - lastTurn.first;
            int previousLastTurn = lastTurnsSpoken.find(n) == lastTurnsSpoken.end() ? -1 : lastTurnsSpoken[n].second;
            lastTurnsSpoken[n] = std::pair<int, int>(previousLastTurn, turnCount);
            previousNum = n;
        }
    }

    std::cout <<  turnMax << "th number spoken: " << previousNum << "\n";
}