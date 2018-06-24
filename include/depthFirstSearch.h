#ifndef DFS_PRINT_H
#define DFS_PRINT_H

#include "../include/undirected_graph.h"
#include "../include/directed_graph.h"
#include <stack>

class depthFirstSearch {
public:
    depthFirstSearch(const graph& g);

    virtual ~depthFirstSearch() = default;

    std::vector<int> iterativeTraversal(int s);

    std::vector<int> recursiveTraversal(int s);

    // returns a vector of node positions
    std::vector<int> topologicalSort();

private:
    depthFirstSearch() = default;

    std::vector<int> rTs(int s, std::map<int, bool>& visitedNodes, std::vector<int>& traversalOrder);

    void tps(int s, std::map<int, bool>& visitedNodes, std::stack<int>& labels);

    std::map<int, std::set<int>> m_adjacencyList;
};

#endif /* ifndef BFS_PRINT_H */
