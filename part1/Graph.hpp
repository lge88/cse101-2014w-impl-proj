
#include <iostream>
#include <vector>
#include <list>
#include <map>

class Edge {
  friend class Graph;
  friend class Vertex;
 private:
  int src;
  int dest;
  double cost;
  Edge(int s, int d, double c = 1.0) : src(s), dest(d), cost(c) {}
};

class Vertex {
  friend class Graph;
 private:
  std::string name;
  std::list<Edge*> adj;
  int indx;
  double dist;
  int prev;
  int scratch;
  Vertex(std::string nm, int i) : name(nm), indx(i) { }
  ~Vertex() {
    std::list<Edge*>::iterator it = adj.begin();
    while(it != adj.end()) { delete *it; ++it; }
  }
};

class Graph {
 private:
  std::map<std::string,int> vertexMap;
  std::vector<Vertex*> vertexVec;

  void toDotHelper(Vertex* v, std::map<int, bool>& visited, std::ostream& out) {
    visited[v->indx] = true;

    out << "  " << v->indx << " [label=\"";
    out << v->name;
    out << "\"]\n";

    std::list<Edge*>& adj = v->adj;
    std::list<Edge*>::iterator it = adj.begin();
    std::list<Edge*>::iterator en = adj.end();

    while (it != en) {
      Vertex* u = vertexVec[(*it)->dest];
      out << "  " << v->indx;
      out << " -- " << u->indx << "\n";
      if (!visited[u->indx]) {
        toDotHelper(u, visited, out);
      }
      ++it;
    }
  }

 public:
  Graph() {}

  Graph(int n, double p) {


  }

  ~Graph() {
    std::vector<Vertex*>::iterator it = vertexVec.begin();
    while(it != vertexVec.end()) { delete *it; ++it; }
  }

  bool addVertex(std::string const & vertexName) {
    int indx = getVertexIndex(vertexName);
    if (indx >= 0) return false;
    indx = vertexVec.size();

    Vertex* v = new Vertex(vertexName, indx);
    vertexVec.push_back(v);

    vertexMap[vertexName] = indx;
    return true;
  }

  bool addEdge(std::string src, std::string dest, double coutt = 1.0) {
    int srci = getVertexIndex(src);
    int desti = getVertexIndex(dest);
    if(srci < 0 || desti < 0) return false;

    std::list<Edge*> & adj = vertexVec[srci]->adj;
    adj.push_back(new Edge(srci,desti,coutt));
    return true;
  }

  int getVertexIndex(std::string vname) {
    std::map<std::string,int>::iterator it = vertexMap.find(vname);
    if(it == vertexMap.end()) return -1;
    return it->second;
  }

  void toDot(std::ostream& out) {
    if (vertexVec.size() == 0) return;

    std::map<int, bool> visited;
    out << "graph g {\n";
    toDotHelper(vertexVec[0], visited, out);
    out << "}\n";
  }
};
