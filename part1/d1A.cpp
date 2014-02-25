#include <iostream>

#include "Graph.hpp"

using namespace std;

void addUndirectedEdge(Graph& g, const string& u, const string& v,
                       double w = 1.0) {
  g.addEdge(u, v, w);
  g.addEdge(v, u, w);
}


int main() {
  Graph g;
  g.addVertex("A");
  g.addVertex("B");
  g.addVertex("C");
  g.addVertex("D");
  g.addVertex("E");

  addUndirectedEdge(g, "A", "B");
  addUndirectedEdge(g, "A", "C");
  addUndirectedEdge(g, "B", "C");
  addUndirectedEdge(g, "B", "D");
  addUndirectedEdge(g, "C", "D");
  addUndirectedEdge(g, "A", "E");
  addUndirectedEdge(g, "C", "E");


  g.toDot(cout);
}
