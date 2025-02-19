/**
 * Copyright (c) 2020 Grama Nicolae
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

        // The nodes are indexed starting from 0 internally
        adjency[start - 1].push_back({start - 1, end - 1, cost});
    }

    Dijkstra(adjency, vertexCount, 0.0, vertexCount - 1, energy, out);

    return 0;
}
