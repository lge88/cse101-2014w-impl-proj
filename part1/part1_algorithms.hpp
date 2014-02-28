#include <vector>
#include <map>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>


using namespace std;

template <typename Graph>
void findCCHelper(const Graph& g, typename Graph::Vertex* v, map<int, bool>& visited,
                  vector<int>& out) {
  int vid = v->getIndx();
  visited[vid] = true;
  out.push_back(vid);

  vector<typename Graph::Vertex*> nbs = g.getNeighbors(v);
  for (int i = 0, len = nbs.size(); i < len; ++i) {
    typename Graph::Vertex* u = nbs[i];
    if (!visited[u->getIndx()]) {
      findCCHelper(u, visited, out);
    }
  }
}

template <typename Graph>
vector<vector<int> > findCCs(const Graph& g) {
  vector<vector<int> > res;
  map<int, bool> visited;
  int V = g.getNumOfVertices();

  for (int i = 0; i < V; ++i) {
    typename Graph::Vertex* u = g.getVertex(i);
    if (!visited[u->getIndx()]) {
      vector<int> out;
      findCCHelper(u, visited, out);
      res.push_back(out);
    }
  }
  return res;
}

ostream& operator<<(ostream& out, const vector<int>& s) {
  vector<int>::const_iterator it = s.begin();
  vector<int>::const_iterator en = s.end();
  while (it != en) {
    out << *it << " ";
    ++it;
  }
  return out;
}

template <class Graph, class Vertex>
Graph findMST(const Graph& g, const string& vertexName) {
  Vertex* s = g.getVertex(vertexName);
  Graph mst;
  double cost;

  map<int, bool> visited;
  vector<int> vids;
  findCCHelper(s, visited, vids);

  findMST(s, vids, mst, cost);
  return mst;
}

template <class Vertex, class VertexComp>
ostream& operator<<(ostream& out, const set<Vertex*, VertexComp>& s) {
  typename set<Vertex*, VertexComp>::const_iterator sit = s.begin();
  typename set<Vertex*, VertexComp>::const_iterator en = s.end();
  while (sit != en) {
    out << "(" << (*sit)->getName() << ", ";
    out << (*sit)->getKey() << ")";
    ++sit;
    if (sit != en)
      out << " ";
  }
  return out;
}

// class VertexComp {
//  public:
//   bool operator()(Vertex* lhs, Vertex* rhs) const {
//     if (lhs->getKey() == rhs->getKey())
//       return lhs->getName() < rhs->getName();
//     return lhs->getKey() < rhs->getKey();
//   }
// };

// findMST using Prim's algorthtm.
// Input:
//   s: start vertex
//   vids: the vertex ids of the connected component
//         that contains s
// Output:
//   mst: the MST as a graph
//   totalCost: total edge cost of the MST.

template <typename Graph>
void findMST(const Graph& g, Vertex* s, const vector<int>& vids,
             Graph& mst, double& totalCost) {
// void Graph::findMST(Vertex* s, const vector<int>& vids,
//                     Graph& mst, double& totalCost) const {

  map<int, double> weights;
  map<int, int> prevs;

  struct VertexCompByEdgeWeight {
    VertexCompByEdgeWeight(const map<int, double>& w) : weights(w) {}
    bool operator()(const Vertex*& u, const Vertex*& v) const {
      int uid = u->getIndx(), vid = v->getIndx();
      if (weights.at(uid) == weights.at(vid))
        return uid < vid;
      return weights.at(uid) < weights.at(vid);
    }
   private:
    const map<int, double>& weights;
  } comp(weights);

  // Use std::set(RB-tree) as a priority queue.
  set<Vertex*, VertexCompByEdgeWeight> q(comp);

  // Init edge weights to infinity, prevs to -1;
  double inf = numeric_limits<double>::max();
  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    weights[vids[i]] = inf;
    prevs[vids[i]] = -1;
  }

  weights[s->getIndx()] = 0.0;

  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = g.getVertex(vids[i]);
    q.insert(u);
  }

  // cout << "Init pq: \n";
  // cout << q << endl;

  totalCost = 0.0;
  while (q.size() > 0) {
    // cout << q << endl;

    typename set<Vertex*, VertexCompByEdgeWeight>::iterator sit = q.begin();
    Vertex* u = *sit;

    q.erase(sit);

    mst.addVertex(u->getName());

    int previ = prevs[u->getIndx()];

    // TODO: not finish yet...
    if (previ != -1) {
      Vertex* prev = g.getVertex(previ);
      Edge* e = g.getEdge(u, prev);

      totalCost += e->getCost();
      mst.addEdge(u->getName(), prev->getName(), e->getCost());
      // TODO: somehow update diameter here?

    }

    vector<Edge*> edges = g.getEdges(u);

    for (int i = 0, len = edges.size(); i < len; ++i) {
      Edge* e = edges[i];
      int vid = e->otherEnd(u->getIndx());
      Vertex* v = g.getVertex(vid);

      if (q.count(v) > 0 && e->getCost() < weights[v->getIndx()] ) {
        q.erase(v);
        weights[v->getIndx()] = e->getCost();
        prevs[v->getIndx()] = u->getIndx();
        q.insert(v);
      }
    }

  }
  // cout << "q after loop:\n";
  // cout << q << endl;
}

