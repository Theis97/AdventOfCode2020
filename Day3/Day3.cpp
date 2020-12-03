#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::ifstream inputFile;
    inputFile.open("day3.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string line;
    std::getline(inputFile, line);
    int width = line.length();
    int treeCount = 0;
    int column = 3;
    while (std::getline(inputFile, line)) {
        if (line[column] == '#') {
            treeCount++;
        }
        column = (column + 3) % width;
    }

    std::cout << "# Trees encountered: " << treeCount << "\n";
}