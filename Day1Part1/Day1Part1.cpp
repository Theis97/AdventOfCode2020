#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#define TARGET_SUM 2020

int main()
{
    std::vector<int> input;

    std::ifstream inputFile;
    inputFile.open("day1.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(std::stoi(line));
    }
    inputFile.close();

    std::sort(input.begin(), input.end());

    int frontIdx = 0;
    int backIdx = input.size() - 1;
    bool isSuccessful = false;

    while (frontIdx < backIdx) {
        int sum = input[frontIdx] + input[backIdx];

        if (sum == TARGET_SUM) {
            isSuccessful = true;
            std::cout << "The answer is: " << input[frontIdx] << " * " << input[backIdx] << " = " << input[frontIdx] * input[backIdx] << "\n";
            break;
        }
        else if (sum < TARGET_SUM) {
            frontIdx++;
        }
        else {
            backIdx--;
        }
    }

    if (!isSuccessful) {
        std::cout << "No such numbers were found\n";
    }
}