struct MSTState {
  double cost;
  double diameter;
  int nccs;
  MSTState() : cost(0.0), diameter(0.0), nccs(0) {}
};

template <typename Graph>
MSTState calcAvgMSTState(const Graph& g) {
  vector<vector<int> > ccs = findCCs(g);
  int nccs = ccs.size();

  MSTState res;

  for (int i = 0; i < nccs; ++i) {
    const vector<int>& vertIds = ccs[i];
    Vertex* u = g.getVertex(vertIds[0]);

    double totalCost = 0.0;
    Graph mst;
    findMST(g, u, vertIds, mst, totalCost);

    res.cost += totalCost;
    res.diameter += calcTreeDiameter(mst);
  }

  res.cost = res.cost/nccs;
  res.diameter = res.diameter/nccs;
  res.nccs = nccs;

  return res;
}

template <class Graph>
double calcMSTCost(const Graph& g, const std::string& name) {

  Vertex* s = g.getVertex(name);
  Graph mst;
  double cost;

  map<int, bool> visited;
  vector<int> vids;
  findCCHelper(g, s, visited, vids);

  findMST(g, s, vids, mst, cost);
  return cost;
}

// Precondition: the graph is known to be a tree.
// Using the algorithm from:
// http://algs4.cs.princeton.edu/41undirected/
// Item 26
template <class Graph>
int calcTreeDiameter(const Graph& g) {

  if (g.getNumOfVertices() == 0) return 0;

  Vertex* v = g.getVertex(0);
  vector<int> dist = bfsSP(g, v);

  int wi = 0;
  int d = -1;

  for (int i = 0, len = dist.size(); i < len; ++i) {
    if (dist[i] > d) {
      d = dist[i];
      wi = i;
    }
  }

  Vertex* w = g.getVertex(wi);
  dist = bfsSP(w);

  d = -1;
  for (int i = 0, len = dist.size(); i < len; ++i) {
    d = max(d, dist[i]);
  }

  return d;
}

template <class Graph>
int getNumOfCCs(const Graph& g) {
  return findCCs(g).size();
}


// vector<Graph> Graph::findMSTs() const {
//   vector<Graph> out;
//   // TODO:


//   return out;
// };

template<class V>
class VertexCompByDist {
  const std::vector<double>& dist;
 public:
  VertexCompByDist(const std::vector<double>& d) : dist(d) {}
  bool operator()(const V*& lhs, const V*& rhs) const {
    if (dist[lhs->getIndx()] == dist[rhs->getIndx()])
      return lhs->getName() < rhs->getName();
    return dist[lhs->getIndx()] < dist[rhs->getIndx()];
  }
};

template <class Graph>
vector<double> dijsktraSP(const Graph& g, Graph::Vertex* s) {

  vector<double> dist;

  VertexCompByDist<Vertex> comp(dist);
  set<Vertex*, VertexCompByDist<Vertex> > q(comp);

  int V = g.getNumOfVertices();
  for (int i = 0; i < V; ++i) {
    dist.push_back(numeric_limits<double>::max());
  }

  dist[s->getIndx()] = 0.0;

  for (int i = 0; i < V; ++i)
    q.insert(g.getVertex(i));

  while (!q.empty()) {
    typename set<Vertex*, VertexCompByDist<Vertex> >::iterator it = q.begin();
    Vertex* u = *it;
    q.erase(it);

    vector<Vertex*> nbs = g.getNeighbors(u);
    for (int i = 0, len = nbs.size(); i < len; ++i) {
      Vertex* v = nbs[i];
      double w = getEdgeWeight(u, v);
      if (dist[v->getIndx()] > dist[u->getIndx()] + w) {
        q.erase(v);
        dist[v->getIndx()] = dist[u->getIndx()] + w;
        q.insert(v);
      }
    }
  }

  return dist;
}

template <class Graph>
vector<double> dijsktraSP(const Graph& g, const string& uname) {
  return dijsktraSP(g.getVertex(uname));
}

template <class Graph, class Vertex>
vector<int> bfsSP(const Graph& g, Vertex* s) {
  vector<int> dist;
  int V = g.getNumOfVertices();
  int inf = numeric_limits<int>::max();
  for (int i = 0; i < V; ++i) {
    dist.push_back(inf);
  }

  dist[s->getIndx()] = 0;

  queue<Vertex*> q;
  q.push(s);

  while (!q.empty()) {
    Vertex* u = q.front();
    q.pop();

    vector<Vertex*> nbs = g.getNeighbors(u);
    for (int i = 0, len = nbs.size(); i < len; ++i) {
      Vertex* v = nbs[i];
      if (dist[v->getIndx()] == inf) {
        dist[v->getIndx()] = dist[u->getIndx()] + 1;
        q.push(v);
      }
    }
  }
  return dist;
}
