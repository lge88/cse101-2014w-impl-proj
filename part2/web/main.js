function clearCanvas(ctx) {
  ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.width);
}

var can = document.getElementById("canvas");
var ctx = can.getContext("2d");

var pointset = new Pointset([
  [0, 0],
  [1, 1],
  [1, -0.5],
  [-0.75, -0.75],
  [-1, 1]
]);

var N = 50;
var pointset = new Pointset(N);


var indices = grahamScan(pointset.points);

pointset.drawPoints(ctx);
pointset.drawPolygon(ctx, indices);
