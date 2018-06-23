#ifndef DFS_PRINT_H
#define DFS_PRINT_H

#include "../include/undirected_graph.h"

class depthFirstSearch {
public:
    depthFirstSearch(const undirected_graph& g);

    virtual ~depthFirstSearch() = default;

    std::vector<int> iterativeTraversal(int s);

    std::vector<int> recursiveTraversal(int s);

private:
    depthFirstSearch() = default;

    std::vector<int> rTs(int s, std::map<int, bool>& visitedNodes, std::vector<int>& traversalOrder);

    std::map<int, std::set<int>> m_adjacencyList;
};

#endif /* ifndef BFS_PRINT_H */
