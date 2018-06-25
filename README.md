# Depth First Search

The algorithm for depth first traversal of a graph, both Iterative and Recursive implementations. The iterative implementation is
very similar to the BFS traversal algorithm, with the only difference being in the use of a stack data structure instead of a queue.
The idea for the recursive implementation is similar as it uses function call stack.

Iterative Algorithm :-

1.  mark all nodes of the graph as unexplored and push the start node into the stack
2.  While the stack is not empty
3.    remove the top of stack and call it v
4.    if v is not visited, add it to the traversal list and mark it visited.
5.    for all vertices w adjacent to v:
6.      if w is not visited, add it to the stack.

Recursive Algorithm :-

1.  mark s as explored and add it to the traversal list
2.  for every vertex v adjacent to s:
3.    if v is unexplored
4.      recurse on v

Application :- Topological Ordering of a directed acyclic graph.
Topological sorting is a linear ordering of the vertices such that
for every directed edge (u, v), vertex u comes before v in the
ordering.
NOTE:- Topological sorting for a graph is not possible if it is not
a Directed Acyclic Graph (DAG).

Motivation in sequencing tasks with a given precedence constraints.

