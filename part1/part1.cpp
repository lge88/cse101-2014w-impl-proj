
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "Graph.hpp"
#include "Graph.findMST.hpp"

using namespace std;

struct Measurements {
  double avgNumOfCCs;
  double stdevNumOfCCs;
  double avgMSTCost;
  double avgMSTDiameter;
 public:
  Measurements() :
      avgNumOfCCs(0.0), stdevNumOfCCs(0.0),
      avgMSTCost(0.0), avgMSTDiameter(0.0) {}
};

// Input: n - num of vertices, p - edge possibility, k - repeat k times
// Output: Measuremens struct with each field init to zero.
void calcMeasurements(int n, double p, int k, Measurements& m) {
  vector<int> nums;
  vector<double> costs;
  vector<int> diameters;

  for (int i = 0; i < k; ++i) {
    Graph g(n, p);
    Graph::MSTState s = g.calcAvgMSTState();
    nums.push_back(s.nccs);
    costs.push_back(s.cost);
    diameters.push_back(s.diameter);
  }

  for (int i = 0; i < k; ++i) {
    m.avgNumOfCCs += nums[i];
    m.avgMSTCost += costs[i];
    m.avgMSTDiameter += diameters[i];
  }

  m.avgNumOfCCs = m.avgNumOfCCs/k;
  m.avgMSTCost = m.avgMSTCost/k;
  m.avgMSTDiameter = m.avgMSTDiameter/k;

  for (int i = 0; i < k; ++i) {
    m.stdevNumOfCCs += (nums[i]-m.avgNumOfCCs)*(nums[i]-m.avgNumOfCCs);
  }
  m.stdevNumOfCCs = sqrt(m.stdevNumOfCCs/k);
}


// Usage: ./part1 100 300
// Output: columns for left to right: n, p, avgNumOfCCs, stdevNumOfCCs,
//         avgMSTCost, avgMSTDiameter
int main(int argc, char* argv[]) {
  int n = 20, k = 300;
  if (argc > 1)
    n = atoi(argv[1]);

  if (argc > 2)
    k = atoi(argv[2]);

  double p = 0.00;
  while (p <= 1.01) {
    Measurements m;
    calcMeasurements(n, p, k, m);
    cout << setw(4) << n;
    cout << setw(6) << p;
    cout << setw(12) << m.avgNumOfCCs;
    cout << setw(12) << m.stdevNumOfCCs;
    cout << setw(12) << m.avgMSTCost;
    cout << setw(12) << m.avgMSTDiameter;
    cout << "\n";
    p += 0.02;
  }
}
