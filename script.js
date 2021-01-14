var mousePressed = false;
var lastX;
var lastY;
var ctx;
var equation = "test";

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
	//clear equation
}

function Back(){
	//if equation isn't empty pop
}

function Solve(){
	//Send equation to c++
}

function Submit(){
	//Sendd to keras and then push to equation
}

function print(){
	$("#display").val(equation);
}

print();
