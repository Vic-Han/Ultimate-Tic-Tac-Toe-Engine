
let winStatus = new Int16Array(9);
var gameInfo = new Int32Array(83);
var moveList = new Int32Array(81);
var moveListLength = 0;

function setupArray() {
  winStatus = new Int16Array(9);
  gameInfo = new Int32Array(83);
  moveList = new Int32Array(81);
  moveListLength = 0;
  // next board variable in the c++ program
  gameInfo[0] = -1;
  // x turn
  gameInfo[1] = 1;
  // all other cells are 0 for the moment
  for (let a = 2; a < 83; a++) {
    gameInfo[a] = 0;
  }
  for (let b = 0; b < 9; b++) {
    winStatus[b] = b + 3;
  }
}

function play_move(num, value) {
  gameInfo[num + 2] = convert(value)
  moveList[moveListLength] = num;
  moveListLength++;
  if (checkWin(num, value)) {
    changeBoard(Math.floor(num / 9), value)
    winStatus[Math.floor(num / 9)] = convert(value);
    if (totalWin(value)) {
      gameInfo[0] = -2;

      document.getElementById("output").textContent = (value + " Wins!");

    }
  } else {
    changeButton(num, value);
    gameInfo[0] = Math.floor(num % 9);
  }
  gameInfo[0] = Math.floor(num % 9);
  if (winStatus[gameInfo[0]] < 3) {
    gameInfo[0] = -1;
  }
}

function checkWin(num, value) {
  const board_num = Math.floor(num / 9);
  const cell_offset = (board_num * 9) + 2;
  const target = convert(value);
  if (gameInfo[cell_offset] === target && gameInfo[cell_offset + 1] === target && gameInfo[cell_offset + 2] === target) { return true }
  if (gameInfo[cell_offset + 3] === target && gameInfo[cell_offset + 4] === target && gameInfo[cell_offset + 5] === target) { return true }
  if (gameInfo[cell_offset + 6] === target && gameInfo[cell_offset + 7] === target && gameInfo[cell_offset + 8] === target) { return true }
  if (gameInfo[cell_offset] === target && gameInfo[cell_offset + 3] === target && gameInfo[cell_offset + 6] === target) { return true }
  if (gameInfo[cell_offset + 1] === target && gameInfo[cell_offset + 4] === target && gameInfo[cell_offset + 7] === target) { return true }
  if (gameInfo[cell_offset + 2] === target && gameInfo[cell_offset + 5] === target && gameInfo[cell_offset + 8] === target) { return true }
  if (gameInfo[cell_offset] === target && gameInfo[cell_offset + 4] === target && gameInfo[cell_offset + 8] === target) { return true }
  if (gameInfo[cell_offset + 6] === target && gameInfo[cell_offset + 4] === target && gameInfo[cell_offset + 2] === target) { return true }
  return false;
}

function totalWin(value) {
  const target = convert(value);
  console.log(winStatus[1] === target, winStatus[4] === target, winStatus[7] === target)
  if (winStatus[0] === target && winStatus[1] === target && winStatus[2] === target) { return true }
  if (winStatus[3] === target && winStatus[4] === target && winStatus[5] === target) { return true }
  if (winStatus[6] === target && winStatus[7] === target && winStatus[8] === target) { return true }
  if (winStatus[0] === target && winStatus[3] === target && winStatus[6] === target) { return true }
  if (winStatus[1] === target && winStatus[4] === target && winStatus[7] === target) { return true }
  if (winStatus[2] === target && winStatus[5] === target && winStatus[8] === target) { return true }
  if (winStatus[0] === target && winStatus[4] === target && winStatus[8] === target) { return true }
  if (winStatus[6] === target && winStatus[4] === target && winStatus[2] === target) { return true }
  return false;
}