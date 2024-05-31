const worker = new Worker('worker.js')
worker.postMessage({action:"fetchWebAssembly"});
worker.onmessage = event => {
	if(event.data.message === "Successfully saved Wasm"){
		console.log("Wasm saved!")
	}
	if(event.data.message === "Failed to Save Wasm"){
		console.log(event.data.error)
	}
	if(event.data.message == "Move Found"){
		if(moveListLength === 0){
			return;
		}
		const move = event.data.move;
		document.getElementById("output").textContent = "Your Turn!";
		play_move(move, 'O');
		
		set_buttons();
		gameInfo[1] = 1;
	}
}
let winStatus = new Int16Array(9);
var gameInfo = new Int32Array(83);
var moveList = new Int32Array(81);
var moveListLength = 0;
function setupArray()
{
	winStatus = new Int16Array(9);
	gameInfo = new Int32Array(83);
	moveList = new Int32Array(81);
	moveListLength = 0;
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

function setupTable(TableId)
{
	var mainTable = document.getElementById(TableId);
	for(let tableNum = 0; tableNum < 9; tableNum++) 
	{
		mainTable.innerHTML += "<div id =" + miniBoardID(tableNum) + " class = main_board_component >" + mini_board_html(tableNum) + "</div>"
	}
	
}
function empty_cell_html(num) {
	return `<div class="empty_cell" onclick="try_move(${num})"></div>`;
  }
  
  function filled_cell_html(value) {
	return `<div class="filled_cell">${value}</div>`;
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
		document.getElementById("output").textContent = " Thinking....";
		play_move(moveNum, 'X');
		removeButtons();
		
		console.log(winStatus)
		worker.postMessage({action: "computeMove" , moveList: moveList, listSize: moveListLength})
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
			gameInfo[0] = -2;
		
			document.getElementById("output").textContent = (value + " Wins!");

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
	return false;
}
function set_buttons()
{
	for(let board = 0; board < 9; board++)
	{
		for(let square = board * 9; (square < (board+1) * 9) && winStatus[board] > 2; square++)
		document.getElementById(squareID(square)).querySelectorAll("empty_cell").forEach((button) =>
			{
				if(gameInfo[0] !== -2 && (Math.floor(square /9 ) === gameInfo[0] || gameInfo[0] === -1))
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
		document.getElementById(squareID(square)).querySelectorAll("empty_cell").forEach((button) =>
			{
				
				button.classList.remove("valid_button");
			})
	}
}
function startNewGame(){
	document.getElementById("main board").innerHTML = "";
	document.getElementById("output").textContent = "Your Turn!";
	setupArray();

	setupTable("main board");
	set_buttons()
}
startNewGame();