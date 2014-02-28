#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>


using namespace std;

template <typename Graph, typename Vertex, typename Edge>
void findCCHelper(const Graph& g, Vertex* v, map<int, bool>& visited,
                  vector<int>& out) {
  int vid = v->getIndx();
  visited[vid] = true;
  out.push_back(vid);

  vector<Vertex*> nbs = g.getNeighbors(v);
  for (int i = 0, len = nbs.size(); i < len; ++i) {
    if (!visited[u->getIndx()]) {
      findCCHelper(u, visited, out);
    }
  }
}

template <typename Graph, typename Vertex, typename Edge>
vector<vector<int> > findCCs(const Graph& g) {
  vector<vector<int> > res;
  map<int, bool> visited;
  int V = g.getNumOfVertices();

  for (int i = 0; i < V; ++i) {
    Vertex* u = g.getVertex(i);
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
    out << "(" << (*sit)->getName() << ", ";
    out << (*sit)->getKey() << ")";
    ++sit;
    if (sit != en)
      out << " ";
  }
  return out;
}



class VertexComp {
 public:
  bool operator()(Vertex* lhs, Vertex* rhs) const {
    if (lhs->getKey() == rhs->getKey())
      return lhs->getName() < rhs->getName();
    return lhs->getKey() < rhs->getKey();
  }
};

// findMST using Prim's algorthtm.
// Input:
//   s: start vertex
//   vids: the vertex ids of the connected component
//         that contains s
// Output:
//   mst: the MST as a graph
//   totalCost: total edge cost of the MST.

template <typename Graph, typename Vertex, typename Edge>
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
    map<int, double>& weights;
  } comp(weights);

  // Use std::set(RB-tree) as a priority queue.
  set<Vertex*, VertexCompByEdgeWeight> q(comp);

  // Init edge weights to infinity, prevs to -1;
  double inf = numeric_limits<double>::max();
  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    weights[vids[i]] = inf;
    prevs[vids[i]] = -1;
  }

  weigths[s->getIndx()] = 0.0;

  for (size_t i = 0, len = vids.size(); i < len; ++i) {
    Vertex* u = g.getVertex(vids[i]);
    q.insert(u);
  }

  // cout << "Init pq: \n";
  // cout << q << endl;

  totalCost = 0.0;
  while (q.size() > 0) {
    // cout << q << endl;

    set<Vertex*, VertexCompByEdgeWeight>::iterator sit = q.begin();
    Vertex* u = *sit;

    q.erase(sit);

    mst.addVertex(u->getName());

    int previ = prevs[u->getIndx()];

    // TODO: not finish yet...
    if (previ != -1) {
      Vertex* prev = g.getVertex[previ];
      Edge* e = g.getEdge(u, prev);

      totalCost += e->cost;
      mst.addEdge(u->name, prev->name, e->cost);
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
  // cout << "q after loop:\n";
  // cout << q << endl;
}

Graph::MSTState Graph::calcAvgMSTState() const {
  vector<vector<int> > ccs = findCCs();
  int nccs = ccs.size();

  Graph::MSTState res;

  for (int i = 0; i < nccs; ++i) {
    const vector<int>& vertIds = ccs[i];
    Vertex* u = getVertex(vertIds[0]);

    double totalCost = 0.0;
    Graph mst;
    findMST(u, vertIds, mst, totalCost);

    res.cost += totalCost;
    res.diameter += mst.calcTreeDiameter();
  }

  res.cost = res.cost/nccs;
  res.diameter = res.diameter/nccs;
  res.nccs = nccs;

  return res;
}

double Graph::calcMSTCost(const std::string& name) const {
  int vid = vertexMap.at(name);
  Vertex* s = vertexVec[vid];
  Graph mst;
  double cost;

  map<int, bool> visited;
  vector<int> vids;
  findCCHelper(s, visited, vids);

  findMST(s, vids, mst, cost);
  return cost;
}

// Precondition: the graph is known to be a tree.
// Using the algorithm from:
// http://algs4.cs.princeton.edu/41undirected/
// Item 26
int Graph::calcTreeDiameter() const {
  if (getNumOfVertices() == 0) return 0;

  Vertex* v = vertexVec[0];
  vector<int> dist = bfsSP(v);

  int wi = 0;
  int d = -1;

  for (int i = 0, len = dist.size(); i < len; ++i) {
    if (dist[i] > d) {
      d = dist[i];
      wi = i;
    }
  }

  Vertex* w = getVertex(wi);
  dist = bfsSP(w);

  d = -1;
  for (int i = 0, len = dist.size(); i < len; ++i) {
    d = max(d, dist[i]);
  }

  return d;
}

int Graph::getNumOfCCs() const {
  return findCCs().size();
}

vector<Graph> Graph::findMSTs() const {
  vector<Graph> out;
  // TODO:


  return out;
};

vector<double> Graph::dijsktraSP(Vertex* s) const {
  vector<double> dist;
  VertexCompByDist comp(dist);
  set<Vertex*, VertexCompByDist> q(comp);

  int V = getNumOfVertices();
  for (int i = 0; i < V; ++i) {
    dist.push_back(numeric_limits<double>::max());
  }

  dist[s->indx] = 0.0;

  for (int i = 0; i < V; ++i)
    q.insert(vertexVec[i]);

  while (!q.empty()) {
    set<Vertex*, VertexCompByDist>::iterator it = q.begin();
    Vertex* u = *it;
    q.erase(it);

    vector<Vertex*> nbs = getNeighbors(u);
    for (int i = 0, len = nbs.size(); i < len; ++i) {
      Vertex* v = nbs[i];
      double w = getEdgeWeight(u, v);
      if (dist[v->indx] > dist[u->indx] + w) {
        q.erase(v);
        dist[v->indx] = dist[u->indx] + w;
        q.insert(v);
      }
    }
  }

  return dist;
}

vector<double> Graph::dijsktraSP(const string& uname) const {
  return dijsktraSP(getVertex(uname));
}

vector<int> Graph::bfsSP(Vertex* s) const {
  vector<int> dist;
  int V = getNumOfVertices();
  int inf = numeric_limits<int>::max();
  for (int i = 0; i < V; ++i) {
    dist.push_back(inf);
  }

  dist[s->indx] = 0;

  queue<Vertex*> q;
  q.push(s);

  while (!q.empty()) {
    Vertex* u = q.front();
    q.pop();

    vector<Vertex*> nbs = getNeighbors(u);
    for (int i = 0, len = nbs.size(); i < len; ++i) {
      Vertex* v = nbs[i];
      if (dist[v->indx] == inf) {
        dist[v->indx] = dist[u->indx] + 1;
        q.push(v);
      }
    }
  }
  return dist;
}
