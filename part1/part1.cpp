
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "Graph.hpp"
#include "Graph.findMST.hpp"

using namespace std;

int numOfCCs(const Graph& g) {
  return g.findCCs().size();
}

// Input: n - num of vertices, p - edge possibility, k - repeat k times
// Output: avg - average, stdev - standart deviation
void runOneCase(int n, double p, int k, double& avg, double& stdev) {
  vector<int> nums;
  for (int i = 0; i < k; ++i) {
    Graph g(n, p);
    int nccs = numOfCCs(g);
    nums.push_back(nccs);
  }

  avg = 0.0;
  for (int i = 0; i < k; ++i) {
    avg += nums[i];
  }
  cout << "avg: " << avg << endl;
  avg = avg/k;

  stdev = 0.0;
  for (int i = 0; i < k; ++i) {
    stdev += (nums[i]-avg)*(nums[i]-avg);
  }
  stdev = sqrt(stdev/k);
}

int main(int argc, char* argv[]) {
  int n = 10, k = 100;
  if (argc > 1)
    n = atoi(argv[1]);

  if (argc > 2)
    k = atoi(argv[2]);

  double p = 0.00;
  while (p <= 1.01) {
    double avg, stdev;
    runOneCase(n, p, k, avg, stdev);
    cout << p << "  ";
    cout << avg << " ";
    cout << stdev ;
    cout << endl;
    p += 0.02;
  }
}
