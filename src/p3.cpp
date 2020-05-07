#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

struct Edge {
    int start;
    int end;
    double cost;
};

bool operator<(const Edge& x, const Edge& y) { return x.cost < y.cost; }

typedef std::pair<long double, int> dPair;

void Dijkstra(const std::vector<std::vector<Edge>>& adjency,
              const int vertexCount, const int sourceVertex,
              const int targetVertex, const double startEnergy,
              std::ofstream& out) {
    // Intialise the energy to get to the other vertices to 0
    std::vector<std::pair<double, int>> energy(vertexCount,
                                               std::make_pair(0.0, 0));

    // Set the starting energy
    energy[sourceVertex].first = startEnergy;

    std::priority_queue<dPair, std::vector<dPair>, std::less<dPair>> pq;
    std::vector<bool> visited(vertexCount, false);

    pq.push(std::make_pair(startEnergy, sourceVertex));

    while (!pq.empty()) {
        int currVertex = pq.top().second;
        pq.pop();
        visited[currVertex] = true;

        // Add unvisited neighbouring nodes to the graph & update costs
        for (auto& edge : adjency[currVertex]) {
            if (edge.start == currVertex && visited[edge.end] == false) {
                // The "cost" from the current vertex to the neighbour
                double newEnergy = energy[edge.start].first *
                                   (1.0 - (((double)edge.cost) / 100.0L));

                // Update the energy if it uses less on this path
                if (newEnergy > energy[edge.end].first) {
                    energy[edge.end].first = newEnergy;
                    energy[edge.end].second = edge.start;
                    pq.push(std::make_pair(energy[edge.end].first, edge.end));
                }
            }
        }
    }

    out << std::fixed << std::setprecision(8) << energy[targetVertex].first
        << "\n";

    // Build the path from the end to the start (the will be reversed)
    std::stack<int> path;
    path.push(targetVertex);
    int curr = energy[targetVertex].second;
    while (curr != sourceVertex) {
        path.push(curr);
        curr = energy[curr].second;
    }
    path.push(sourceVertex);

    // Print the path
    while (!path.empty()) {
        out << path.top() + 1 << " ";
        path.pop();
    }
}

int main() {
    std::ifstream in("p3.in");
    std::ofstream out("p3.out");
    int vertexCount, edgeCount, energy;

    in >> vertexCount >> edgeCount >> energy;

    // Build the adjency list
    std::vector<std::vector<Edge>> adjency(vertexCount);

    for (int i = 0; i < edgeCount; ++i) {
        int start, end;
        double cost;
        in >> start >> end >> cost;
        adjency[start - 1].push_back({start - 1, end - 1, cost});
    }

    Dijkstra(adjency, vertexCount, 0.0, vertexCount - 1, energy, out);

    return 0;
}
