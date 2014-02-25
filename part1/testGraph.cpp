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

  g.addEdge("A", "B", 1.0);
  g.addEdge("A", "C", 3.0);
  g.addEdge("B", "C", 5.0);
  g.addEdge("B", "D", 6.0);
  g.addEdge("C", "D", 7.0);
  g.addEdge("A", "E", 2.0);
  g.addEdge("C", "E", 4.0);

  g.toDot(cout);
}
