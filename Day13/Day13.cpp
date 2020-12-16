#include <iostream>
#include <fstream>
#include <string>
#include "../Utilities/StringUtils.h"

int main() {
    std::ifstream inputFile;
    inputFile.open("day13.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string line;
    std::getline(inputFile, line);
    int earliestDeparture = std::stoi(line);

    std::getline(inputFile, line);
    std::vector<std::string> buses= TokenizeString(line, ',');


    int bestBus = -1;
    int shortestWait = INT_MAX;
    long long firstTimestamp = 0;
    long long productOfIds = 1;
    for (int i = 0; i < buses.size(); i++) {
        std::string bus = buses[i];
        if (bus != "x") {
            int busID = std::stoi(bus);
            long long lBusID = std::stoll(bus);

            int waitTime = busID - (earliestDeparture % busID);
            if (waitTime < shortestWait) {
                shortestWait = waitTime;
                bestBus = busID;
            }

            if (i == 0) {
                productOfIds = lBusID;
            }
            else {
                long long cycleNum = 0;
                long long t = (productOfIds * cycleNum) + firstTimestamp + (long long)i;
                while (t % lBusID != 0) {
                    cycleNum++;
                    t = (productOfIds * cycleNum) + firstTimestamp + (long long)i;
                }
                firstTimestamp = t - (long long)i;
                productOfIds *= lBusID;
            }
        }
    }
    std::cout << "The earliest possible bus to take is " << bestBus << " with a wait time of " << shortestWait << "\n";
    std::cout << "Timestamp of first bus lineup: " << firstTimestamp << "\n";
}