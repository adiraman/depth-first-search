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

    // a safer compliant container alternative to `std::vector<bool>`
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
