#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>

class Edge {
  friend class Graph;
  friend class Vertex;
 private:
  int src;
  int dest;
  double cost;
  Edge(int s, int d, double c = 1.0) :
      src(s), dest(d), cost(c) {}
 public:
  bool contains(int vid);
  int otherEnd(int thisEnd);
};

class Vertex {
  friend class Graph;
 private:
  std::string name;
  std::list<Edge*> adj;
  int indx;
  double dist;
  int prev;
  double scratch;
  Vertex(std::string nm, int i) :
      name(nm), indx(i) {}
 public:
  double getKey() { return scratch; }
  void setKey(double k) { scratch = k; }
  int getPrev() { return prev; }
  void setPrev(int p) { prev = p; }
  std::string getName() { return name; }
  void setName(const std::string& s) { name = s; }
  std::vector<int> getNeighbors();
};

class Graph {
  // Basic operations. Basic operations are implemented in this header
  // file Graph.hpp.
 public:
  Graph() {}
  // Random graph constructor. n is the number of vertices, p is edge
  // possibility.
  Graph(int n, double p);
  ~Graph();

  // Mutation methods:
  bool addVertex(const std::string& vertexName);
  bool addVertex(int vertexTag);
  bool addEdge(const std::string& u, const std::string& v, double cost = 1.0);
  bool addEdge(int uTag, int vTag, double cost = 1.0);
  void clear();

  // Vertex queries:
  int getVertexIndex(const std::string& vname) const;
  Vertex* getVertex(int index) const;
  Vertex* getVertex(const std::string& vname) const;
  int getNumOfVertices() const;

  // Adjacency queries:
  std::vector<Vertex*> getNeighbors(std::string vname) const;
  std::vector<Vertex*> getNeighbors(int uid) const;
  std::vector<Vertex*> getNeighbors(Vertex* u) const;

  bool isAdjacent(const std::string& uname, const std::string& vname) const;
  bool isAdjacent(int uid, int vid) const;
  bool isAdjacent(Vertex* u, Vertex* v) const;

  // Edge queries:
  int getNumOfEdges() const;
  Edge* getEdge(int uid, int vid) const;
  Edge* getEdge(const std::string& uname, const std::string& vname) const;
  Edge* getEdge(Vertex* u, Vertex* v) const;

  double getEdgeWeight(int uid, int vid) const;
  double getEdgeWeight(const std::string& uname, const std::string& vname) const;
  double getEdgeWeight(Vertex* u, Vertex* v) const;

  // I/O
  void toDot(std::ostream& out) const;
  void fromTxt(std::istream& in);
  void toTxt(std::ostream& out) const;

 private:
  std::map<std::string,int> vertexMap;
  std::vector<Vertex*> vertexVec;
  std::vector<Edge*> edgeVec;

  // Algorithms:
  // Algorithms are implemented in Graph.algo.hpp.
 public:
  struct MSTState {
    double cost;
    double diameter;
    int nccs;
    MSTState() : cost(0.0), diameter(0.0), nccs(0) {}
  };

  std::vector<std::vector<int> > findCCs() const;
  int getNumOfCCs() const;
  Graph findMST(const std::string&) const;
  std::vector<Graph> findMSTs() const;
  double calcMSTCost(const std::string&) const;
  int calcTreeDiameter() const;
  MSTState calcAvgMSTState() const;

  std::vector<double> dijsktraSP(Vertex*) const;
  std::vector<double> dijsktraSP(const std::string&) const;
  std::vector<int> bfsSP(Vertex*) const;


 private:
  void findMST(Vertex*, const std::vector<int>&, Graph&, double&) const;
  void findCCHelper(Vertex*, std::map<int, bool>&, std::vector<int>&) const;

  class VertexCompByDist {
    std::vector<double> dist;
   public:
    VertexCompByDist(std::vector<double>& d) : dist(d) {}
    bool operator()(Vertex* lhs, Vertex* rhs) const {
      if (dist[lhs->indx] == dist[rhs->indx])
        return lhs->getName() < rhs->getName();
      return dist[lhs->indx] < dist[rhs->indx];
    }
  };
};


// Implementations:

bool Edge::contains(int i) {
  return i == src || i == dest;
}

int Edge::otherEnd(int thisEnd) {
  if (thisEnd == src)
    return dest;
  else if (thisEnd == dest)
    return src;
  else
    return -1;
}

std::vector<int> Vertex::getNeighbors() {
  std::vector<int> vids;
  std::list<Edge*>::iterator eit = adj.begin();
  std::list<Edge*>::iterator en = adj.end();
  while (eit != en) {
    vids.push_back((*eit)->otherEnd(indx));
    ++eit;
  }
  return vids;
}


std::string itoa(int i) {
  std::stringstream ss;
  ss << i;
  return ss.str();
}

Graph::Graph(int n, double p) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  // Generate vertices:
  for (int i = 0; i < n; ++i)
    addVertex("V" + itoa(i));

  // Generate edges:
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double q = distribution(generator);
      if (q < p) {
        std::string u = "V" + itoa(i);
        std::string v = "V" + itoa(j);
        double cost = distribution(generator);
        addEdge(u, v, cost);
      }
    }
  }

}

Graph::~Graph() {
  clear();
}

bool Graph::addVertex(int vertexTag) {
  return addVertex("V"+itoa(vertexTag));
}

