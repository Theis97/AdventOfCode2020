#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cout << "Incorrect number of arguments\n";
        std::cout << "Usage: " << argv[0] << " <steps right> <steps down>\n";
        return 0;
    }

    int stepsRight = std::stoi(argv[1]);
    int stepsDown = std::stoi(argv[2]);

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
    int column = stepsRight;
    int row = 1;
    while (std::getline(inputFile, line)) {
        if (row % stepsDown == 0) {
            if (line[column] == '#') {
                treeCount++;
            }
            column = (column + stepsRight) % width;
        }
        row++;
    }

    std::cout << "# Trees encountered: " << treeCount << "\n";
}