const space = '500px';
let colour = 'black';


var canvas, ctx, flag = false,
            prevX = 0,
            currX = 0,
            prevY = 0,
            currY = 0,
            dot_flag = false;

var x = "black",
       y = 2;

function init() {
            canvas = document.getElementById('can');
            ctx = canvas.getContext("2d");
            w = canvas.width;
            h = canvas.height;

            canvas.addEventListener("mousemove", function (e) {
                findxy('move', e)
            }, false);
            canvas.addEventListener("mousedown", function (e) {
                findxy('down', e)
            }, false);
            canvas.addEventListener("mouseup", function (e) {
                findxy('up', e)
            }, false);
            canvas.addEventListener("mouseout", function (e) {
                findxy('out', e)
            }, false);
        }

function draw() {
            ctx.beginPath();
            ctx.moveTo(prevX, prevY);
            ctx.lineTo(currX, currY);
            ctx.strokeStyle = x;
            ctx.lineWidth = y;
            ctx.stroke();
            ctx.closePath();
        }

function erase() {
            var m = confirm("Want to clear");
            if (m) {
                ctx.clearRect(0, 0, w, h);
                document.getElementById("canvasimg").style.display = "none";
            }
        }

function save() {
            document.getElementById("canvasimg").style.border = "2px solid";
            var dataURL = canvas.toDataURL();
            document.getElementById("canvasimg").src = dataURL;
            document.getElementById("canvasimg").style.display = "inline";
        }

function findxy(res, e) {
            if (res == 'down') {
                prevX = currX;
                prevY = currY;
                currX = e.clientX - canvas.offsetLeft;
                currY = e.clientY - canvas.offsetTop;

                flag = true;
                dot_flag = true;
                if (dot_flag) {
                    ctx.beginPath();
                    ctx.fillStyle = x;
                    ctx.fillRect(currX, currY, 2, 2);
                    ctx.closePath();
                    dot_flag = false;
                }
            }
            if (res == 'up' || res == "out") {
                flag = false;
            }
            if (res == 'move') {
                if (flag) {
                    prevX = currX;
                    prevY = currY;
                    currX = e.clientX - canvas.offsetLeft;
                    currY = e.clientY - canvas.offsetTop;
                    draw();
                }
            }
        }

function sketch(){
    let cells = document.querySelectorAll('.cell');
    cells.forEach((cell) =>{
        cell.addEventListener('mouseover', function(){
            cell.style.backgroundColor = colour;
        });
    });
}

sketch();

function createButtons(){
    const buts = document.querySelector('#btn_ctn');
    const clear_btn = document.createElement('button');
    clear_btn.textContent = "Clear";
    clear_btn.setAttribute('class', 'clear_btn');
    buts.appendChild(clear_btn);

    const resize_btn = document.createElement('button');
    resize_btn.textContent = "Back";
    resize_btn.setAttribute('class', 'back');
    buts.appendChild(back);

    const randomColour = document.createElement('button');
    randomColour.textContent = "Submit Drawing";
    randomColour.setAttribute('class', 'sub');
    buts.appendChild(sub);

    const blackColour = document.createElement('button');
    blackColour.textContent = "Solve Equation";
    blackColour.setAttribute('class', 'solve');
    buts.appendChild(solve);

}

createButtons();




function clear(){
    const clr = document.querySelector('.clear_btn');
    clr.addEventListener('mousedown', function(){
        let cells = document.querySelectorAll('.cell');

        cells.forEach((cell) =>{
            cell.style.backgroundColor = 'transparent';
        });


    });

}
clear();

function back(){

}
back();

function sub(){
}
sub();

function solve(){

}
solve();
