#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
#include "../Utilities/StringUtils.h"

const int tileSize = 10;

struct Tile {
    Tile(int i, std::vector<std::string> b) : id(i), borders(b) {};
    int id;
    std::vector<std::string> borders;
};

int main() {
    std::ifstream inputFile;
    inputFile.open("day20.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::vector<std::unique_ptr<Tile>> tiles;
    std::map<std::string, std::set<Tile*>> tilesWithEdge;

    std::string line;
    while (std::getline(inputFile, line)) {
        int id = std::stoi(TokenizeString(line, ' ')[1]);
        
        std::vector<std::string> borders;
        std::string leftBorder = "";
        std::string rightBorder = "";
        for (int i = 0; i < tileSize; i++) {
            std::getline(inputFile, line);
            if (i == 0 || i == tileSize - 1) {
                borders.push_back(line);
            }
            leftBorder += line[0];
            rightBorder += line[tileSize - 1];
        }
        borders.push_back(leftBorder);
        borders.push_back(rightBorder);

        tiles.push_back(std::make_unique<Tile>(id, borders));
        for (auto &border : borders) {
            std::set<Tile*> s = tilesWithEdge[border];
            s.insert(tiles.back().get());
            tilesWithEdge[border] = s;

            std::string flipped(border);
            std::reverse(flipped.begin(), flipped.end());
            s = tilesWithEdge[flipped];
            s.insert(tiles.back().get());
            tilesWithEdge[flipped] = s;
        }

        std::getline(inputFile, line);
    }

    std::vector<Tile*> corners;
    for (auto &tile : tiles) {
        int uniqueBorders = 0;
        for (auto &border : tile->borders) {
            std::set<Tile*> s = tilesWithEdge[border];
            if (s.size() == 1) {
                uniqueBorders++;
            }
        }
        if (uniqueBorders == 2) {
            corners.push_back(tile.get());
        }
    }

    long long cornerProduct = 1;
    for (auto corner : corners) {
        cornerProduct *= corner->id;
    }

    std::cout << "Product of corner tile ids: " << cornerProduct << "\n";
}