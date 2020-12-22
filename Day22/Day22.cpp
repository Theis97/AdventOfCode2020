#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream inputFile;
    inputFile.open("day22.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }


    std::vector<std::vector<int>> decks;
    decks.push_back(std::vector<int>());

    std::string line;
    std::getline(inputFile, line); // "Player 1:"
    while (std::getline(inputFile, line)) {
        if(line == "") {
            decks.push_back(std::vector<int>());
            std::getline(inputFile, line); // "Player 2:"
        }
        else {
            decks.back().push_back(std::stoi(line));
        }
    }

    //int roundCounter = 1;
    while (decks[0].size() > 0 && decks[1].size() > 0) {
        //std::cout << "Round " << roundCounter++ << "\n";
        //std::cout << decks[0][0] << " vs " << decks[1][0] << "\n";
        if (decks[0][0] > decks[1][0]) {
            //std::cout << "Player 1 wins the round\n";
            decks[0].push_back(decks[0][0]);
            decks[0].push_back(decks[1][0]);
            decks[0].erase(decks[0].begin());
            decks[1].erase(decks[1].begin());
        }
        else {
            //std::cout << "Player 2 wins the round\n";
            decks[1].push_back(decks[1][0]);
            decks[1].push_back(decks[0][0]);
            decks[0].erase(decks[0].begin());
            decks[1].erase(decks[1].begin());
        }
    }

    std::vector<int> winningDeck;
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

    std::cout << "Winner's score: " << score << "\n";
}