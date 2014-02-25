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
  double scratch;
  Vertex(std::string nm, int i) : name(nm), indx(i) { }
 public:
  double getKey() { return scratch; }
  void setKey(double k) { scratch = k; }
  int getPrev() { return prev; }
  void setPrev(int p) { prev = p; }
  std::string getName() { return name; }
  void setName(const std::string& s) { name = s; }
};

double random0To1() {
  return 1.0 * random() / std::numeric_limits<int>::max();
}

std::string itoa(int i) {
  std::stringstream ss;
  ss << i;
  return ss.str();
}

class Graph {
 private:
  std::map<std::string,int> vertexMap;
  std::vector<Vertex*> vertexVec;
  std::vector<Edge*> edgeVec;

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
      for (int j = i + 1; j < n; ++j) {
        double q = random0To1();
        if (q < p) {
          std::string u = "V" + itoa(i);
          std::string v = "V" + itoa(j);
          addEdge(u, v);
        }
      }
    }

    // TODO: Assign edge weights:
    for (size_t i = 0, len = edgeVec.size(); i < len; ++i) {
      edgeVec[i]->cost = random0To1();
    }

  }

  ~Graph() {
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

    Edge* edge = new Edge(srci, desti, coutt);
    edgeVec.push_back(edge);

    std::list<Edge*>& adj1 = vertexVec[srci]->adj;
    adj1.push_back(edge);

    std::list<Edge*>& adj2 = vertexVec[desti]->adj;
    adj2.push_back(edge);

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

    std::vector<Vertex*>::iterator vit = vertexVec.begin();
    while(vit != vertexVec.end()) {
      out << "  " << (*vit)->indx << " [label=\"";
      out << (*vit)->name;
      out << "\"]\n";
      ++vit;
    }

    std::vector<Edge*>::iterator eit = edgeVec.begin();
    while(eit != edgeVec.end()) {
      out << "  " << (*eit)->src;
      out << " -- " << (*eit)->dest;
      out << " [label=\"" << (*eit)->cost << "\"]\n";
      ++eit;
    }
    out << "}\n";
  }

  std::vector<std::vector<int> > findCCs() const;
  std::vector<Graph> findMSTs();
  Graph findMST(Vertex*);
  Graph findMST(const std::string&);

 private:
  void findCCHelper(Vertex*, std::map<int, bool>&, std::vector<int>&) const;

};

#endif /* _GRAPH_H_ */
