#include <iostream>

#include "Graph.hpp"

using namespace std;

int main() {
  Graph g;
  g.fromTxt(cin);
  g.toDot(cout);
  return 0;
}
