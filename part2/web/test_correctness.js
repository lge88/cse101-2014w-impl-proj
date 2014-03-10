
var can = document.getElementById("canvas");
var ctx = can.getContext("2d");

function visualizeFiles(ptsFile, hullFile, ctx) {
  var pointset, points, hull;
  var r1 = new FileReader();
  r1.onload = function(e) {
    var content = e.target.result;
    points = loadPointsFromText(content);
    maybeDraw();
  }
  r1.readAsText(ptsFile);

  var r2 = new FileReader();
  r2.onload = function(e) {
    var content = e.target.result;
    hull = loadPointsFromText(content);
    maybeDraw();
  }
  r2.readAsText(hullFile);

  function maybeDraw() {
    if (points && hull) visualize(points, hull, ctx);
  }
}

function loadPointsFromText(str) {
  return str.trim()
    .split("\n")
    .map(function(line) {
      return line.trim()
        .split(/\s+/)
        .map(function(x) { return parseFloat(x); });
    });
}

function visualize(points, hull, ctx) {
  var pointset = new Pointset(points);
  ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
  pointset.drawPoints(ctx);
  pointset.drawPolygonPoints(ctx, hull);
}

function update() {
  var ptsFile = document.getElementById("pts_file").files[0];
  var hullFile = document.getElementById("hull_file").files[0];
  visualizeFiles(ptsFile, hullFile, ctx);
}

update();
document.getElementById("update").onclick = update;
