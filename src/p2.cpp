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
