
var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
ctx.beginPath();
ctx.rect(0, 0, 300, 300);
ctx.fillStyle = "black";
ctx.fill();

let btn = document.getElementById("btn-reset");
var arr = [];
let toggle = -1;

canvas.addEventListener("click", function() {

  toggle = -toggle;
  if(toggle == 1) {
    write();
  }
})

function write() {
  canvas.addEventListener("mousemove", function(e) {
    if(toggle == 1) {
      arr.push([e.offsetX, e.offsetY]);
      draw(arr);
    }
  });
}

btn.addEventListener("click", function(e){
  ctx.clearRect(0, 0,  canvas.width, canvas.height);
  arr = [];
  ctx.beginPath();
  ctx.rect(0, 0, 300, 300);
  ctx.fillStyle = "black";
  ctx.fill();
})


function draw(arr) {
  if(arr.length == 1) return;
  ctx.beginPath();
  ctx.moveTo(arr[2][0], arr[2][1]);

  for(let i = 1; i < arr.length;i++) {
    ctx.lineTo(arr[i][0], arr[i][1]);
    ctx.lineWidth = 40;
    ctx.strokeStyle = '#fff';
    ctx.stroke();
  }
}


var audio = document.getElementById("myAudio"); 
    
function playAudio() { 
  audio.play(); 
}
