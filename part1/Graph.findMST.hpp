#ifndef _GRAPH_FINDMST_H_
#define _GRAPH_FINDMST_H_

#include <vector>
#include <set>
#include <limits>

#include "Graph.hpp"

using namespace std;

class VertexComp {
 public:
  bool operator()(Vertex* lhs, Vertex* rhs) const {
    return lhs->getKey() < rhs->getKey();
  }
};

void Graph::findCCHelper(Vertex* v, map<int, bool>& visited,
                         std::vector<int>& out) const {
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

std::vector<std::vector<int> > Graph::findCCs() const {
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

std::ostream& operator<<(std::ostream& out, const set<Vertex*, VertexComp>& s) {
  std::set<Vertex*, VertexComp>::const_iterator sit = s.begin();
  std::set<Vertex*, VertexComp>::const_iterator en = s.end();
  while (sit != en) {
    out << (*sit)->getName() << " ";
    out << (*sit)->getKey() << " ";
    ++sit;
  }
  return out;
}

Graph Graph::findMST(Vertex* s) {
  Graph mst;
  set<Vertex*, VertexComp> q;

  std::vector<int> vids;
  map<int, bool> visited;
  findCCHelper(s, visited, vids);

  // Edge weight is from 0 to 1, so 10.0 can be
  // used as "infinity".
  double inf = 10.0;
  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = vertexVec[vids[i]];
    u->setPrev(-1);
    u->setKey(inf);

    // std::set do not allow duplicate keys
    inf += 0.1;
  }

  s->setKey(0.0);

  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = vertexVec[vids[i]];
    q.insert(u);
  }

  while (q.size() > 0) {
    set<Vertex*, VertexComp>::iterator sit = q.begin();
    Vertex* u = *sit;

    q.erase(sit);

    mst.addVertex(u->name);

    if (u->getPrev() != -1) {
      Vertex* prev = vertexVec[u->getPrev()];
      std::list<Edge*>::iterator eit = u->adj.begin();
      std::list<Edge*>::iterator en = u->adj.end();
      while (eit != en) {
        if ((*eit)->otherEnd(u->indx) == u->getPrev())
          break;
        ++eit;
      }

      mst.addEdge(u->name, prev->name, (*eit)->cost);
    }


    std::list<Edge*>::iterator eit = u->adj.begin();
    std::list<Edge*>::iterator en = u->adj.end();

    while (eit != en) {
      Edge* edge = *eit;
      int vid = edge->otherEnd(u->indx);
      Vertex* v = vertexVec[vid];

      if (q.count(v) > 0 && edge->cost < v->getKey()) {
        q.erase(v);
        v->setKey(edge->cost);
        v->setPrev(u->indx);
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
