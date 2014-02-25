#include <iostream>

#include "Graph.hpp"

using namespace std;

int main() {
  Graph g;
  g.addVertex("A");
  g.addVertex("B");
  g.addVertex("C");
  g.addVertex("D");
  g.addVertex("E");

  g.addUndirectedEdge("A", "B");
  g.addUndirectedEdge("A", "C");
  g.addUndirectedEdge("B", "C");
  g.addUndirectedEdge("B", "D");
  g.addUndirectedEdge("C", "D");
  g.addUndirectedEdge("A", "E");
  g.addUndirectedEdge("C", "E");

  g.toDot(cout);
}
