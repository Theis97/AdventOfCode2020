#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

int main() {
    std::ifstream inputFile;
    inputFile.open("day6.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string line;
    std::set<char> anyYesQuestions;
    std::map<char, int> yesAnswersCounts;
    int anyYesSum = 0;
    int everyYesSum = 0;
    int groupSize = 0;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            anyYesSum += anyYesQuestions.size();
            anyYesQuestions.clear();

            for (auto &letterCount : yesAnswersCounts) {
                if (letterCount.second == groupSize) {
                    everyYesSum++;
                }
            }
            yesAnswersCounts.clear();
            groupSize = 0;
        }
        else {
            groupSize++;
            for (char c : line) {
                anyYesQuestions.insert(c);
                yesAnswersCounts[c] += 1;
            }
        }
    }

    anyYesSum += anyYesQuestions.size();
    anyYesQuestions.clear();

    for (auto& letterCount : yesAnswersCounts) {
        if (letterCount.second == groupSize) {
            everyYesSum++;
        }
    }

    std::cout << "Sum of questions anyone answered per group is: " << anyYesSum << "\n";
    std::cout << "Sum of questions everyone answered per group is: " << everyYesSum << "\n";
}