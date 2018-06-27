#include "../include/depthFirstSearch.h"
#include <stack>

depthFirstSearch::depthFirstSearch(const graph& g)
{
    m_adjacencyList = g.getAdjacencyList();
}

// uses an explicit stack container to hold visited vertices
std::vector<int> depthFirstSearch::iterativeTraversal(int s)
{
    int v;
    std::stack<int> bounds;
    std::vector<int> traversalOrder;

    // mark all nodes to be unexplored and add the current node to
    // the explored bounds stack.
    std::map<int, bool> visited;
    for (auto node : m_adjacencyList) {
        visited[node.first] = false;
    }
    bounds.push(s);

    while (!bounds.empty()) {
        // remove the 1st node of the stack and print
        v = bounds.top();
        bounds.pop();

        // may contain same node twice, hence add the popped node
        // only if it is not visited.
        if (!visited[v]) {
            traversalOrder.push_back(v);
            visited[v] = true;
        }

        // for all vertices `w` adjacent to `v`, check if
        // they are visited. If not, then push it to the stack
        for (auto w : m_adjacencyList[v]) {
            if (!visited[w]) {
                bounds.push(w);
            }
        }
    }
    return traversalOrder;
}

// uses function call stack.
std::vector<int> depthFirstSearch::rTs(int s, std::map<int, bool>& visitedNodes, std::vector<int>& traversalOrder)
{
    // mark node s as visited and add it to the traversal list
    visitedNodes[s] = true;
    traversalOrder.push_back(s);

    // for all adjacent nodes of s,
    for (auto v : m_adjacencyList[s]) {
        if (!visitedNodes[v]) {
            rTs(v, visitedNodes, traversalOrder);
        }
    }
    return traversalOrder;
}

std::vector<int> depthFirstSearch::recursiveTraversal(int s)
{
    // mark all vertices as not visited.
    std::map<int, bool> visitedNodes;
    std::vector<int> traversalOrder;
    for (auto node : m_adjacencyList) {
        visitedNodes[node.first] = false;
    }

    // return the results of the recursive helper function `rTs`
    return rTs(s, visitedNodes, traversalOrder);
}

std::vector<int> depthFirstSearch::topologicalSort()
{
    // mark all nodes as not visited.
    std::map<int, bool> visitedNodes;
    std::stack<int> labels;
    std::vector<int> topologicalOrder;
    for (auto node : m_adjacencyList) {
        visitedNodes[node.first] = false;
    }

    // Call recursive helper function `tps` to store the topological
    // ordering starting from all vertices one by one.
    for (auto v : m_adjacencyList) {
        // if `v` is not visited, recurse on this node.
        if (!visitedNodes[v.first]) {
            tps(v.first, visitedNodes, labels);
        }
    }

    // The node visited last in the recursion is added to the stack
    // first for topological sort. Thus the top of the stack is the
    // first element in topological order.
    while (!labels.empty()) {
        topologicalOrder.push_back(labels.top());
        labels.pop();
    }

    return topologicalOrder;
}

void depthFirstSearch::tps(int s, std::map<int, bool>& visitedNodes, std::stack<int>& labels)
{
    // mark the current node as visited.
    visitedNodes[s] = true;

    for (auto v : m_adjacencyList[s]) {
        if (!visitedNodes[v]) {
            // recurse on all adjacent nodes, if not visited.
            tps(v, visitedNodes, labels);
        }
    }

    // push the current node on a temp stack after visiting all its
    // neighbours.
    labels.push(s);
}

std::map<int, std::vector<int>> depthFirstSearch::stronglyConnectedComponents()
{
    int nVertices = m_adjacencyList.size();
    int t = 0; // to book-keep finishing times in 1st pass
    int s = 0; // to book-keep leaders in 2nd pass
    std::vector<int> finishingTimes(nVertices);
    std::vector<int> leader(nVertices);

    // mark all nodes as unexplored
    std::map<int, bool> visitedNodes;
    for (auto node : m_adjacencyList) {
        visitedNodes[node.first] = false;
    }

    // container to keep track of the traversal order for the
    // second pass of DFS.
    std::vector<int> traversalOrder(nVertices);

    // (1) Grev is the given graph G with all arcs reversed. Create
    //     a reversed adjacency list based on the one that is given.
    std::map<int, std::set<int>> Grev;
    for (auto node : m_adjacencyList) {
        for (auto adjNode : node.second) {
            Grev[adjNode].emplace(node.first);
        }
    }

    // (2) 1st pass, run DFS on Grev. ( can also run DFS on G with
    //     going backwards along edges instead of forward ).
    //     objective of the first pass is to compute the order in
    //     which the nodes must be traversed in order to naturally
    //     uncover the strongly Connected Components.
    for (int i = 0; i < nVertices; ++i) {
        if (!visitedNodes[i]) {
            s = i;
            firstPass(Grev, i, visitedNodes, finishingTimes, t);
        }
    }

    // (3) 2nd pass, run DFS on G. process nodes in the decreasing
    //     order of their finishing times and discover the SCC's
    //     one by one. SCC's are the nodes with the same leader.

    // order of traversal for the second pass
    for (int i = 0; i < nVertices; ++i) {
        traversalOrder[finishingTimes[i]] = i;
    }

    // reset the visitedNodes to false for the second pass.
    for (auto node : m_adjacencyList) {
        visitedNodes[node.first] = false;
    }

    // visit the vertices in the decreasing order of finishing times
    for (int i = nVertices - 1; i >= 0; --i) {
        if (!visitedNodes[traversalOrder[i]]) {
            s = traversalOrder[i];
            secondPass(traversalOrder[i], leader, visitedNodes, s);
        }
    }

    // reconstruct the sccs from the leader
    std::set<int> uniqueLeaders;
    for (auto i : leader) {
        uniqueLeaders.emplace(i);
    }
    std::map<int, std::vector<int>> scc;
    int c = 0;
    std::vector<int> temp;
    for (auto l : uniqueLeaders) {
        temp.clear();
        for (unsigned int i = 0; i < leader.size(); ++i) {
            if (leader[i] == l) {
                temp.push_back(i);
            }
        }
        scc.emplace(c, temp);
        ++c;
    }
    return scc;
}

void depthFirstSearch::firstPass(std::map<int, std::set<int>>& grev, int node, std::map<int, bool>& visitedNodes, std::vector<int>& finishingTimes, int& t)
{
    // mark current node as explored
    visitedNodes[node] = true;

    // traverse the reverse graph starting from the start vertex
    for (auto n : grev[node]) {
        if (!visitedNodes[n]) {
            firstPass(grev, n, visitedNodes, finishingTimes, t);
        }
    }
    t++;
    finishingTimes[node] = t;
}

void depthFirstSearch::secondPass(int n, std::vector<int>& leader, std::map<int, bool>& visitedNodes, int& s)
{
    visitedNodes[n] = true;
    leader[n] = s;
    for (auto node : m_adjacencyList[n]) {
        if (!visitedNodes[node]) {
            secondPass(node, leader, visitedNodes, s);
        }
    }
}
