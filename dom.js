function empty_cell_html(num) {
    const cell = document.createElement('div');
    cell.classList.add('empty_cell');
    cell.onclick = () => try_move(num);
    return cell;
  }
  
  function filled_cell_html(value) {
    const cell = document.createElement('div');
    cell.classList.add('filled_cell');
    cell.textContent = value;
    return cell;
  }
  
  function mini_board_html(num) {
    const board = document.createElement('div');
    board.classList.add('sub_board');
    for (let x = 0; x < 9; x++) {
      const cell = empty_cell_html((num * 9) + x);
      const square = document.createElement('div');
      square.id = squareID((num * 9) + x);
      square.classList.add('square');
      square.appendChild(cell);
      board.appendChild(square);
    }
    return board;
  }
  
  function filled_board_html(value) {
    const board = document.createElement('p');
    board.classList.add('filled_board');
    board.textContent = value;
    return board;
  }
  
  function setupTable(TableId) {
    var mainTable = document.getElementById(TableId);
    for (let tableNum = 0; tableNum < 9; tableNum++) {
      const miniBoard = mini_board_html(tableNum);
      const container = document.createElement('div');
      container.id = miniBoardID(tableNum);
      container.classList.add('main_board_component');
      container.appendChild(miniBoard);
      mainTable.appendChild(container);
    }
  }
  
  function changeButton(num, value) {
    const button = document.getElementById(squareID(num));
    button.innerHTML = '';
    button.appendChild(filled_cell_html(value));
  }
  
  function changeBoard(num, value) {
    const board = document.getElementById(miniBoardID(num));
    board.innerHTML = '';
    board.appendChild(filled_board_html(value));
  }
  
  function set_buttons() {
    for (let board = 0; board < 9; board++) {
      for (let square = board * 9; (square < (board + 1) * 9); square++) {
        const button = document.getElementById(squareID(square));
        const emptyCells = button.getElementsByClassName('empty_cell');
        for (const cell of emptyCells) {
          if (gameInfo[0] !== -2 && (Math.floor(square / 9) === gameInfo[0] || gameInfo[0] === -1)) {
            cell.classList.add("valid_button");
          } else {
            cell.classList.remove("valid_button");
          }
        }
      }
    }
  }
  
  function removeButtons() {
    for (let board = 0; board < 9; board++) {
      for (let square = board * 9; (square < (board + 1) * 9); square++) {
        const button = document.getElementById(squareID(square));
        const emptyCells = button.getElementsByClassName('empty_cell');
        for (const cell of emptyCells) {
          cell.classList.remove("valid_button");
        }
      }
    }
  }
  