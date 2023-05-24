#include <emscripten.h>
#include "game.h"
  


EMSCRIPTEN_KEEPALIVE
int subtract(int x, int y) {
  return x - y;
}




EMSCRIPTEN_KEEPALIVE
int bestMove(int* gameinfo)
{
    int result = 0;
    Ultimate_bit_board gameinstance = Ultimate_bit_board(gameinfo);

    uint_fast8_t best_move = gameinstance.pick_move();
    result += ((best_move >> 4) * 9 + (best_move&0xf));
    return result;
}
/*
int main(){
     

    int gameInfo[83];
    for( int x = 2; x< 83; x++)
    {
      gameInfo[x] = 0;
    }
    gameInfo[0] = -1;
    gameInfo[1] = 2;
    gameInfo[40 + 2] = 1;
    gameInfo[4 + 2] = 1;
    gameInfo[13 + 2] = 1;
    gameInfo[22 + 2] = 1;
    gameInfo[8 + 2] = 1;
    gameInfo[1 + 2] = 1;
    gameInfo[7 + 2] = 1;
    gameInfo[76 + 2] = 1;
    gameInfo[36 + 2] = 2;
    gameInfo[37 + 2] = 2;
    gameInfo[38 + 2] = 2;
    gameInfo[0 + 2] = 2;
    gameInfo[72 + 2] = 2;
    gameInfo[9 + 2] = 2;
    gameInfo[63 + 2] = 2;
    Ultimate_bit_board gameinstance = Ultimate_bit_board(gameInfo);
    //uint_fast8_t list[81];
    //uint8_t list_size = 0;
    //gameinstance.move_list(list,list_size);
    //std::cout << (int)list_size;
    //uint_fast8_t best_move = gameinstance.pick_move();
    //int result = ((best_move >> 4) * 9 + (best_move&0xf));
    std::cout << bestMove(gameInfo);
    return 0;
}*/