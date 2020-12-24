#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int RemoveNext(std::vector<int>& v, int value) {
    auto it = std::find(v.begin(), v.end(), value);
    if (it == v.end() - 1) {
        int nextVal = v[0];
        v.erase(v.begin());
        return nextVal;
    }
    int nextVal = *++it;
    v.erase(it);
    return nextVal;
}

const int numMoves = 100;

int main() {
    std::ifstream inputFile;
    inputFile.open("day23.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string line;
    std::getline(inputFile, line);
    std::vector<int> cups;
    for (auto c : line) {
        cups.push_back(c - '0');
    }

    int currentCup = cups[0];
    for (int i = 0; i < numMoves; i++) {
        std::vector<int> removedCups;
        for (int j = 0; j < 3; j++) {
            removedCups.push_back(RemoveNext(cups, currentCup));
        }

        int destinationCup = currentCup - 1;
        int maxCupValue = *std::max_element(cups.begin(), cups.end());
        int minCupValue = *std::min_element(cups.begin(), cups.end());
        while ((std::find(removedCups.begin(), removedCups.end(), destinationCup) != removedCups.end()) && destinationCup > 0) {
            destinationCup--;
        }
        if (destinationCup < minCupValue) {
            destinationCup = maxCupValue;
        }
        auto destination = std::find(cups.begin(), cups.end(), destinationCup);

        destination++;
        if (destination == cups.end()) {
            destination = cups.begin();
        }
        cups.insert(destination, removedCups.begin(), removedCups.end());

        auto currentCupPos = std::find(cups.begin(), cups.end(), currentCup);
        currentCupPos++;
        if (currentCupPos == cups.end()) {
            currentCup = cups[0];
        }
        else {
            currentCup = *currentCupPos;
        }
    }

    for (auto cup : cups) {
        std::cout << cup << ", ";
    }
    std::cout << "\n";
}