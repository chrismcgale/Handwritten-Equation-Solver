const scan = require('./parse_and_solve/scan');
const parse = require('./parse_and_solve/parse');
const galaxy = require('./parse_and_solve/solver');

var mousePressed = false;
var lastX;
var lastY;
var ctx;
var equation = "52 - 10 - 13";

function Init() {
    ctx = document.getElementById('myCanvas').getContext("2d");

    $('#myCanvas').mousedown(function (e) {
        mousePressed = true;
        Draw(e.pageX - $(this).offset().left, e.pageY - $(this).offset().top, false);
    });

    $('#myCanvas').mousemove(function (e) {
        if (mousePressed) {
            Draw(e.pageX - $(this).offset().left, e.pageY - $(this).offset().top, true);
        }
    });

    $('#myCanvas').mouseup(function (e) {
        mousePressed = false;
    });
	    $('#myCanvas').mouseleave(function (e) {
        mousePressed = false;
    });
}

function Draw(x, y, isDown) {
    if (isDown) {
        ctx.beginPath();
        ctx.strokeStyle = "black";
        ctx.lineWidth = "3";
        ctx.lineJoin = "round";
        ctx.moveTo(lastX, lastY);
        ctx.lineTo(x, y);
        ctx.closePath();
        ctx.stroke();
    }
    lastX = x; lastY = y;
}
	
function Clear() {
   ctx.clearRect(0, 0, 500, 500);
}

function Reset(){
	ctx.clearRect(0, 0, 500, 500);
	equation = "";
}

function Back(){
	equation = equation.substring(0, equation.length - 1);
}

function Solve(){
    const sca = scan('./scan ' + equation, {timeout: 20000}, function(error, scanned, stderr) {
        const par = parse('./parse ' + scanned, {timeout: 20000}, function(error, parsed, stderr) {
			   const gala = galaxy('./galaxy ' + parsed, {timeout: 20000}, function(error, answer, stderr) {
                               document.getElementById("display").innerHTML = answer;
			   }
			   }
			   }
		     equation = "";
}

function Submit(){
	term = tf.browser.fromPixels(ctx);
	result = model.predict(term);
	equation += result
}

function Print(){
	$("#display").val(equation);
}
