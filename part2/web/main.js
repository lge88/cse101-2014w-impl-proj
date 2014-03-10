function clearCanvas(ctx) {
  ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.width);
}

function runDemo(N, r, speed) {
  var pointset = null;
  var indices = [];
  var counter = 0;
  var aid = null

  function animate() {
    if (pointset && pointset.points.length > 0) {
      indices = grahamScan(pointset.points);
      ++counter;

      // IO:
      clearCanvas(ctx);
      pointset.drawPoints(ctx);
      pointset.drawPolygon(ctx, indices);
      document.getElementById("counter").textContent = counter;

      var indxMap = indices.reduce(function(res, cur) {
        res[cur] = true;
        return res;
      }, {});

      pointset.points = pointset.points.filter(function(p, indx) {
        return !indxMap[indx];
      });
      aid = setTimeout(animate, speed);
    } else {
      if (counter > 0) {
        document.getElementById("last_total").textContent = counter;
        counter = 0;
      }
      pointset = new Pointset(N, r);
      animate();
    }
  }

  animate();

  return function() { clearTimeout(aid); }
}


var can = document.getElementById("canvas");
var ctx = can.getContext("2d");
var updateBtn = document.getElementById("update");
var stop = function() {};

function updateGUI(ev) {
  // Input:
  var N = parseInt(document.getElementById("N").value);
  var r = parseFloat(document.getElementById("r").value);
  var speed = parseInt(document.getElementById("speed").value);

  // Output:
  document.getElementById("last_total").textContent = "";

  // Action:
  stop();
  stop = runDemo(N, r, speed);
}

updateBtn.addEventListener('click', updateGUI);
updateGUI();
