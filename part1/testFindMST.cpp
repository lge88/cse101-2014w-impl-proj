
#include <iostream>
#include <vector>

#include "Graph.hpp"
#include "Graph.findMST.hpp"

using namespace std;



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

  for (int i = 0, len = ccs.size(); i < len; ++i) {
    vector<int>& tmp = ccs[i];
    for (int j = 0, len2 = tmp.size(); j < len2; ++j) {
      cout << tmp[j] << " ";
    }
    cout << "\n";
  }

  cout << "Num of cc: " << ccs.size() << endl;
}


int main() {
  testFindCCs();

}
