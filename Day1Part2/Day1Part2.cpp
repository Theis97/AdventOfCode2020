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

    bool isSuccessful = false;

    // Brute force it
    // I may want to try implementing a more sophisticated solution in the future
    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            for (int k = j + 1; k < input.size(); k++) {
                if (input[i] + input[j] + input[k] == TARGET_SUM) {
                    isSuccessful = true;
                    std::cout << "The answer is: " << input[i] * input[j] * input[k] << "\n";
                    break;
                }
            }
            if (isSuccessful) {
                break;
            }
        }
        if (isSuccessful) {
            break;
        }
    }

    if (!isSuccessful) {
        std::cout << "No such numbers were found\n";
    }
}