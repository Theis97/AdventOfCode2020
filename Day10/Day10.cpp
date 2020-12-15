#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


double ComputeCombos(int oneDiffCount) {
    // This assumes that there are no more than 5 differences of one in a row
    if (oneDiffCount == 1) {
        return 1.0;
    }
    if (oneDiffCount <= 3 ) {
        return 2.0 * ((double)oneDiffCount - 1);
    }
    return pow(2.0, oneDiffCount - 1) - 1;
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
    int consecutiveOnes = 0;
    double numCombinations = 1;
    for (int i = 0; i < adaptors.size(); i++) {
        int adaptor = adaptors[i];
        int difference = adaptor - prevAdaptor;
        if (difference == 1) {
            oneDiffCount++;
            consecutiveOnes++;
        }
        else if (difference == 3) {
            threeDiffCount++;
            if (consecutiveOnes != 0) {
                numCombinations *= ComputeCombos(consecutiveOnes);
            }
            consecutiveOnes = 0;
        }
        prevAdaptor = adaptor;
    }

    if (consecutiveOnes != 0) {
        numCombinations *= ComputeCombos(consecutiveOnes);
    }
    
    std::cout << "There are " << oneDiffCount << " 1-gaps and " << threeDiffCount + 1 << " 3-gaps\n";
    std::cout << "Answer is: " << oneDiffCount * (threeDiffCount + 1) << "\n";

    std::cout << "There are " << (long long)numCombinations << " distinct arrangements of adaptors\n";
}