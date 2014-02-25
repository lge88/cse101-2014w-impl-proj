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

// class Edge {
//   friend class Graph;
//   friend class Vertex;
//  private:
//   int src;
//   int dest;
//   double cost;
//   Edge(int s, int d, double c = 1.0) : src(s), dest(d), cost(c) {}
// };

class Edge {
  friend class Graph;
  friend class Vertex;
 private:
  int src;
  int dest;
  double cost;
  Edge(int s, int d, double c = 1.0) : src(s), dest(d), cost(c) {}
 public:
  int otherEnd(int thisEnd) {
    if (thisEnd == src)
      return dest;
    else
      return src;
  }
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

double random0To1() {
  return random() / numeric_limits<int>::max();
}

std::string itoa(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

class Graph {
 private:
  std::map<std::string,int> vertexMap;
  std::vector<Vertex*> vertexVec;
  std::vector<Edge*> edgeVec;

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
      if (!visited[u->indx]) {
        out << "  " << v->indx;
        out << " -- " << u->indx << "\n";
        toDotHelper(u, visited, out);
      }
      ++it;
    }
  }

 public:
  Graph() {}

  Graph(int n, double p) {
    srand(time(0));

    // Generate vertices:
    for (int i = 0; i < n; ++i) {
      addVertex("V" + itoa(i));
    }

    // Generate edges:
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        double q = random0To1();
        if (q < p) {
          std::string u = "V" + itoa(i);
          std::string v = "V" + itoa(j);
          addUndirectedEdge(u, v);
        }
      }
    }

    // Assign edge weights:


  }

  ~Graph() {
    std::vector<Vertex*>::iterator it = vertexVec.begin();
    while(it != vertexVec.end()) {
      delete *it;
      ++it;
    }
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

    // std::list<Edge*> & adj = vertexVec[srci]->adj;
    // adj.push_back(new Edge(srci,desti,coutt));


    Edge* edge = new Edge(srci, desti, coutt);
    edgeVec.push_back(edge);

    std::list<Edge*>& adj1 = vertexVec[srci]->adj;
    adj1.push_back(edge);

    std::list<Edge*>& adj2 = vertexVec[desti]->adj;
    adj2.push_back(edge);


    return true;
  }

  bool addUndirectedEdge(std::string src, std::string dest, double coutt = 1.0) {
    bool ok = addEdge(src, dest, coutt);
    ok = ok && addEdge(dest, src, coutt);
    return ok;
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

  std::vector<Vertex*> findCCs();
  Graph findMST(Vertex*);
  std::vector<Graph> findMSTs(Vertex*);

};

#endif /* _GRAPH_H_ */
