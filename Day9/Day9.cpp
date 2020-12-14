#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>

int main() {

    std::ifstream inputFile;
    inputFile.open("day9.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }
    
    const int preambleSize = 25;
    int targetValue = -1;
    std::deque<long long> inputOrderPrevValues;
    std::vector<long long> fullInput;
  
    // read in preamble
    std::string line;
    for (int i = 0; i < preambleSize; i++) {
        std::getline(inputFile, line);
        long long value = std::stoll(line);
        inputOrderPrevValues.push_back(value);
        fullInput.push_back(value);
    }

    while (std::getline(inputFile, line)) {
        long long value = std::stoll(line);
        inputOrderPrevValues.push_back(value);
        fullInput.push_back(value);

        std::priority_queue<long long> bigger;
        std::priority_queue<long long, std::vector<long long>, std::greater<int>> smaller;

        for (auto &val : inputOrderPrevValues) {
            bigger.push(val);
            smaller.push(val);
        }

        bool found = false;
        while (true) {
            long long low = smaller.top();
            long long high = bigger.top();
            if (low >= high) {
                break;
            }
            long long sum = low + high;
            if (sum == value) {
                found = true;
                break;
            }
            else if (sum > value) {
                bigger.pop();
            }
            else {
                smaller.pop();
            }
        }

        if (found) {
            inputOrderPrevValues.pop_front();
        }
        else {
            targetValue = value;
            std::cout << "The first value that breaks the rule is " << targetValue << "\n";
            break;
        }
    }

    bool weaknessFound = false;
    int rangeTop = fullInput.size() - 2;
    int rangeBottom = rangeTop - 1;
    int largest = fullInput[rangeTop] > fullInput[rangeBottom] ? rangeTop : rangeBottom;
    int smallest = fullInput[rangeTop] > fullInput[rangeBottom] ? rangeBottom : rangeTop;;
    long long sum = fullInput[rangeTop] + fullInput[rangeBottom];
    while (!weaknessFound) {
        if (sum == targetValue) {
            weaknessFound = true;
        }
        else if (sum > targetValue) {
            sum -= fullInput[rangeTop];
            rangeTop--;
            if (rangeTop == rangeBottom) {
                // there needs to be at least two different numbers
                rangeBottom--;
                sum += fullInput[rangeBottom];
            }
        }
        else {
            rangeBottom--;
            sum += fullInput[rangeBottom];
        }
    }
    std::vector<long long> indexRange(fullInput.begin() + rangeBottom, fullInput.begin() + rangeTop + 1);
    std::sort(indexRange.begin(), indexRange.end());

    std::cout << "Encryption weakness is: " << indexRange[0] + indexRange[indexRange.size() - 1] << "\n";
}