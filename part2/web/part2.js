var Pointset = require("./Pointset");
var grahamScan = require("./grahamScan");

function runOneCase(N, r, k) {
  var pointset;
  var counter = 0;
  var totalIter = 0, iters = new Array(k);
  var avg = 0, stdev = 0;
  var i = 0;
  var indxMap;
  var indices;

  for (i = 0; i < k; ++i) {
    pointset = new Pointset(N, r);
    while (pointset && pointset.points.length > 0) {
      indices = grahamScan(pointset.points);
      ++counter;

      indxMap = indices.reduce(function(res, cur) {
        res[cur] = true;
        return res;
      }, {});

      pointset.points = pointset.points.filter(function(p, indx) {
        return !indxMap[indx];
      });
    }
    totalIter += counter;
    iters[i] = counter;
    counter = 0;
  }

  avg = totalIter/k;
  for (i = 0; i < k; ++i)
    stdev += (iters[i]-avg)*(iters[i]-avg);

  stdev = Math.sqrt(stdev/k);

  return [avg, stdev];
}


function toFixWidth(str, width) {
  var out;
  if (str.length > width)
    return str.substr(0, width);
  else
    return str + padding(width - str.length);
}

function padding(w) {
  var out = []
  while (w-- > 0) out.push(" ");
  return out.join("");
}

function str(n) { return "" + n; }

function printHeader() {
  var out = [];
  out.push(toFixWidth("# N", 5));
  out.push(toFixWidth("k", 5));
  out.push(toFixWidth("r", 5));
  out.push(toFixWidth("avgIters", 15));
  out.push(toFixWidth("stdev", 15));
  console.log(out.join(""));
}

function printRow(N, k, r, avg, stdev) {
  var out = [];
  out.push(toFixWidth(str(N), 5));
  out.push(toFixWidth(str(k), 5));
  out.push(toFixWidth(r.toFixed(1), 5));
  out.push(toFixWidth(avg.toFixed(8), 15));
  out.push(toFixWidth(stdev.toFixed(8), 15));
  console.log(out.join(""));
}


var Ns = [20, 50, 100, 200, 500, 1000, 2000, 3000];
var rs = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9];
var k = 500;
var N, r, avg, stdev, tmp;
var startTime, endTime;

var i = 0, j = 0;
var nL = Ns.length;
var rL = rs.length;

printHeader();

startTime = Date.now();
while (i < nL) {
  while (j < rL) {
    N = Ns[i];
    r = rs[j];
    tmp = runOneCase(N, r, k);
    avg = tmp[0];
    stdev = tmp[1];
    printRow(N, k, r, avg, stdev);
    ++j;
  }
  j = 0;
  ++i;
}
endTime = Date.now();

console.log("# time: " + (endTime-startTime)/1000 + " seconds.");
