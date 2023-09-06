var exports;
var memory;
let best;
let wasmMemory = new WebAssembly.Memory({initial: 256, maximum: 512});
WebAssembly.instantiateStreaming(
    fetch("js_api.wasm"), {
        js: {
            mem: wasmMemory
        }
    }
).then(results => {
    exports = results.instance.exports;
    memory = results.instance.exports.memory;
    best = results.instance.exports._Z12bestMoveListPii;
}).catch(error => {
    console.log("Wasm corrupted/doesn't exist", error);
});



let winStatus = new Int16Array(9);
var gameInfo = new Int32Array(83);
var moveList = new Int32Array(81);
var moveListLength = 0;
function setupArray()
{
	// next board variable in the c++ program
	gameInfo[0] = -1;
	// x turn
	gameInfo[1] = 1;
	// all other cells are 0 for the moment
	for(let a = 2; a < 83; a++)
	{
		gameInfo[a] = 0;
	}
	for( let b = 0; b < 9; b++)
	{
		winStatus[b] = b + 3;
	}
} 
function convert(value)
{
	if(value === 'X'){return 1}
	return 2;
}
async function runWasm()
{
    var myArray = new Int32Array(memory.buffer)
	for(let a = 0; a < moveListLength; a++)
	{
		myArray[a] = moveList[a];
	}
	//console.log(gameInfo[0]);
	const move = best(0,moveListLength);
	console.log(move);
    return move;
}
function setupTable(TableId)
{
	var mainTable = document.getElementById(TableId);
	for(let tableNum = 0; tableNum < 9; tableNum++) 
	{
		mainTable.innerHTML += "<div id =" + miniBoardID(tableNum) + " class = main_board_component >" + mini_board_html(tableNum) + "</div>"
	}
	
}
function filled_cell_html(value)
{
	return `<p class = "filled_cell" >` + value + `</p>`

}
function empty_cell_html(num)
{
	return `<button class = "empty_cell" onclick = "try_move(` + num + `)">  </button>`

}
function mini_board_html(num)
{
	let empty_cells = "";
	for(let x = 0; x < 9; x++)
	{
		empty_cells += "<div id = " + squareID((num *9) + x) + " class = square >" + empty_cell_html((num * 9) + x) + "</div>"
	}
	return  `<div class = "sub_board"> `+ empty_cells + `</div>`

}
function filled_board_html(value)
{
	return `<p class = "filled_board" id = >` + value + `</p>`

}
function miniBoardID(num)
{
	const str = num.toString();
	return "mini" + str;
}
function squareID(num)
{
	const str = num.toString();
	return "square" + str;
}
function changeButton(num, value)
{
	document.getElementById(squareID(num)).innerHTML = filled_cell_html(value);
}
function changeBoard(num, value)
{
	document.getElementById(miniBoardID(num)).innerHTML = filled_board_html(value);
}
function try_move(moveNum) {
	if(gameInfo[1] === 2){return}
	gameInfo[1] = 2;
	if(gameInfo[0] === -1 || Math.floor(moveNum / 9) === gameInfo[0])
	{
		
		play_move(moveNum, 'X');
		//console.log([...Array.from(gameInfo)])
		//console.log([...Array.from(moveList)])
		document.getElementById("output").textContent = " Thinking....";
		console.log(winStatus)
		runWasm().then(move => {
			play_move(move, 'O');
			document.getElementById("output").textContent = "Your Turn!";
			set_buttons();
			gameInfo[1] = 1;
		});
		  

	}
	else
	{
		document.getElementById("output").textContent = "Illegal Move!";
		setTimeout(function() {
			document.getElementById("output").textContent = "Your Turn!";
		}, 2000);
		set_buttons();
		gameInfo[1] = 1;
	}
	
}
function play_move(num, value)
{
	gameInfo[num + 2] = convert(value)
	moveList[moveListLength] = num;
	moveListLength++;
	if(checkWin(num,value))
	{
		changeBoard(Math.floor(num / 9),value)
		winStatus[Math.floor(num/9)] = convert(value);
		if(totalWin(value))
		{
			console.log("WHY??")
			gameInfo[0] = -2;
			document.getElementById("output").textContent = "Illegal Move!";
			//document.getElementById("output").textContent = (value + " Wins!");
			console.log(document.getElementById("output").textContent = (value + " Wins!"))

		}	
	}
	else{
		changeButton(num,value);
		gameInfo[0] = Math.floor(num %9);
	}
	gameInfo[0] = Math.floor(num %9);
	if(winStatus[gameInfo[0]] < 3 )
	{
		gameInfo[0] = -1;
	}
}
function checkWin(num, value)
{
	const board_num = Math.floor(num / 9);
	const cell_offset = (board_num * 9) +2;
	const target = convert(value);
	if(gameInfo[cell_offset] === target && gameInfo[cell_offset +1] === target && gameInfo[cell_offset+2] === target){return true}
	if(gameInfo[cell_offset+3] === target && gameInfo[cell_offset +4] === target && gameInfo[cell_offset+5] === target){return true}
	if(gameInfo[cell_offset+6] === target && gameInfo[cell_offset +7] === target && gameInfo[cell_offset+8] === target){return true}
	if(gameInfo[cell_offset] === target && gameInfo[cell_offset +3] === target && gameInfo[cell_offset+6] === target){return true}
	if(gameInfo[cell_offset+1] === target && gameInfo[cell_offset +4] === target && gameInfo[cell_offset+7] === target){return true}
	if(gameInfo[cell_offset+2] === target && gameInfo[cell_offset +5] === target && gameInfo[cell_offset+8] === target){return true}
	if(gameInfo[cell_offset] === target && gameInfo[cell_offset +4] === target && gameInfo[cell_offset+8] === target){return true}
	if(gameInfo[cell_offset+6] === target && gameInfo[cell_offset +4] === target && gameInfo[cell_offset+2] === target){return true}
	return false;
}
function totalWin(value)
{
	const target = convert(value);
	console.log(winStatus[1] === target, winStatus[4] === target, winStatus[7] === target)
	if(winStatus[0] === target && winStatus[1] === target && winStatus[2] === target){return true}
	if(winStatus[3] === target && winStatus[4] === target && winStatus[5] === target){return true}
	if(winStatus[6] === target && winStatus[7] === target && winStatus[8] === target){return true}
	if(winStatus[0] === target && winStatus[3] === target && winStatus[6] === target){return true}
	if(winStatus[1] === target && winStatus[4] === target && winStatus[7] === target){return true}
	if(winStatus[2] === target && winStatus[5] === target && winStatus[8] === target){return true}
	if(winStatus[0] === target && winStatus[4] === target && winStatus[8] === target){return true}
	if(winStatus[6] === target && winStatus[4] === target && winStatus[2] === target){return true}
	console.log("fuck")
	return false;
}
function set_buttons()
{
	for(let board = 0; board < 9; board++)
	{
		for(let square = board * 9; (square < (board+1) * 9) && winStatus[board] > 2; square++)
		document.getElementById(squareID(square)).querySelectorAll("button").forEach((button) =>
			{
				if(Math.floor(square /9 ) === gameInfo[0] || gameInfo[0] === -1)
				{
					button.classList.add("valid_button");
				}
				else{
					button.classList.remove("valid_button");
				}
			})
	}
}
function removeButtons()
{
	for(let board = 0; board < 9; board++)
	{
		for(let square = board * 9; (square < (board+1) * 9) && winStatus[board] > 2; square++)
		document.getElementById(squareID(square)).querySelectorAll("button").forEach((button) =>
			{
				
				button.classList.remove("valid_button");
			})
	}
}
setupArray();

setupTable("main board");
set_buttons()

play_move(9,'O');
play_move(10,'O');
play_move(11,'O');
play_move(36,'O');
play_move(37,'O');
play_move(38,'O');
play_move(70, 'O');
play_move(69, 'O');
