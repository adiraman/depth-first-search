#include "../include/depthFirstSearch.h"
#include "../include/undirected_graph.h"
#include "../include/directed_graph.h"

template <typename T>
void printVec(const T& elems)
{
    for (auto i : elems) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    return;
}

int main()
{
    undirected_graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(4, 1);
    g.addEdge(1, 5);
    g.addEdge(2, 6);
    g.addEdge(7, 3);
    g.addEdge(4, 7);
    g.addEdge(7, 5);
    g.addEdge(6, 7);
    std::cout << "           Input Graph          " << std::endl;
    std::cout << g << std::endl;
    g.writeDot("graph.dot");

    depthFirstSearch dfs(g);

    std::cout << " Iterative Traversal from node 3 " << std::endl;
    auto t1 = dfs.iterativeTraversal(3);
    auto t2 = dfs.recursiveTraversal(3);
    printVec(t1);
    std::cout << " Recursive Traversal from node 3 " << std::endl;
    printVec(t2);
    std::cout << std::endl;

    std::cout << " Iterative Traversal from node 5 " << std::endl;
    auto t3 = dfs.iterativeTraversal(5);
    auto t4 = dfs.recursiveTraversal(5);
    printVec(t3);
    std::cout << " Recursive Traversal from node 5 " << std::endl;
    printVec(t4);
    std::cout << std::endl;

    std::cout << " Iterative Traversal from node 0 " << std::endl;
    auto t5 = dfs.iterativeTraversal(0);
    auto t6 = dfs.recursiveTraversal(0);
    printVec(t5);
    std::cout << " Recursive Traversal from node 0 " << std::endl;
    printVec(t6);
    std::cout << std::endl;

    directed_graph g1;
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    std::cout << g1 << std::endl;
    g1.writeDot("graph2.dot");

    depthFirstSearch dfs1(g1);

    std::cout << "Topological order of G1" << std::endl;
    auto t7 = dfs1.topologicalSort();
    printVec(t7);
    std::cout << std::endl;

    return 0;
}
