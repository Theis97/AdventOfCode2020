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

std::pair<bool, int> MatchRule(std::map<int, Rule>& rules, const std::string& message, Rule rule, int index) {
    if (rule.isTerminal) {
        return std::pair<bool, int>(message[index] == rule.terminal, 1);
    }

    bool foundMatch = false;
    int matchLength = 0;
    for (int i = 0; i < rule.subrules.size(); i++) {
        std::vector<int> subrule = rule.subrules[i];
        bool subruleMatched = true;
        int subruleMatchLength = 0;
        for (int j = 0; j < subrule.size(); j++) {
            int ruleNum = subrule[j];
            std::pair<bool, int> match = MatchRule(rules, message, rules[ruleNum], index + subruleMatchLength);
            if (!match.first) {
                subruleMatched = false;
                break;
            }
            subruleMatchLength += match.second;
        }
        if (subruleMatched) {
            foundMatch = true;
            matchLength += subruleMatchLength;
            break;
        }
    }

    return std::pair<bool, int>(foundMatch, matchLength);
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day19.txt");
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
        std::pair<bool, int> match = MatchRule(rules, line, rules[0], 0);
        if (match.first && match.second == line.length()) {
            matchingMessages++;
        }
    }

    std::cout << "Complete matches: " << matchingMessages << "\n";
}