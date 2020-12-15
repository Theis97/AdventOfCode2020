#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


int CountCombinations(std::vector<int> chunk) {
    // TODO
    return -1;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day10.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::vector<int> adaptors;

    std::string line;
    while (std::getline(inputFile, line)) {
        adaptors.push_back(std::stoi(line));
    }

    std::sort(adaptors.begin(), adaptors.end());

    int prevAdaptor = 0;
    int oneDiffCount = 0;
    int threeDiffCount = 0;
    for (int i = 0; i < adaptors.size(); i++) {
        int adaptor = adaptors[i];
        int difference = adaptor - prevAdaptor;
        if (difference == 1) {
            oneDiffCount++;
        }
        else if (difference == 3) {
            threeDiffCount++;
        }
        prevAdaptor = adaptor;
    }


    std::cout << "There are " << oneDiffCount << " 1-gaps and " << threeDiffCount + 1 << " 3-gaps\n";
    std::cout << "Answer is: " << oneDiffCount * (threeDiffCount + 1) << "\n";
}