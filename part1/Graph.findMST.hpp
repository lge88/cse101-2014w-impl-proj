#ifndef _GRAPH.FINDMST_H_
#define _GRAPH.FINDMST_H_

#include <vector>
#include "Graph.hpp"
#include "Graph.findCCs.hpp"

using namespace std;

Graph Graph::findMST() {
  Graph mst;

  return mst;
}


vector<Graph> Graph::findMSTs() {
  vector<Vertex*> sources = findCCs();
  vector<Graph> msts;
  for (size_t i = 0, len = sources.size(); i < len; ++i) {
    msts.push_back(findMST(sources[i]));
  }
  return msts;
}

#endif /* _GRAPH.FINDMST_H_ */
