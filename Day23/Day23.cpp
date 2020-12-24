#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

const int numMoves = 10000000;
const int totalCups = 1000000;

int main() {
    std::ifstream inputFile;
    inputFile.open("day23.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string line;
    std::getline(inputFile, line);
    std::vector<int> cups(totalCups + 1); // extra one because we ignore index 0

    for (int i = 0; i < line.length() - 1; i++) {
        int cup = line[i] - '0';
        int nextCup = line[i + 1] - '0';
        cups[cup] = nextCup;
    }

    if (totalCups > line.length()) {
        // We're assuming that 9 is the largest label we're given
        cups[line[line.size()-1] - '0'] = 10;
        for (int i = 10; i < totalCups; i++) {
            cups[i] = i + 1;
        }
        cups[totalCups] = line[0] - '0';
    }
    else {
        cups[line[line.size() - 1] - '0'] = line[0] - '0';
    }

    int currentCup = line[0] - '0';
    for (int i = 0; i < numMoves; i++) {
        int minCup = 1;
        int maxCup = totalCups;

        int movingCupOne = cups[currentCup];
        minCup = movingCupOne == minCup ? minCup + 1 : minCup;
        maxCup = movingCupOne == maxCup ? maxCup - 1 : maxCup;
        int movingCupTwo = cups[movingCupOne];
        minCup = movingCupTwo == minCup ? minCup + 1 : minCup;
        maxCup = movingCupTwo == maxCup ? maxCup - 1 : maxCup;
        int movingCupThree = cups[movingCupTwo];
        minCup = movingCupThree == minCup ? minCup + 1 : minCup;
        maxCup = movingCupThree == maxCup ? maxCup - 1 : maxCup;

        cups[currentCup] = cups[movingCupThree];

        int destination = currentCup - 1;
        while (destination == movingCupOne || destination == movingCupTwo || destination == movingCupThree) {
            destination--;
            if (destination < minCup) {
                destination = maxCup;
            }
        }
        if (destination < minCup) {
            destination = maxCup;
        }

        cups[movingCupThree] = cups[destination];
        cups[destination] = movingCupOne;
        cups[movingCupOne] = movingCupTwo;
        cups[movingCupTwo] = movingCupThree;

        currentCup = cups[currentCup];
    }
    std::cout << cups[1] << " and " << cups[cups[1]] << "\n";
    std::cout << "Answer is " << (long long)cups[1] * (long long)cups[cups[1]] << "\n";
}