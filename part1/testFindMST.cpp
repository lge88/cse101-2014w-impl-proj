
#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "Graph.findMST.hpp"

using namespace std;

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

}

int main() {
  // testFindCCs();
  testFindMST();
}
