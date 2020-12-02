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

    int validCount = 0;

    std::string line;
    while (std::getline(inputFile, line)) {

        size_t dashPos = line.find('-');
        size_t colonPos = line.find(':');

        int lowerBound = std::stoi(line.substr(0, dashPos));
        int upperBound = std::stoi(line.substr(dashPos + 1, colonPos - dashPos - 3));
        char letter = line[colonPos - 1];
        std::string password = line.substr(colonPos + 2);

        int letterCount = 0;
        for (int i = 0; i < password.size(); i++) {
            if (password[i] == letter) {
                letterCount++;
            }
        }

        if (letterCount >= lowerBound && letterCount <= upperBound) {
            validCount++;
        }
    }

    std::cout << "# Valid passwords: " << validCount << "\n";
    inputFile.close();
}