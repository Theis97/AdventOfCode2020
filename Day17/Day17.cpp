#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <set>
#include <vector>

std::vector<std::tuple<int, int, int>> GetNeighbors3D(std::tuple<int, int, int> cube) {
    int x = std::get<0>(cube);
    int y = std::get<1>(cube);
    int z = std::get<2>(cube);

    std::vector<std::tuple<int, int, int>> neighbors;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            for (int k = z - 1; k <= z + 1; k++) {
                if (i != x || j != y || k != z) {
                    neighbors.push_back(std::tuple<int, int, int>(i,j,k));
                }
            }
        }
    }
    return neighbors;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day17.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    const int totalRounds = 6;
    std::set<std::tuple<int, int, int>> activeCubes;

    std::string line;
    int lineNum = 0;
    while (std::getline(inputFile, line)) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '#') {
                activeCubes.insert(std::tuple<int, int, int>(i, lineNum, 0));
            }
        }
        lineNum++;
    }

    for (int i = 0; i < totalRounds; i++) {
        std::set<std::tuple<int, int, int>> cubesToCheck;
        for (auto &cube : activeCubes) {
            std::vector<std::tuple<int, int, int>> neighbors = GetNeighbors3D(cube);
            for (auto &neighbor : neighbors) {
                cubesToCheck.insert(neighbor);
            }
        }

        // check all of those cubes, shoving any that become/stay active into a new active set
        std::set<std::tuple<int, int, int>> nextActive;
        for (auto &cube : cubesToCheck) {
            std::vector<std::tuple<int, int, int>> neighbors = GetNeighbors3D(cube);
            int activeNeighbors = 0;
            for (auto& neighbor : neighbors) {
                if (activeCubes.count(neighbor)) {
                    activeNeighbors++;
                }
            }
            if (activeNeighbors == 3 || (activeCubes.count(cube) && activeNeighbors == 2)) {
                nextActive.insert(cube);
            }
        }

        activeCubes = nextActive;
    }

    std::cout << "Total active cubes left: " << activeCubes.size() << "\n";
}