#include <emscripten.h>
#include "game.h"
  


EMSCRIPTEN_KEEPALIVE
int bestMoveState(int* gameinfo)
{
  
    int result = 0;
    
    srand(42);
    Ultimate_bit_board gameinstance = Ultimate_bit_board(gameinfo);
    uint_fast8_t best_move = gameinstance.pick_move();  
    result += ((best_move >> 4) * 9 + (best_move&0xf));
    return result;
}
EMSCRIPTEN_KEEPALIVE
int bestMoveList(int *moveList, int listSize){
  int result = 0;
  
  srand(42);
  uint_fast8_t copyMoveList[81];
  for(int index = 0; index < listSize; index++){
    copyMoveList[index] = (uint_fast8_t)( ((moveList[index]/9) << 4) + (moveList[index]%9));
  }
  Ultimate_bit_board current_game = Ultimate_bit_board();
  current_game.simulate_game(copyMoveList, listSize);
  uint_fast8_t best_move = current_game.pick_move();  
  result += ((best_move >> 4) * 9 + (best_move&0xf));
  return result;
}
/*
void test1(){
   int gameInfo[83] = {8, 2, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 2, 2, 0, 1, 0, 0, 0, 1, 0, 1, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 2, 1, 0, 2, 0, 0, 0, 0, 2, 0, 2, 2, 1, 0, 2, 2, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 2, 0, 0, 0, 1, 0, 2, 0, 1, 1};
    std::cout << bestMove(gameInfo);
}
void test2(){
  int gameInfo[83] = {6, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2, 2, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 1, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1};
  std::cout << bestMove(gameInfo);
}
void test3(){
   int gameInfo[83] = {1, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, 1, 
   0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 1, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::cout << bestMove(gameInfo);
}

int main(){
     
    test1();
   
    return 0;
}*/