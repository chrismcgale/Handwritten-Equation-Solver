const space = '500px';
let colour = 'black';
var stack = [];

// create canvas element and append it to document body
var canvas = document.createElement('canvas');
document.body.appendChild(canvas);

// some hotfixes... ( ≖_≖)
document.body.style.margin = 0;
canvas.style.position = 'fixed';

// get canvas 2D context and set him correct size
var ctx = canvas.getContext('2d');
resize();

// last known position
var pos = { x: 0, y: 0 };

window.addEventListener('resize', resize);
document.addEventListener('mousemove', draw);
document.addEventListener('mousedown', setPosition);
document.addEventListener('mouseenter', setPosition);


// new position from mouse event
function setPosition(e) {
  pos.x = e.clientX;
  pos.y = e.clientY;
}

function resize() {
  ctx.canvas.width = window.innerWidth;
  ctx.canvas.height = window.innerHeight;
}

function draw(e) {
  // mouse left button must be pressed
  if (e.buttons !== 1) return;

  ctx.beginPath(); // begin

  ctx.lineWidth = 5;
  ctx.lineCap = 'round';
  ctx.strokestyle = '#000'

  ctx.moveTo(pos.x, pos.y); // from
  setPosition(e);
  ctx.lineTo(pos.x, pos.y); // to

  ctx.stroke(); // draw it!
}


function createButtons(){
    const buts = document.querySelector('#btn_ctn');
    const clear_btn = document.createElement('button');
    clear_btn.textContent = "clear";
    clear_btn.setAttribute('class', 'clear_btn');
    buts.appendChild(clear_btn);

    const submit = document.createElement('button');
    submit.textContent = "submit";
    submit.setAttribute('class', 'submit');
    buts.appendChild(submit);

    const back = document.createElement('button');
    back.textContent = "back";
    back.setAttribute('class', 'back');
    buts.appendChild(back);

    const reset = document.createElement('button');
    reset.textContent = "reset";
    reset.setAttribute('class', 'reset');
    buts.appendChild(reset);
    
    const solve = document.createElement('button');
    solve.textContent = "solve";
    solve.setAttribute('class', 'solve');
    buts.appendChild(solve);

}

createButtons();



const clr = document.querySelector('.clear_btn');
clr.addEventListener('mousedown', function(){
          const context = canvas.getContext('2d');
          context.clearRect(0, 0, canvas.width, canvas.height);
});