bool Graph::addVertex(std::string const & vertexName) {
  int indx = getVertexIndex(vertexName);
  if (indx >= 0) return false;
  indx = vertexVec.size();

  Vertex* v = new Vertex(vertexName, indx);
  vertexVec.push_back(v);

  vertexMap[vertexName] = indx;
  return true;
}

bool Graph::addEdge(const std::string& src,
                    const std::string& dest,
                    double cost) {
  int srci = getVertexIndex(src);
  int desti = getVertexIndex(dest);
  if(srci < 0 || desti < 0) return false;

  Edge* edge = new Edge(srci, desti, cost);
  edgeVec.push_back(edge);

  std::list<Edge*>& adj1 = vertexVec[srci]->adj;
  adj1.push_back(edge);

  std::list<Edge*>& adj2 = vertexVec[desti]->adj;
  adj2.push_back(edge);

  return true;
}

bool Graph::addEdge(int uTag, int vTag, double cost) {
  return addEdge("V"+itoa(uTag), "V"+itoa(uTag), cost);
}

void Graph::clear() {
  std::vector<Vertex*>::iterator it = vertexVec.begin();
  while(it != vertexVec.end()) {
    delete *it;
    ++it;
  }
  std::vector<Edge*>::iterator eit = edgeVec.begin();
  while(eit != edgeVec.end()) {
    delete *eit;
    ++eit;
  }
  vertexMap.clear();
  vertexVec.clear();
  edgeVec.clear();
}

int Graph::getVertexIndex(const std::string& vname) const {
  std::map<std::string,int>::const_iterator it = vertexMap.find(vname);
  if(it == vertexMap.end()) return -1;
  return it->second;
}

Vertex* Graph::getVertex(int index) const {
  if (index >=0 && index < vertexVec.size())
    return vertexVec[index];
  return 0;
}

Vertex* Graph::getVertex(const std::string& vname) const {
  return getVertex(getVertexIndex(vname));
}

int Graph::getNumOfVertices() const {
  return vertexVec.size();
}

std::vector<Vertex*> Graph::getNeighbors(std::string vname) const {
  return getNeighbors(getVertex(vname));
}

std::vector<Vertex*> Graph::getNeighbors(int uid) const {
  return getNeighbors(getVertex(uid));
}

std::vector<Vertex*> Graph::getNeighbors(Vertex* u) const {
  std::vector<Vertex*> nbs;
  if (!u) return nbs;

  std::vector<int> vids = u->getNeighbors();
  for (int i = 0, len = vids.size(); i < len; ++i)
    nbs.push_back(vertexVec[vids[i]]);
  return nbs;
}

bool Graph::isAdjacent(
    const std::string& uname,
    const std::string& vname) const {
  return isAdjacent(getVertex(uname), getVertex(vname));
}

bool Graph::isAdjacent(int uid, int vid) const {
  return isAdjacent(getVertex(uid), getVertex(vid));
}

bool Graph::isAdjacent(Vertex* u, Vertex* v) const {
  return getEdge(u, v) != 0;
}

int Graph::getNumOfEdges() const {
  return edgeVec.size();
}

Edge* Graph::getEdge(int uid, int vid) const {
  return getEdge(getVertex(uid), getVertex(vid));
}

Edge* Graph::getEdge(const std::string& uname, const std::string& vname) const {
  return getEdge(getVertex(uname), getVertex(vname));
}

Edge* Graph::getEdge(Vertex* u, Vertex* v) const {
  std::list<Edge*>::iterator eit = u->adj.begin();
  std::list<Edge*>::iterator en = u->adj.end();
  int uid = u->indx;
  int vid = v->indx;

  while (eit != en) {
    if ((*eit)->otherEnd(uid) == vid)
      return *eit;
    ++eit;
  }
  return 0;
}

double Graph::getEdgeWeight(int uid, int vid) const {
  return getEdgeWeight(getVertex(uid), getVertex(vid));
}

double Graph::getEdgeWeight(const std::string& uname,
                            const std::string& vname) const {
  return getEdgeWeight(getVertex(uname), getVertex(vname));
}

double Graph::getEdgeWeight(Vertex* u, Vertex* v) const {
  Edge* e = getEdge(u, v);
  return e ? e->cost : -1.0;
}

void Graph::toDot(std::ostream& out) const {
  if (vertexVec.size() == 0) return;

  std::map<int, bool> visited;
  out << "graph g {\n";

  std::vector<Vertex*>::const_iterator vit = vertexVec.begin();
  while(vit != vertexVec.end()) {
    out << "  " << (*vit)->indx << " [label=\"";
    out << (*vit)->name;
    out << "\"]\n";
    ++vit;
  }

  std::vector<Edge*>::const_iterator eit = edgeVec.begin();
  while(eit != edgeVec.end()) {
    out << "  " << (*eit)->src;
    out << " -- " << (*eit)->dest;
    out << " [label=\"" << (*eit)->cost << "\"]\n";
    ++eit;
  }
  out << "}\n";
}

void Graph::fromTxt(std::istream& in) {
  clear();
  while (in) {
    int u, v;
    double w;
    in >> u >> v >> w;
    addVertex(u);
    addVertex(v);
    addEdge(u, v, w);
  }
}

void Graph::toTxt(std::ostream& out) const {
  for (size_t i = 0, len = edgeVec.size(); i < len; ++i) {
    Edge* edge = edgeVec[i];
    out << edge->src << " " << edge->dest << " ";
    out << edge->cost << "\n";
  }
}

#endif /* _GRAPH_H_ */
