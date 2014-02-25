#include <iostream>
#include <cstdlib>

#include "Graph.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  int n = 10;
  double p = 0.2;

  if (argc > 1)
    n = atoi(argv[1]);

  if (argc > 2)
    p = atof(argv[2]);

  Graph g(n, p);
  g.toDot(cout);
}
