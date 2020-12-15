#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int CountAdjacentAlongHorizontal(std::vector<std::vector<char>>& board, int startX, int startY, bool lookLeft) {
    int direction = 1;
    int boundary = board[0].size();
    if (lookLeft) {
        direction = -1;
        boundary = -1;
    }

    int count = 0;
    int topIndex = startY - 1;
    int bottomIndex = startY + 1;
    bool topFound = false;
    bool midFound = false;
    bool bottomFound = false;

    for (int k = startX + direction; k != boundary; k += direction) {
        if (!topFound && topIndex >= 0) {
            if (board[topIndex][k] == '#') {
                count++;
            }

            if (board[topIndex][k] != '.') {
                topFound = true;
            }
        }
        if (!midFound) {
            if (board[startY][k] == '#') {
                count++;
            }

            if (board[startY][k] != '.') {
                midFound = true;
            }
        }
        if (!bottomFound && bottomIndex < board.size()) {
            if (board[bottomIndex][k] == '#') {
                count++;
            }

            if (board[bottomIndex][k] != '.') {
                bottomFound = true;
            }
        }
        if (topFound && midFound && bottomFound) {
            break;
        }
        topIndex--;
        bottomIndex++;
    }

    return count;
}

int main(int argc, char* argv[]) {
    bool partTwoRules = false;

    if (argc > 1) {
        std::cout << argv[0] << "\n";
        partTwoRules = true;
    }

    std::ifstream inputFile;
    inputFile.open("day11.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::vector<std::vector<char>> ferryDeck;
    std::vector<std::vector<char>> nextFerryDeck;

    std::string line;
    while (std::getline(inputFile, line)) {
        ferryDeck.push_back(std::vector<char>());
        nextFerryDeck.push_back(std::vector<char>());
        for (int i = 0; i < line.length(); i++) {
            ferryDeck.back().push_back(line[i]);
            nextFerryDeck.back().push_back(line[i]);
        }
    }

    int width = ferryDeck[0].size();
    int height = ferryDeck.size();

    bool stateChanged = true;
    while (stateChanged) {
        stateChanged = false;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int adjacentCount = 0;

                if (partTwoRules) {
                    // look left
                    adjacentCount += CountAdjacentAlongHorizontal(ferryDeck, j, i, true);
                    // look right
                    adjacentCount += CountAdjacentAlongHorizontal(ferryDeck, j, i, false);
                    // look directly up
                    for (int k = i - 1; k >= 0; k--) {
                        if (ferryDeck[k][j] == '#') {
                            adjacentCount++;
                            break;
                        }
                        else if (ferryDeck[k][j] == 'L') {
                            break;
                        }
                    }
                    // look directly down
                    for (int k = i + 1; k < height; k++) {
                        if (ferryDeck[k][j] == '#') {
                            adjacentCount++;
                            break;
                        }
                        else if (ferryDeck[k][j] == 'L') {
                            break;
                        }
                    }
                }
                else {
                    int leftBound = j == 0 ? 0 : j - 1;
                    int rightBound = j == width - 1 ? width - 1 : j + 1;
                    int topBound = i == 0 ? 0 : i - 1;
                    int bottomBound = i == height - 1 ? height - 1 : i + 1;

                    for (int k = topBound; k <= bottomBound; k++) {
                        for (int l = leftBound; l <= rightBound; l++) {
                            if (ferryDeck[k][l] == '#' && (k != i || l != j)) {
                                adjacentCount++;
                            }
                        }
                    }
                }

                int crowdingPoint = partTwoRules ? 5 : 4;
                if (ferryDeck[i][j] == 'L' && adjacentCount == 0) {
                    nextFerryDeck[i][j] = '#';
                    stateChanged = true;
                } else if (ferryDeck[i][j] == '#' && adjacentCount >= crowdingPoint) {
                    nextFerryDeck[i][j] = 'L';
                    stateChanged = true;
                }
            }
        }
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                ferryDeck[i][j] = nextFerryDeck[i][j];
            }
        }
    }

    int stableSeatedCount = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (ferryDeck[i][j] == '#') {
                stableSeatedCount++;
            }
        }
    }

    std::cout << "There are " << stableSeatedCount << " occupied seats\n";
}