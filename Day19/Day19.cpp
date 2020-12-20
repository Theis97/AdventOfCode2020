#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "../Utilities/StringUtils.h"

struct Rule {
    bool isTerminal = false;
    char terminal = 0;
    std::vector<std::vector<int>> subrules;
};

// Returns the lengths of all possible matches
std::vector<int> MatchRule(std::map<int, Rule>& rules, const std::string& message, Rule rule, int index) {
    if (rule.isTerminal && message[index] == rule.terminal) {
        return std::vector<int>{1};
    }

    std::vector<int> matchLengths;
    for (int i = 0; i < rule.subrules.size(); i++) {
        std::vector<int> subrule = rule.subrules[i];
        std::vector<int> submatchLengths{0};

        for (int j = 0; j < subrule.size(); j++) {
            int ruleNum = subrule[j];
            std::vector<int> matches;
            std::vector<int> newSubmatchLengths;

            for (auto length : submatchLengths) {
                matches = MatchRule(rules, message, rules[ruleNum], index + length);
                for (auto nextMatch : matches) {
                    newSubmatchLengths.push_back(length + nextMatch);
                }
            }
            submatchLengths = newSubmatchLengths;
        }
        for (auto length : submatchLengths) {
            matchLengths.push_back(length);
        }
    }
    return matchLengths;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day19part2.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::map<int, Rule> rules;

    std::string line;
    std::getline(inputFile, line);
    while (line != "") {
        std::vector<std::string> tokens = TokenizeString(line, ' ');
        int ruleNum = std::stoi(tokens[0]);

        Rule rule;
        if (tokens[1][0] == '"') {
            rule.isTerminal = true;
            rule.terminal = tokens[1][1];
        }
        else {
            std::vector<int> subrule;
            for (int i = 1; i < tokens.size(); i++) {
                if (tokens[i][0] == '|') {
                    rule.subrules.push_back(subrule);
                    subrule.clear();
                }
                else {
                    subrule.push_back(std::stoi(tokens[i]));
                }
            }
            if (!subrule.empty()) {
                rule.subrules.push_back(subrule);
            }
        }
        rules[ruleNum] = rule;
        std::getline(inputFile, line);
    }

    int matchingMessages = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> matches = MatchRule(rules, line, rules[0], 0);
        if (!matches.empty()) {
            for (auto length : matches) {
                if (length == line.length()) {
                    matchingMessages++;
                    break;
                }
            }
        }
    }

    std::cout << "Complete matches: " << matchingMessages << "\n";
}