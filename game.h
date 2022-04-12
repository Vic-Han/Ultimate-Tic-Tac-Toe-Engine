
/*
Victor Han
March 20th, 2022

*/

#ifndef GAME_H
#define GAME_H


#include "ultimate_board.h"
#include<random>

// definitions for the numerical representations of the places
/*
   0   1   2

   3   4   5

   6   7   8
*/
#define TOP_LEFT 0
#define TOP_MIDDLE 1
#define TOP_RIGHT 2
#define MIDDLE_LEFT 3
#define MIDDLE 4
#define MIDDLE_RIGHT 5
#define BOTTOM_LEFT 6
#define BOTTOM_MIDDLE 7
#define BOTTOM_RIGHT 8
// definitions for the main board
// used when the next piece can be placed on any local board
#define ANYWHERE -1
// used when the next peice cannot be placed anywhere because one player has won
#define NOWHERE -2

// the total number of iterations that the monte carlo tree search does
// this specific constant takes 2-5 seconds when used 
#define MAX_ITERATIONS 200000	
	
	
int score_of_iteration(Ultimate_bit_board test_state);
uint_fast8_t pick_move(Ultimate_bit_board game_state);
#endif