#include <iostream>
#include <fstream>
#include <string>
#include <map>

void PartOneInstructions(char action, int value, int& eastWestPos, int& northSouthPos, int& rotation) {
    switch (action) {
    case 'N':
        northSouthPos += value;
        break;
    case 'S':
        northSouthPos -= value;
        break;
    case 'E':
        eastWestPos += value;
        break;
    case 'W':
        eastWestPos -= value;
        break;
    case 'L':
        // counter-clockwise
        if (rotation - value < 0) {
            rotation = (rotation + 360 - value) % 360;
        }
        else {
            rotation = rotation - value;
        }
        break;
    case 'R':
        // clockwise
        rotation = (rotation + value) % 360;
        break;
    case 'F':
        if (rotation == 0) {
            eastWestPos += value;
        }
        else if (rotation == 90) {
            northSouthPos -= value;
        }
        else if (rotation == 180) {
            eastWestPos -= value;
        }
        else if (rotation == 270) {
            northSouthPos += value;
        }
        break;
    }
}

char GetNewDirection(char startDirection, int rotDegrees) {
    const std::map<char, char> forwardRotationCycle{ {'E', 'S'}, {'S', 'W'}, {'W', 'N'}, {'N', 'E'} };
    const std::map<char, char> backwardRotationCycle{ {'E', 'N'}, {'N', 'W'}, {'W', 'S'}, {'S', 'E'} };

    int cycleCount = std::abs(rotDegrees / 90);
    std::map<char, char> cycle = rotDegrees >= 0 ? forwardRotationCycle : backwardRotationCycle;
    char direction = startDirection;
    for (int i = 0; i < cycleCount; i++) {
        direction = cycle[direction];
    }
    return direction;
}

void RotateWaypoint(int rotDegrees, int& eastWestPos, int& northSouthPos) {
    int newEastWest = 0;
    int newNorthSouth = 0;
    char currDir = eastWestPos >= 0 ? 'E' : 'W';
    char newDir = GetNewDirection(currDir, rotDegrees);
    switch (newDir) {
    case 'E':
        newEastWest = std::abs(eastWestPos);
        break;
    case 'W':
        newEastWest = -std::abs(eastWestPos);
        break;
    case 'N':
        newNorthSouth = std::abs(eastWestPos);
        break;
    case 'S':
        newNorthSouth = -std::abs(eastWestPos);
        break;
    }

    currDir = northSouthPos>= 0 ? 'N' : 'S';
    newDir = GetNewDirection(currDir, rotDegrees);
    switch (newDir) {
    case 'E':
        newEastWest = std::abs(northSouthPos);
        break;
    case 'W':
        newEastWest = -std::abs(northSouthPos);
        break;
    case 'N':
        newNorthSouth = std::abs(northSouthPos);
        break;
    case 'S':
        newNorthSouth = -std::abs(northSouthPos);
        break;
    }

    eastWestPos = newEastWest;
    northSouthPos = newNorthSouth;
}

int main() {

    const bool partOne = false;

    std::ifstream inputFile;
    inputFile.open("day12.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    // East +; West -
    int eastWestPos = 0;
    // North +; South -
    int northSouthPos = 0;
    // East == 0
    // South == 90
    // West == 180
    // North == 270
    int rotation = 0;

    int waypointOffsetEW = 10;
    int waypointOffsetNS = 1;

    std::string line;
    while (std::getline(inputFile, line)) {
        char action = line[0];
        int value = std::stoi(line.substr(1));
        if (partOne) {
            PartOneInstructions(action, value, eastWestPos, northSouthPos, rotation);
        }
        else {
            if (action != 'R' && action != 'L' && action != 'F') {
                PartOneInstructions(action, value, waypointOffsetEW, waypointOffsetNS, rotation);
            }
            else if (action == 'R') {
                RotateWaypoint(value, waypointOffsetEW, waypointOffsetNS);
            }
            else if (action == 'L') {
                RotateWaypoint(-value, waypointOffsetEW, waypointOffsetNS);
            }
            else if (action == 'F') {
                for (int i = 0; i < value; i++) {
                    eastWestPos += waypointOffsetEW;
                    northSouthPos += waypointOffsetNS;
                }
            }
        }
    }
    int distance = std::abs(eastWestPos) + std::abs(northSouthPos);
    std::cout << "The ship is " << distance << " units away from its start point\n";
}