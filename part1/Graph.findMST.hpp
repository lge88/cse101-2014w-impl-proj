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
                         vector<int>& out) const {
  visited[v->indx] = true;
  out.push_back(v->indx);

  list<Edge*>::iterator eit = v->adj.begin();
  list<Edge*>::iterator en = v->adj.end();

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

vector<vector<int> > Graph::findCCs() const {
  vector<vector<int> > res;
  map<int, bool> visited;

  for (size_t i = 0, len = vertexVec.size(); i < len; ++i) {
    Vertex* u = vertexVec[i];
    if (!visited[u->indx]) {
      vector<int> out;
      findCCHelper(u, visited, out);
      res.push_back(out);
    }
  }
  return res;
}

Graph Graph::findMST(const string& name) const {
  int vid = vertexMap.at(name);
  Vertex* s = vertexVec[vid];
  Graph mst;
  double cost;

  map<int, bool> visited;
  vector<int> vids;
  findCCHelper(s, visited, vids);

  findMST(s, vids, mst, cost);
  return mst;
}

ostream& operator<<(ostream& out, const set<Vertex*, VertexComp>& s) {
  set<Vertex*, VertexComp>::const_iterator sit = s.begin();
  set<Vertex*, VertexComp>::const_iterator en = s.end();
  while (sit != en) {
    out << (*sit)->getName() << " ";
    out << (*sit)->getKey() << " ";
    ++sit;
  }
  return out;
}

// findMST using Prim's algorthtm.
// Input:
//   s: start vertex
//   vids: the vertex ids of the connected component
//         that contains s
// Output:
//   mst: the MST as a graph
//   totalCost: total edge cost of the MST.
void Graph::findMST(Vertex* s, const vector<int>& vids,
                    Graph& mst, double& totalCost) const {

  // Use std::set(RB-tree) as a priority queue.
  set<Vertex*, VertexComp> q;

  // Edge weight is from 0.0 to 1.0, so 10.0 can be
  // used as "infinity".
  double inf = 10.0;
  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = vertexVec[vids[i]];
    u->setPrev(-1);
    u->setKey(inf);

    // set do not allow duplicate keys
    inf += 0.1;
  }

  s->setKey(0.0);

  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = vertexVec[vids[i]];
    q.insert(u);
  }

  totalCost = 0.0;
  while (q.size() > 0) {
    set<Vertex*, VertexComp>::iterator sit = q.begin();
    Vertex* u = *sit;

    q.erase(sit);

    mst.addVertex(u->name);

    int previ = u->getPrev();
    if (previ != -1) {
      Vertex* prev = vertexVec[previ];
      list<Edge*>::iterator eit = u->adj.begin();
      list<Edge*>::iterator en = u->adj.end();
      while (eit != en) {
        if ((*eit)->otherEnd(u->indx) == previ)
          break;
        ++eit;
      }

      totalCost += (*eit)->cost;
      mst.addEdge(u->name, prev->name, (*eit)->cost);
      // TODO: somehow update diameter here?

    }

    list<Edge*>::iterator eit = u->adj.begin();
    list<Edge*>::iterator en = u->adj.end();

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
}

Graph::MSTState Graph::calcAvgMSTState() const {
  vector<vector<int> > ccs = findCCs();
  int nccs = ccs.size();

  Graph::MSTState res;

  for (int i = 0; i < nccs; ++i) {
    const vector<int>& vertIds = ccs[i];
    Vertex* u = getVertexByIndex(vertIds[0]);

    double totalCost = 0.0;
    Graph mst;
    findMST(u, vertIds, mst, totalCost);

    res.cost += totalCost;
    res.diameter += mst.calcDiameter();
  }

  res.cost = res.cost/nccs;
  res.diameter = res.diameter/nccs;
  res.nccs = nccs;

  return res;
}


// TODO:
int Graph::calcDiameter() const {
  return 0;
}

int Graph::getNumOfCCs() const {
  return findCCs().size();
}

vector<Graph> Graph::findMSTs() const {
  vector<Graph> out;
  // TODO:


  return out;
};

#endif /* _GRAPH.FINDMST_H_ */
