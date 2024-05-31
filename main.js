const worker = new Worker('worker.js')
worker.postMessage({ action: "fetchWebAssembly" });
worker.onmessage = event => {
  if (event.data.message === "Successfully saved Wasm") {
    console.log("Wasm saved!")
  }
  if (event.data.message === "Failed to Save Wasm") {
    console.log(event.data.error)
  }
  if (event.data.message == "Move Found") {
    if (moveListLength === 0) {
      return;
    }
    const move = event.data.move;
    document.getElementById("output").textContent = "Your Turn!";
    play_move(move, 'O');

    set_buttons();
    gameInfo[1] = 1;
  }
}

function try_move(moveNum) {
  if (gameInfo[1] === 2) { return }
  gameInfo[1] = 2;
  if (gameInfo[0] === -1 || Math.floor(moveNum / 9) === gameInfo[0]) {
    document.getElementById("output").textContent = " Thinking....";
    play_move(moveNum, 'X');
    removeButtons();

    console.log(winStatus)
    worker.postMessage({ action: "computeMove", moveList: moveList, listSize: moveListLength })
  } else {
    document.getElementById("output").textContent = "Illegal Move!";
    setTimeout(function () {
      document.getElementById("output").textContent = "Your Turn!";
    }, 2000);
    set_buttons();
    gameInfo[1] = 1;
  }

}

function startNewGame() {
  document.getElementById("main board").innerHTML = "";
  document.getElementById("output").textContent = "Your Turn!";
  setupArray();

  setupTable("main board");
  set_buttons()
}

startNewGame();