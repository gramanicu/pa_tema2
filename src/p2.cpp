#include <fstream>
#include <iostream>
#include <vector>

#define MAX_COST 10000

struct Edge {
    int source;
    int target;
    int cost;
};

long int BellmanFord(const std::vector<Edge> adjency, const int vertexCount,
                     const int sourceVertex, const int targetVertex) {
    // Initialise the distance to all other vertices to infinity
    std::vector<long int> distance(vertexCount, INT32_MAX);

    // The distance to itself is 0
    distance[sourceVertex] = 0;

    // Relax edges
    for (int i = 0; i < vertexCount - 1; ++i) {
        bool changes = false;
        for (auto& edge : adjency) {
            int newDistance = distance[edge.source] + edge.cost;

            if (distance[edge.source] != INT32_MAX &&
                newDistance < distance[edge.target]) {
                // Relax edge
                distance[edge.target] = newDistance;
                changes = true;
            }
        }

        // The graph doesn't need to change anymore
        if (!changes) {
            break;
        }
    }

    return distance[targetVertex];
}

int main() {
    std::ifstream in("p2.in");
    std::ofstream out("p2.out");

    int vertexCount, edgeCount;
    int srcVertex, dstVertex;

    in >> vertexCount >> edgeCount;
    in >> srcVertex >> dstVertex;

    // Build the adjency list
    std::vector<Edge> adjency(edgeCount);

    for (auto& edge : adjency) {
        int source, target, cost;
        in >> source >> target >> cost;
        
        // The nodes are indexed starting from 0 internally
        edge = {source - 1, target - 1, cost};
    }

    out << BellmanFord(adjency, vertexCount, srcVertex - 1, dstVertex - 1);

    return 0;
}
