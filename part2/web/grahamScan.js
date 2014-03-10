
// > 0 if p1->p2->p3 is counter-clock-wise.
// = 0 if p1->p2->p3 is colinear.
// < 0 if p1->p2->p3 is clock-wise.
function ccw(p1, p2, p3) {
  return (p2[0] - p1[0])*(p3[1] - p1[1]) - (p2[1] - p1[1])*(p3[0] - p1[0]);
}

function findLowestYIndx(points) {
  var i = 0, len = points.length;
  var indx = -1, ymin = Infinity, y;

  for (; i < len; ++i) {
    y = points[i][1];
    if (y < ymin || (y == ymin && points[i][0] < points[indx][0])) {
      indx = i;
      ymin = y;
    }
  }

  return indx;
}

function swap(arr, i, j) {
  var tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

// In degree.
function polarAngle(p0, p) {
  var x = p[0] - p0[0];
  var y = p[1] - p0[1];
  if (x == 0 && y ==0) return -Infinity;
  var ang = 180*Math.atan2(y, x)/Math.PI;
  return ang >= 0.0 ? ang : 360.0 + ang;
}

function less(a, b) { return a - b; }

function sort(A, comp) {
  return qsort(A, 0, A.length - 1, comp || less);
}

function qsort(A, p, r, comp) {
  var q;
  if (p < r) {
    q = randomizedParition(A, p, r, comp);
    qsort(A, p, q - 1, comp);
    qsort(A, p + 1, r, comp);
  }
  return A;
}

// Randomly pick a int from set { p, p+1, ..., r-1, r }
function randomPick(p, r) {
  return p + Math.floor((r-p+1)*Math.random());
}

function randomizedParition(A, p, r, comp) {
  var i = randomPick(p, r);
  swap(A, i, r);
  return partition(A, p, r, comp);
}

function partition(A, p, r, comp) {
  var x = A[r];
  var i = p - 1;
  var j;
  for (j = p; j <= r - 1; ++j) {
    if (comp(A[j], x) <= 0) {
      ++i;
      swap(A, i, j);
    }
  }
  swap(A, i+1, r);
  return i+1;
}

function Stack() {
  var data = [];
  return {
    push: function(x) { data.push(x); },
    pop: function() { return data.pop(); },
    top: function() { return data[data.length - 1]; },
    size: function() { return data.length; },
    empty: function() { return data.length == 0; },
    nextToTop: function() { return data[data.length - 2]; },
    toArray: function() { return data; }
  };
}

function distSq(p1, p2) {
  var dx = p2[0] - p1[0], dy = p2[1] - p1[1];
  return dx*dx+dy*dy;
}

// Given points as 2D array, this algorithm points indices that makes
// the convex hull polygon.
function grahamScan(points) {
  var N = points.length;
  if (N == 0) return [];
  if (N == 1) return [0];
  if (N == 2) return [0, 1];

  // console.time("findLowest");
  var yi = findLowestYIndx(points);
  // console.timeEnd("findLowest");
  swap(points, 0, yi);
  p0 = points[0];

  var compare = function(p1, p2) {
    if (p1[0] == p0[0] && p1[1] == p0[1])
      return -1;
    if (p2[0] == p0[0] && p2[1] == p0[1])
      return 1;
    var o = ccw(p0, p1, p2);
    if (o == 0)
      return distSq(p0, p1) - distSq(p0, p1);
    return -o;
  };

  // console.time("sort");
  // home made quick sort is much slower than Array.prototype.sort.
  // qsort(points, 1, N-1, compare);
  points.sort(compare);
  // console.timeEnd("sort");

  var s = new Stack();
  s.push(0);
  s.push(1);
  s.push(2);

  // console.time("scan");
  var i, a, b;
  for (i = 3; i < N; ++i) {
    a = s.nextToTop();
    b = s.top();
    while (ccw(points[a], points[b], points[i]) <= 0) {
      s.pop();
      a = s.nextToTop();
      b = s.top();
    }
    s.push(i);
  }
  // console.timeEnd("scan");

  return s.toArray();
}

if (typeof module !== "undefined") {
  module.exports = exports = grahamScan;
}
