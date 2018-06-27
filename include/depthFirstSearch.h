#ifndef DFS_PRINT_H
#define DFS_PRINT_H

#include "../include/directed_graph.h"
#include "../include/undirected_graph.h"
#include <stack>

class depthFirstSearch {
public:
    depthFirstSearch(const graph& g);

    virtual ~depthFirstSearch() = default;

    std::vector<int> iterativeTraversal(int s);

    std::vector<int> recursiveTraversal(int s);

    // returns a vector of node positions
    std::vector<int> topologicalSort();

    std::map<int, std::vector<int>> stronglyConnectedComponents();

private:
    depthFirstSearch() = default;

    // helper for recursive Traversal
    std::vector<int> rTs(int s, std::map<int, bool>& visitedNodes, std::vector<int>& traversalOrder);

    // helper for topological Sort
    void tps(int s, std::map<int, bool>& visitedNodes, std::stack<int>& labels);

    // helper for computing scc's. First pass DFS in Kosaraju's
    // algorithm
    void firstPass(std::map<int, std::set<int>>& grev, int node, std::map<int, bool>& visitedNodes, std::vector<int>& finishingTimes, int& t);

    // helper for computing scc's. Second pass DFS in Kosaraju's
    // algorithm
    void secondPass(int n, std::vector<int>& leader, std::map<int, bool>& visitedNodes, int& s);

    std::map<int, std::set<int>> m_adjacencyList;
};

#endif /* ifndef BFS_PRINT_H */
