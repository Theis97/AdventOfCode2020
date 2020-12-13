#include <iostream>
#include <fstream>
#include <string>

#include "../Utilities/StringUtils.h"
#include "../Utilities/Graph.h"

// TODO: make some more general traversal algo(s) in Graph.h
int GetTotalBagsInside(Graph& g, std::string startBag, std::map<std::string, int>& visited) {
    int totalBags = 0;
    std::vector<std::pair<std::string, int>> containedBags = g.GetEdges(startBag);
    for (auto &e : containedBags) {
        if (visited.find(e.first) != visited.end()) {
            totalBags += (visited[e.first] + 1) * e.second;
        }
        else {
            totalBags += (GetTotalBagsInside(g, e.first, visited) + 1) * e.second;
        }
    }
    visited[startBag] = totalBags;
    return totalBags;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("day7.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    Graph heldToHolderGraph;
    Graph holderToHeldGraph;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> tokens = TokenizeString(line, ' ');
        std::string holderBagColor = tokens[0] + tokens[1];

        if (!heldToHolderGraph.Contains(holderBagColor)) {
            heldToHolderGraph.AddVertex(holderBagColor);
            holderToHeldGraph.AddVertex(holderBagColor);
        }

        if (tokens.size() > 7) {
            int i = 4;
            while (i < tokens.size()) {
                int bagCount = std::stoi(tokens[i]);
                std::string heldBagColor = tokens[i+1] + tokens[i+2];

                if (!heldToHolderGraph.Contains(heldBagColor)) {
                    heldToHolderGraph.AddVertex(heldBagColor);
                    holderToHeldGraph.AddVertex(holderBagColor);
                }

                heldToHolderGraph.AddEdge(heldBagColor, holderBagColor, bagCount);
                holderToHeldGraph.AddEdge(holderBagColor, heldBagColor, bagCount);

                i += 4;
            }
        }
    }
    int partOneAnswer = heldToHolderGraph.CountReachableVertices("shinygold") - 1;

    std::map<std::string, int> visited;
    int partTwoAnswer = GetTotalBagsInside(holderToHeldGraph, "shinygold", visited);

    std::cout << "There are " << partOneAnswer << " bags that can hold at least 1 shiny gold bag in them somewhere\n";
    std::cout << partTwoAnswer << " bags are required to be in your shiny gold bag\n";
}