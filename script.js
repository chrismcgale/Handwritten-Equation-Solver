const space = '500px';
let colour = 'black';
var canvas, ctx, flag = false,


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
init()


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


function sketch() {
        ctx.beginPath();
        ctx.moveTo(prevX, prevY);
        ctx.lineTo(currX, currY);
        ctx.strokeStyle = x;
        ctx.lineWidth = y;
        ctx.stroke();
        ctx.closePath();
}
sketch()

function clear() {
        var m = confirm("Want to clear");
        if (m) {
            ctx.clearRect(0, 0, w, h);
            document.getElementById("canvasimg").style.display = "none";
        }
}
clear()


