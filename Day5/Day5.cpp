#include <iostream>
#include <fstream>
#include <string>

int FindPosition(std::string line, int total, int start, int end, char takeLowerIndicator) {
    int min = 0;
    int max = total - 1;
    int range = total;

    for (int i = start; i < end; i++) {
        range = max - min + 1;
        if (line[i] == takeLowerIndicator) {
            max -= range / 2;
        }
        else {
            min += range / 2;
        }
    }

    if (line[end] == takeLowerIndicator) {
        return min;
    }
    else {
        return max;
    }
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day5.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    const int totalRows = 128;
    const int totalColumns = 8;

    std::string line;
    int highestSeatId = INT_MIN;
    int lowestSeatId = INT_MAX;
    int actualSeatIdSum = 0;
    while (std::getline(inputFile, line)) {
        int row = FindPosition(line, totalRows, 0, 6, 'F');
        int column = FindPosition(line, totalColumns, 7, 9, 'L');

        int seatId = (row * 8) + column;
        actualSeatIdSum += seatId;
        highestSeatId = seatId > highestSeatId ? seatId : highestSeatId;
        lowestSeatId = seatId < lowestSeatId ? seatId : lowestSeatId;
    }
    int expectedSeatSum = ((highestSeatId * (highestSeatId + 1))/2) - ((lowestSeatId * (lowestSeatId - 1)) / 2);
    int yourSeatId = expectedSeatSum - actualSeatIdSum;

    std::cout << "Highest seat number is: " << highestSeatId << "\n";
    std::cout << "Lowest seat number is: " << lowestSeatId << "\n";
    std::wcout << "Your seat number is: " << yourSeatId << "\n";
}