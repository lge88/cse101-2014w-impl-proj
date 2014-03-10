
function Pointset(n, r) {
  this.points = [];

  if (typeof n === "number") {
    var R, theta, x, y;
    while (n-- > 0) {
      if (typeof r === "number")
        R = r*r+Math.random()*(1-r*r);
      else
        R = Math.random();

      theta = 2*Math.PI*Math.random();
      x = Math.sqrt(R)*Math.cos(theta);
      y = Math.sqrt(R)*Math.sin(theta);
      // x = R*Math.cos(theta);
      // y = R*Math.sin(theta);
      this.points.push([x, y]);
    }
  } else if (Array.isArray(n)){
    this.points = n.slice();
  } else if (typeof n === "string") {
    this.fromString(n);
  }
}

Pointset.prototype.toString = function() {
  return this.points.map(function(p) {
    return p.map(function(x) {
      return x.toFixed(10);
    }).join(" ");
  }).join("\n");
};

Pointset.prototype.toJS = function() {
  var arr = [];
  arr.push("var points = [\n");
  this.points.forEach(function(p) {
    arr.push("  [" + p[0] + ", " + p[1], "],\n");
  });
  arr.push("];");
  return arr.join("");
};

Pointset.prototype.fromString = function(str) {
  this.points = str
    .trim()
    .split("\n")
    .map(function(line) {
      return line.trim().split(/\s+/).map(function(x) {
        return parseFloat(x);
      });
    });
};

Pointset.prototype.loadURL = function(url) {
  var client = new XMLHttpRequest();
  client.open('GET', url);

  var _this = this;
  client.onreadystatechange = function() {
    _this.fromString(client.responseText);
  };
  client.send();
}

Pointset.prototype.drawPoints = function(ctx) {
  var r = 2;

  ctx.fillStyle = "#ff0000";
  this.points.forEach(function(p) {
    p = this.toCanvasPoint(p, ctx);
    ctx.beginPath();
    ctx.arc(p[0], p[1], r, 0, 2*Math.PI);
    ctx.closePath();
    ctx.fill();
  }, this);
};

Pointset.prototype.drawPolygon = function(ctx, indices) {
  var pts = this.points;
  if (pts.length <= 1) return;

  var i, len = indices.length, x, y, p;

  ctx.strokeStyle = "#0000ff";
  ctx.lineWidth = 3;

  ctx.beginPath();
  p = pts[indices[0]];
  p = this.toCanvasPoint(p, ctx);
  x = p[0];
  y = p[1];
  ctx.moveTo(x, y);
  for (i = 1; i < len; ++i) {
    p = pts[indices[i]];
    p = this.toCanvasPoint(p, ctx);
    x = p[0];
    y = p[1];
    ctx.lineTo(x, y);
  }
  p = pts[indices[0]];
  p = this.toCanvasPoint(p, ctx);
  x = p[0];
  y = p[1];
  ctx.lineTo(x, y);
  ctx.closePath();
  ctx.stroke();
};

Pointset.prototype.drawPolygonPoints = function(ctx, points) {

  var i, len = points.length, x, y, p;
  if (len <= 1) return;

  ctx.strokeStyle = "#0000ff";
  ctx.lineWidth = 3;

  ctx.beginPath();
  p = points[0];
  p = this.toCanvasPoint(p, ctx);
  x = p[0];
  y = p[1];
  ctx.moveTo(x, y);
  for (i = 1; i < len; ++i) {
    p = points[i];
    p = this.toCanvasPoint(p, ctx);
    x = p[0];
    y = p[1];
    ctx.lineTo(x, y);
  }
  p = points[0];
  p = this.toCanvasPoint(p, ctx);
  x = p[0];
  y = p[1];
  ctx.lineTo(x, y);
  ctx.closePath();
  ctx.stroke();
};

Pointset.prototype.getBoundingBox = function() {
  var left = Infinity, right = -Infinity;
  var top = -Infinity, bottom = Infinity;

  this.points.forEach(function(p) {
    left = Math.min(left, p[0]);
    right = Math.max(right, p[0]);
    bottom = Math.min(bottom, p[1]);
    top = Math.max(top, p[1]);
  });

  return {
    left: left,
    right: right,
    bottom: bottom,
    top: top
  };
};

Pointset.prototype.getBound = function(ctx) {
  var margin = 5;
  var R  = ctx.canvas.width < ctx.canvas.height ?
    0.5*ctx.canvas.width-margin : 0.5*ctx.canvas.height-margin;
  return R;
};

Pointset.prototype.getCenter = function(ctx) {
  return [
    0.5*ctx.canvas.width,
    0.5*ctx.canvas.height
  ];
};

Pointset.prototype.toCanvasPoint = function(p, ctx) {
  var c = this.getCenter(ctx);
  var cx = c[0];
  var cy = c[1];
  var B = this.getBound(ctx);
  return [
    cx + B*p[0],
    cy - B*p[1]
  ];
};

if (typeof module !== "undefined") {
  module.exports = exports = Pointset;
  if (!module.parent) {
    var n = parseInt(process.argv[2]);
    var pts = new Pointset(n);
    console.log(pts.toJS());
  }
}
