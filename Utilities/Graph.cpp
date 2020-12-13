#include "Graph.h"
#include <iostream>

void Graph::AddVertex(std::string vertex) {
	vertices[vertex];
}

void Graph::AddEdge(std::string fromVertex, std::string toVertex, int weight) {
	std::vector<std::pair<std::string, int>> edges = vertices[fromVertex];
	edges.push_back(std::pair<std::string, int>(toVertex, weight));
	vertices[fromVertex] = edges;
}

bool Graph::Contains(std::string vertex) {
	return vertices.find(vertex) != vertices.end();
}

std::vector<std::pair<std::string, int>> Graph::GetEdges(std::string vertex) {
	return vertices[vertex];
}

int Graph::CountReachableVertices(std::string startvertex) {
	std::set< std::string> visited;
	return CountReachableHelper(startvertex, visited);
}

int Graph::CountReachableHelper(std::string vertex, std::set<std::string>& visited) {
	visited.insert(vertex);

	int reachableCount = 0;
	std::vector<std::pair<std::string, int>> edges = vertices[vertex];
	for (auto& edge : edges) {
		std::string otherVertex = edge.first;
		if (visited.find(otherVertex) == visited.end()) {
			reachableCount += CountReachableHelper(otherVertex, visited);
		}
	}
	return reachableCount + 1;
}