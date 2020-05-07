# PA, Second Homework - "Robin Hood and Graphs"

The second homework for the Algorithm Design Course. The problem statement can be found [here](./docs/problem_statement.pdf).

## Save Robin Hood - First problem

**Time complexity**

**Optimisations**

## Robin Hood stealing for the poor - Second Problem

As the graph used to represent the problem can have negative edges, there are a few shortest-path algorithms we could use: Bellman-Ford or Johnson's Algorithm. I decided to use Bellman-Ford as it is simpler and is better for solving "one to all" shortest-path problems (Johnson is better in the case we need to find the distances from all to all vertices).

**Time complexity**

- `O(|V| * |E|)` - the complexity of the Bellman-Ford algorithm. |V| is the number of vertices and |E| is the number of edges

**Optimisations**

The search can be considered finished after |V| - 1 cycles. However, this can be done even faster in some cases, so I accounted for this situation by having the `changes` variable, that will be set to true when we could relax any edge. When no edge was relaxed, we know we found a path. In this case, the search stops.

## Fooling the guards - Third Problem

This problem can be easily solved by using a modified Dijkstra's Algorithm. Where a standard dijkstra would search for the path with the shortest cost, in this case I actually search for the path with the biggest cost (to have as much energy at the end).

Initially, all the nodes have a `0` cost, except the starting one, who has the starting energy. An edge stores how much of the energy is lost (as a percentage). A path is considered better when the new cost is larger than the old one. The new cost is computed using the next formula:

` new_cost = starting_energy * (1 - edge_cost / 100) `

To represent the best route, we don't store just the "distance" to each node, but also the predecesors of the nodes. Starting in the destination node, we can move through the "predecesors" to get to the start node, storing the nodes in a stack as we go. Then, we simply print the stack.

**Time complexity**

- `O(|V| * |E|log|V|)` - the complexity of the Dijkstra's algorithm. |V| is the number of vertices, and |E| is the number of edges.

**Optimisations**

Firstly, the solution was optimised by using a priority queue (max heap). Initially, this was not enough to complete the test in the required time (without using any compiler optimisations). The problem was solved by storing the adjency list a bit differently. 

```cpp
    // ---------- From --------------
    std::vector<Edge> adjency(edgeCount);
    for (auto& edge : adjency) {
        int start, end;
        double cost;
        in >> start >> end >> cost;
        edge.push_back({start - 1, end - 1, cost});
    }
    
    // ---------- Into --------------
    std::vector<std::vector<Edge>> adjency(vertexCount);
    for (int i = 0; i < edgeCount; ++i) {
        int start, end;
        double cost;
        in >> start >> end >> cost;
        adjency[start - 1].push_back({start - 1, end - 1, cost});
    }
```

By organising the list into "buckets", that contain all the edges that start in specific vertex, I could find a lot faster the neighbours of a vertex (thus reducing the complexity of the Dijkstra).

© 2020 Grama Nicolae
