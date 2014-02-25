#ifndef _GRAPH.FINDMST_H_
#define _GRAPH.FINDMST_H_

#include <vector>
#include <set>
#include <limits>

#include "Graph.hpp"
#include "Graph.findCCs.hpp"

using namespace std;

class VertexComp {
 public:
  bool operator()(Vertex* lhs, Vertex* rhs) const {
    return lhs->getKey() < rhs->getKey();
  }
};

void Graph::findCCHelper(Vertex* v, map<int, bool>& visited,
                         std::vector<int>& out) {
  visited[v->indx] = true;
  out.push_back(v->indx);

  std::list<Edge*>::iterator eit = v->adj.begin();
  std::list<Edge*>::iterator en = v->adj.end();

  while (eit != en) {
    Edge* edge = *eit;
    int uid = edge->otherEnd(v->indx);
    Vertex* u = vertexVec[uid];

    if (!visited[u->indx]) {
      findCCHelper(u, visited, out);
    }
    ++eit;
  }
}

std::vector<std::vector<int> > Graph::findCCs() {
  std::vector<std::vector<int> > res;
  map<int, bool> visited;

  for (size_t i = 0, len = vertexVec.size(); i < len; ++i) {
    Vertex* u = vertexVec[i];
    if (!visited[u->indx]) {
      std::vector<int> out;
      findCCHelper(u, visited, out);
      res.push_back(out);
    }
  }
  return res;
}

Graph Graph::findMST(const std::string& name) {
  int vid = vertexMap[name];
  Vertex* s = vertexVec[vid];
  return findMST(s);
}

Graph Graph::findMST(Vertex* s) {
  Graph mst;
  set<Vertex*, VertexComp> q;


  std::vector<int> vids;
  map<int, bool> visited;
  findCCHelper(s, visited, vids);

  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = vertexVec[vids[i]];
    u->setPrev();
    u->setKey(numeric_limits<double>::max());
  }

  s->setKey(0.0);

  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = vertexVec[vids[i]];
    q.insert(u);
  }

  while (q.size() > 0) {
    set<Vertex*, VertexComp>::iterator sit = q.begin();
    q.erase(sit);

    Vertex* u = *sit;

    mst.addVertex(u->name);

    std::list<Edge*>::iterator eit = u->adj.begin();
    std::list<Edge*>::iterator en = u->adj.end();

    while (eit != en) {
      Edge* edge = *eit;
      int vid = edge->otherEnd(u->indx);
      Vertex* v = vertexVec[vid];

      if (q.count(v) > 0 && edge->cost < v->getKey()) {

        q.erase(v);
        v->setKey(edge->cost);
        q.insert(v);
      }

      ++eit;
    }




  }




  return mst;
}


vector<Graph> Graph::findMSTs() {
  // vector<Vertex*> sources = findCCs();
  vector<Graph> msts;
  // for (size_t i = 0, len = sources.size(); i < len; ++i) {
    // msts.push_back(findMST(sources[i]));
  // }
  return msts;
}

#endif /* _GRAPH.FINDMST_H_ */
