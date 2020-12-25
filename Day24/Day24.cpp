#include <iostream>
#include <fstream>
#include <string>
#include <set>

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
}