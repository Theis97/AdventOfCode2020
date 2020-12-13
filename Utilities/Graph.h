#pragma once
#include <map>
#include <vector>
#include <memory>
#include <set>
#include <string>

// TODO: make this generic
class Graph {
public:
	void AddVertex(std::string vertex);
	void AddEdge(std::string fromVertex, std::string toVertex, int weight);

	bool Contains(std::string vertex);

	std::vector<std::pair<std::string, int>> GetEdges(std::string vertex);

	int CountReachableVertices(std::string startvertex);
private:
	int CountReachableHelper(std::string vertex, std::set<std::string>& visited);
	std::map<std::string, std::vector<std::pair<std::string, int>>> vertices;
};