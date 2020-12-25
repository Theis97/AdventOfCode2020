#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

const int days = 100;

std::vector<std::pair<int, int>> GetNeighbors(std::pair<int, int> hex) {
	std::vector<std::pair<int, int>> neighbors;
	neighbors.reserve(6);
	neighbors.push_back(std::pair<int, int>(hex.first + 2, hex.second));
	neighbors.push_back(std::pair<int, int>(hex.first - 2, hex.second));
	neighbors.push_back(std::pair<int, int>(hex.first - 1, hex.second - 1));
	neighbors.push_back(std::pair<int, int>(hex.first - 1, hex.second + 1));
	neighbors.push_back(std::pair<int, int>(hex.first + 1, hex.second - 1));
	neighbors.push_back(std::pair<int, int>(hex.first + 1, hex.second + 1));
	return neighbors;
}

int main() {
	std::ifstream inputFile;
	inputFile.open("day24.txt");
	if (!inputFile.is_open()) {
		std::cout << "File could not be opened.\n";
		return 0;
	}

	// (0,0) is the reference hex
	// Here is where you end up when moving in each direction from the reference tile:
	// East: (0,2)
	// West: (-2,0)
	// Northeast: (1,1)
	// Northwest: (-1,1)
	// Southeast: (1,-1)
	// Southwest: (-1,-1)
	// So East/North are the positive directions and West/South are the negative directions.
	// Moving in any of the 6 directions will change the coordinates by 2.

	std::set<std::pair<int, int>> flippedHexes;
	std::string line;
	while (std::getline(inputFile, line)) {

		std::pair<int, int> position;
		for (int i = 0; i < line.length(); i++) {
			bool ordinalMove = false;
			switch (line[i]) {
			case 'e':
				position.first += 2;
				break;
			case 'w':
				position.first -= 2;
				break;
			case 'n':
				ordinalMove = true;
				position.second++;
				break;
			case 's':
				ordinalMove = true;
				position.second--;
				break;
			}

			if (ordinalMove) {
				i++;
				position.first += line[i] == 'e' ? 1 : -1;
			}
		}

		if (flippedHexes.count(position) == 1) {
			flippedHexes.erase(position);
		}
		else {
			flippedHexes.insert(position);
		}
	}
	std::cout << flippedHexes.size() << " tiles are black side up after installation\n";

	for (int i = 0; i < days; i++) {
		std::vector<std::pair<int, int>> hexesToCheck;
		for (auto &hex : flippedHexes) {
			hexesToCheck.push_back(hex);
			std::vector<std::pair<int, int>> neighbors = GetNeighbors(hex);
			hexesToCheck.insert(hexesToCheck.end(), neighbors.begin(), neighbors.end());
		}

		std::set<std::pair<int, int>> newFlippedHexes;
		for (auto &hex : hexesToCheck) {
			int activeNeighbors = 0;
			std::vector<std::pair<int, int>> neighbors = GetNeighbors(hex);
			for (auto &neighbor : neighbors) {
				if (flippedHexes.count(neighbor) == 1) {
					activeNeighbors++;
				}
			}
			if (flippedHexes.count(hex) == 1 && (activeNeighbors > 0 && activeNeighbors <= 2)) {
				newFlippedHexes.insert(hex);
			}
			else if (flippedHexes.count(hex) == 0 && activeNeighbors == 2) {
				newFlippedHexes.insert(hex);
			}
		}
		flippedHexes = newFlippedHexes;
		std::cout << "Day " << i + 1 << ": " << flippedHexes.size() << "\n";
	}

	std::cout << flippedHexes.size() << " tiles are black side up after " << days << " days on exhibition\n";
}