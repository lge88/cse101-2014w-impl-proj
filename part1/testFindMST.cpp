
#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "Graph.algo.hpp"

using namespace std;

enum Option {
  IN = 0,
  OUT,
  COST
};

std::ostream& operator<<(std::ostream& out, const vector<vector<int> >& v) {
  for (int i = 0, len = v.size(); i < len; ++i) {
    const vector<int>& tmp = v[i];
    for (int j = 0, len2 = tmp.size(); j < len2; ++j) {
      out << tmp[j] << " ";
    }
    out << "\n";
  }
  return out;
}

void testFindCCs() {
  Graph g;
  g.addVertex("A");
  g.addVertex("B");
  g.addVertex("C");
  g.addVertex("D");
  g.addVertex("E");
  g.addVertex("F");
  g.addVertex("G");
  g.addVertex("H");

  g.addEdge("A", "B");
  g.addEdge("A", "C");
  g.addEdge("B", "C");

  g.addEdge("D", "E");

  g.addEdge("F", "G");
  g.addEdge("G", "H");
  g.addEdge("F", "H");

  vector<vector<int> > ccs;

  ccs = g.findCCs();

  cout << ccs;
  cout << "Num of cc: " << ccs.size() << endl;
}

void testFindMST() {
  Graph g;
  g.addVertex("A");
  g.addVertex("B");
  g.addVertex("C");
  g.addVertex("D");
  g.addVertex("E");

  g.addEdge("A", "B", 0.10);
  g.addEdge("A", "C", 0.30);
  g.addEdge("B", "C", 0.50);
  g.addEdge("B", "D", 0.60);
  g.addEdge("C", "D", 0.70);
  g.addEdge("A", "E", 0.20);
  g.addEdge("C", "E", 0.40);

  g.toDot(cout);

  cout << "#\n";

  Graph mst = g.findMST("A");
  mst.toDot(cout);

  cout << "cost: " << g.calcMSTCost("A") << endl;

}


void testFindMST2(Option opt) {
  Graph g;
  g.addVertex("a");
  g.addVertex("b");
  g.addVertex("c");
  g.addVertex("d");
  g.addVertex("e");
  g.addVertex("f");
  g.addVertex("g");
  g.addVertex("h");
  g.addVertex("i");

  g.addEdge("a", "b", 0.40);
  g.addEdge("a", "h", 0.80);
  g.addEdge("b", "c", 0.80);
  g.addEdge("b", "h", 1.10);
  g.addEdge("c", "d", 0.70);
  g.addEdge("c", "f", 0.40);
  g.addEdge("c", "i", 0.20);
  g.addEdge("d", "e", 0.90);
  g.addEdge("d", "f", 1.40);
  g.addEdge("e", "f", 1.00);
  g.addEdge("f", "g", 0.20);
  g.addEdge("g", "h", 0.10);
  g.addEdge("g", "i", 0.60);
  g.addEdge("h", "i", 0.70);

  if (opt == OUT) {
    g.toDot(cout);
  } else if (opt == IN) {
    Graph mst = g.findMST("a");
    mst.toDot(cout);
  } else if (opt == COST) {
    // double cost = g.calcMSTCost("a");
    // cout << cost << endl;
    cout << g.calcAvgMSTState().cost << endl;
  }
}

int main(int argc, char* argv[]) {
  // testFindCCs();
  // testFindMST();
  Option opt = OUT;
  if (argc > 1) {
    if (string(argv[1]) == "in") {
      opt = IN;
    } else if (string(argv[1]) == "cost") {
      opt = COST;
    }
  }
  testFindMST2(opt);
}
