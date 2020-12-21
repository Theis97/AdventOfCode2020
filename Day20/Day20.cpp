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

const int monsterWidth = 20;
const int monsterHeight = 3;
const std::set<std::pair<int, int>> seaMonsterPattern{
    {0,18},
    {1,0},
    {1,5},
    {1,6},
    {1,11},
    {1,12},
    {1,17},
    {1,18},
    {1,19},
    {2,1},
    {2,4},
    {2,7},
    {2,10},
    {2,13},
    {2,16}
};

struct Tile {
    Tile(int i, std::vector<std::string> b) : id(i), borders(b){};

    int id;

    // 0: top border
    // 1: bottom border
    // 2: left border
    // 3: right border
    std::vector<std::string> borders;

    std::vector<std::vector<char>> image;
};

void Flip2DVector(std::vector<std::vector<char>>& v) {
    for (auto& row : v) {
        std::reverse(row.begin(), row.end());
    }
}

void Rotate2DVector(std::vector<std::vector<char>> &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            std::swap(v[i][j], v[j][i]);
        }
    }
    Flip2DVector(v);
}

// Rotates the tile 90 degrees clockwise
void RotateTile(Tile* t) {
    Rotate2DVector(t->image);
    std::swap(t->borders[0], t->borders[3]); // right side
    std::swap(t->borders[0], t->borders[1]); // bottom side
    std::swap(t->borders[0], t->borders[2]); // remaining sides
    std::reverse(t->borders[1].begin(), t->borders[1].end()); // fix bottom
    std::reverse(t->borders[0].begin(), t->borders[0].end()); // fix top
}

void FlipTile(Tile* t) {
    Flip2DVector(t->image);
    std::reverse(t->borders[0].begin(), t->borders[0].end());
    std::reverse(t->borders[1].begin(), t->borders[1].end());
    std::swap(t->borders[2], t->borders[3]);
}

std::pair<bool, int> FindSeaMonsters(std::vector<std::vector<char>> image) {
    bool monsterFound = true;
    bool success = false;
    std::set<std::pair<int, int>> monsterParts;
    for (int i = 0; i < image.size() - monsterHeight; i++) {
        for (int j = 0; j < image[0].size() -  monsterWidth; j++) {
            for (auto& coord : seaMonsterPattern) {
                if (image[i + coord.first][j + coord.second] != '#') {
                    monsterFound = false;
                    break;
                }
            }
            if (monsterFound) {
                success = true;
                for (int k = i; k < i + monsterHeight; k++) {
                    for (int l = j; l < j + monsterWidth; l++) {
                        if (image[k][l] == '#' && seaMonsterPattern.count(std::pair<int, int>(k - i,l - j)) == 1) {
                            monsterParts.insert(std::pair<int, int>(k, l));
                        }
                    }
                }
            }
            else {
                monsterFound = true;
            }
        }
    }

    int roughness = 0;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[0].size(); j++) {
            if (image[i][j] == '#' && monsterParts.count(std::pair<int, int>(i, j)) != 1) {
                roughness++;
            }
        }
    }

    return std::pair<int, int>(success, roughness);
}

void AddToImage(std::vector<std::vector<char>>& image, Tile* tile, bool startNewRow) {
    int startX = -1;
    int startY = -1;
    if (startNewRow) {
        startY = image.size();
        for (int i = 0; i < tile->image.size(); i++) {
            image.push_back(std::vector<char>(tile->image.size()));
        }
        startX = 0;
    }
    else {
        startY = image.size() - tile->image.size();
        startX = image[startY].size();
        for (int i = startY; i < image.size(); i++) {
            image[i].resize(image[i].size() + tile->image.size());
        }
    }

    for (int i = 0; i < tile->image.size(); i++) {
        for (int j = 0; j < tile->image.size(); j++) {
            image[startY + i][startX + j] = tile->image[i][j];
        }
    }
}

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
        
        std::vector<std::vector<char>> image;
        std::vector<std::string> borders;
        std::string leftBorder = "";
        std::string rightBorder = "";
        for (int i = 0; i < tileSize; i++) {
            std::getline(inputFile, line);
            if (i == 0 || i == tileSize - 1) {
                borders.push_back(line);
            }
            else {
                image.push_back(std::vector<char>());
                for (int j = 1; j < tileSize - 1; j++) {
                    image[i-1].push_back(line[j]);
                }
            }
            leftBorder += line[0];
            rightBorder += line[tileSize - 1];
        }
        borders.push_back(leftBorder);
        borders.push_back(rightBorder);

        tiles.push_back(std::make_unique<Tile>(id, borders));
        tiles.back().get()->image = image;
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


    std::vector<std::vector<char>> finalImage;

    // Choose an arbitrary corner for the top left, rotate it such that its top and
    // left borders don't match any other tile's
    Tile* topLeftCorner = corners[0];
    while (tilesWithEdge[topLeftCorner->borders[0]].size() != 1 
        || tilesWithEdge[topLeftCorner->borders[2]].size() != 1) {
        RotateTile(topLeftCorner);
    }
    AddToImage(finalImage, topLeftCorner, true);

    Tile* prevTile = topLeftCorner;
    Tile* rowStart = topLeftCorner;
    bool firstLoop = true;
    while (tilesWithEdge[prevTile->borders[3]].size() != 1
        || tilesWithEdge[prevTile->borders[1]].size() != 1) {

        if (!firstLoop) {
            std::set<Tile*> s = tilesWithEdge[rowStart->borders[1]];
            s.erase(rowStart);
            Tile* nextTile = *s.begin();

            bool orientationFound = false;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 4; j++) {
                    if (rowStart->borders[1] == nextTile->borders[0]) {
                        orientationFound = true;
                        break;
                    }
                    RotateTile(nextTile);
                }
                if (orientationFound) {
                    break;
                }
                FlipTile(nextTile);
            }
            AddToImage(finalImage, nextTile, true);
            rowStart = nextTile;
            prevTile = rowStart;
        }
        while (tilesWithEdge[prevTile->borders[3]].size() != 1) {
            std::set<Tile*> s = tilesWithEdge[prevTile->borders[3]];
            s.erase(prevTile);
            Tile* nextTile = *s.begin();

            bool orientationFound = false;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 4; j++) {
                    if (prevTile->borders[3] == nextTile->borders[2]) {
                        orientationFound = true;
                        break;
                    }
                    RotateTile(nextTile);
                }
                if (orientationFound) {
                    break;
                }
                FlipTile(nextTile);
            }
            AddToImage(finalImage, nextTile, false);
            prevTile = nextTile;
        }
        firstLoop = false;
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << "\n";
            for (auto& row : finalImage) {
                for (auto& c : row) {
                    std::cout << c;
                }
                std::cout << "\n";
            }
            std::pair<bool, int> result = FindSeaMonsters(finalImage);
            if (result.first) {
                std::cout << "Roughness: " << result.second << "\n";
            }
            else {
                std::cout << "No monsters found in this orientation\n";
            }
            Rotate2DVector(finalImage);
        }
        Flip2DVector(finalImage);
    }
}