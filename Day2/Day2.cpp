#include <vector>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    
    std::ifstream inputFile;
    inputFile.open("day2.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    int oldValidCount = 0;
    int newValidCount = 0;

    std::string line;
    while (std::getline(inputFile, line)) {

        size_t dashPos = line.find('-');
        size_t colonPos = line.find(':');

        int lowerNum = std::stoi(line.substr(0, dashPos));
        int upperNum = std::stoi(line.substr(dashPos + 1, colonPos - dashPos - 3));
        char letter = line[colonPos - 1];
        std::string password = line.substr(colonPos + 2);

        int letterCount = 0;
        for (int i = 0; i < password.size(); i++) {
            if (password[i] == letter) {
                letterCount++;
            }
        }

        if (letterCount >= lowerNum && letterCount <= upperNum) {
            oldValidCount++;
        }

        char first = password[lowerNum - 1];
        char second = password[upperNum - 1];
        if (first == letter && second != letter || first != letter && second == letter) {
            newValidCount++;
        }
    }

    std::cout << "# Valid passwords (old policy): " << oldValidCount << "\n";
    std::cout << "# Valid passwords (new policy): " << newValidCount << "\n";
    inputFile.close();
}