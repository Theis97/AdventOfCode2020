#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

const bool partOne = false;

// Returns whether Player 1 won or not and the score of the winning player
std::pair<bool, int> PlayRecursiveCombat(std::vector<std::deque<int>> decks, std::map<std::vector<std::deque<int>>, std::pair<bool, int>>& previousGameResults) {
    if (previousGameResults.count(decks) > 0) {
        return previousGameResults[decks];
    }

    std::vector<std::deque<int>> startingDecks = decks;
    std::set<std::string> previousRounds;
    while (decks[0].size() > 0 && decks[1].size() > 0) {
        std::string gameState = "";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < decks[i].size(); j++) {
                gameState += decks[i][j];
            }
            // Mark the end of a player's deck
            gameState += ".";
        }

        if (previousRounds.count(gameState) == 1) {
            // We *could* actually calculate a score here, but eeeeh
            return std::pair<bool, int>(true, -1);
        }
        previousRounds.insert(gameState);

        if (decks[0].front() <= decks[0].size() - 1 
            && decks[1].front() <= decks[1].size() - 1) {
            std::vector<std::deque<int>> newDecks;
            for (auto &deck : decks) {
                newDecks.push_back(std::deque<int>(deck.begin() + 1, deck.begin() + deck.front() + 1));
            }
            std::pair<bool, int> subgameResult = PlayRecursiveCombat(newDecks, previousGameResults);
            if (subgameResult.first) {
                decks[0].push_back(decks[0].front());
                decks[0].push_back(decks[1].front());
            }
            else {
                decks[1].push_back(decks[1].front());
                decks[1].push_back(decks[0].front());
            }
        }
        else {
            if (decks[0].front() > decks[1].front()) {
                decks[0].push_back(decks[0].front());
                decks[0].push_back(decks[1].front());
            }
            else {
                decks[1].push_back(decks[1].front());
                decks[1].push_back(decks[0].front());
            }
        }
        decks[0].pop_front();
        decks[1].pop_front();
    }

    bool playerOneVictory = false;
    std::deque<int> winningDeck;
    if (decks[0].size() == 0) {
        // Player 2 won
        winningDeck = decks[1];
    }
    else {
        // Player 1 won
        playerOneVictory = true;
        winningDeck = decks[0];
    }

    int mult = 1;
    int score = 0;
    for (int i = winningDeck.size() - 1; i >= 0; i--) {
        score += winningDeck[i] * mult;
        mult++;
    }

    std::pair<bool, int> result(playerOneVictory, score);
    previousGameResults[startingDecks] = result;
    return result;
}

// Returns the winning player's score. (Original game)
int PlayCombat(std::vector<std::deque<int>> decks) {
    while (decks[0].size() > 0 && decks[1].size() > 0) {
        if (decks[0].front() > decks[1].front()) {
            decks[0].push_back(decks[0].front());
            decks[0].push_back(decks[1].front());
        }
        else {
            decks[1].push_back(decks[1].front());
            decks[1].push_back(decks[0].front());
        }
        decks[0].pop_front();
        decks[1].pop_front();
    }

    std::deque<int> winningDeck;
    if (decks[0].size() == 0) {
        // Player 2 won
        winningDeck = decks[1];
    }
    else {
        // Player 1 won
        winningDeck = decks[0];
    }

    int mult = 1;
    int score = 0;
    for (int i = winningDeck.size() - 1; i >= 0; i--) {
        score += winningDeck[i] * mult;
        mult++;
    }

    return score;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day22.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::vector<std::deque<int>> decks;
    decks.push_back(std::deque<int>());

    std::string line;
    std::getline(inputFile, line); // "Player 1:"
    while (std::getline(inputFile, line)) {
        if(line == "") {
            decks.push_back(std::deque<int>());
            std::getline(inputFile, line); // "Player 2:"
        }
        else {
            decks.back().push_back(std::stoi(line));
        }
    }

    if (partOne) {
        int score = PlayCombat(decks);
        std::cout << "Winner's score: " << score << "\n";
    }
    else {
        std::map<std::vector<std::deque<int>>, std::pair<bool, int>> previousGameResults;
        std::pair<bool, int> result = PlayRecursiveCombat(decks, previousGameResults);
        if (result.first) {
            std::cout << "Player 1 ";
        }
        else {
            std::cout << "Player 2 ";
        }
        std::cout << "wins with a score of " << result.second << "\n";
    }
}