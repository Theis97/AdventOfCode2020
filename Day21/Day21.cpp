#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "../Utilities/StringUtils.h"

void NarrowOptions(std::string allergen, std::string ingredient, std::map<std::string, std::set<std::string>>& allergenCandidates) {
    for (auto &a : allergenCandidates) {
        if (allergen != a.first && allergenCandidates[a.first].size() != 1) {
            std::set<std::string> ingredients = allergenCandidates[a.first];
            ingredients.erase(ingredient);
            allergenCandidates[a.first] = ingredients;
            if (ingredients.size() == 1) {
                NarrowOptions(a.first, *ingredients.begin(), allergenCandidates);
            }
        }
    }
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day21.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::map<std::string, int> allIngredientCounts;
    std::map<std::string, std::set<std::string>> allergenCandidates;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> t = TokenizeString(line, '(');
        std::vector<std::string> ingredients = TokenizeString(t[0], ' ');
        std::string trimmed = TrimStr(t[1], ')');
        trimmed = trimmed.substr(8);
        std::vector<std::string> allergens = TokenizeString(trimmed, ',');
        for (int i = 0; i < allergens.size(); i++) {
            allergens[i] = TrimStr(allergens[i], ' ');
        }

        for (auto& ingredient : ingredients) {
            allIngredientCounts[ingredient]++;
        }

        for (auto& allergen : allergens) {
            if (allergenCandidates.count(allergen) == 0) {
                std::set<std::string> candidates;
                for (auto& ingredient : ingredients) {
                    candidates.insert(ingredient);
                }
                allergenCandidates[allergen] = candidates;
            }
            else {
                std::set<std::string> oldCandidates = allergenCandidates[allergen];
                std::set<std::string> narrowedCandidates;
                for (auto& ingredient : ingredients) {
                    if (oldCandidates.count(ingredient) == 1) {
                        narrowedCandidates.insert(ingredient);
                    }
                }
                allergenCandidates[allergen] = narrowedCandidates;
            }
        }
    }

    for (auto& allergen : allergenCandidates) {
        if (allergenCandidates[allergen.first].size() == 1) {
            NarrowOptions(allergen.first, *allergenCandidates[allergen.first].begin(), allergenCandidates);
            break;
        }
    }

    std::cout << "Allergens are...\n";
    std::string partTwoAnswer = "";
    for (auto& allergen : allergenCandidates) {
        std::cout << allergen.first << ": ";
        for (auto& ingredient : allergen.second) {
            allIngredientCounts.erase(ingredient);
            std::cout << ingredient << " ";
            partTwoAnswer += ingredient + ",";
        }
        std::cout << "\n";
    }
    partTwoAnswer = TrimStr(partTwoAnswer, ',');

    int appearanceCounts = 0;
    for (auto &ingredient : allIngredientCounts) {
        appearanceCounts += ingredient.second;
    }
    std::cout << "Number of times a non-allergen appeared: " << appearanceCounts << "\n\n";
    std::cout << "Part 2 answer format:\n";
    std::cout << partTwoAnswer << "\n";
}