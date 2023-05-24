/*
Victor Han
March 23rd,2022
file containing the Monte Carlo Tree Search functions for the game
*/
#include "game.h"

// function that returns the result of one iteration

int Ultimate_bit_board::score_of_iteration()
{
	// make moves until the game in this iteration is over
	uint_fast8_t possible_moves[81];
	uint_fast8_t size = 0;
	move_list(possible_moves, size);
	while(size != 0)
	{
		make_move(possible_moves[rand()%size]);
		size = 0;
		move_list(possible_moves, size);
	}
	// return -1 if o wins, 1 if x wins, and 0 if the game is drawn
	// this makes x favour higher scores and o favour lower scores
	if(o_win())
	{
		return -1;
	}
	else if(x_win())
	{
		return 1;
	}
	return 0;
}
// function that uses Monte Carlo Tree Search to select a move
uint_fast8_t Ultimate_bit_board::pick_move()
{
	
	// get all moves and return 0 if there are no moves
	uint_fast8_t possible_moves[81];
	uint_fast8_t size = 0;
	move_list(possible_moves, size);
	if(size == 0)
	{
		return (uint_fast8_t)0;
	}
	// set the default move to 0
	int index_of_best_move = 0;
	int best_move_score = 0;
	// get the number of iterations per move
	const int iterations_per_move = MAX_ITERATIONS / size;
	// set best move score to lowest possible value for x, or highest possible value for o
	if(get_X_move())
	{
		best_move_score = -1 * iterations_per_move;
	}
	else
	{
		best_move_score = iterations_per_move;
	}
	
	// iterate through every move to see which one has the highest chance of victory
	for(int move_num = 0; move_num != size; ++move_num)
	{
		
		int move_score = 0;
		// calculate the score of the random sample
		
		for(int iteration = 0; iteration < iterations_per_move; ++iteration)
		{

			// make a new board and play the move
			short nextBoard;
			uint_fast16_t board_contents[18];
			bool win_contents[18];
			get_fields(board_contents,win_contents,&nextBoard);
			Ultimate_bit_board move_result(board_contents,win_contents,nextBoard);
			
			move_result.make_move(possible_moves[move_num]);
			// add the score of the iteration 
			move_score += move_result.score_of_iteration();
		}
		//std::cout << (possible_moves[move_num] >> 4) * 9 + (possible_moves[move_num]&0xf) << "  " << move_score << std::endl;
		// if the current move score is greater than the previous best move and its x's turn
		// or if current move score is less than the previous best move and its o's turn
		if(((best_move_score < move_score) && get_X_move()) || ((best_move_score > move_score) && !get_X_move()))
		{
			// change best move to the current move
			best_move_score = move_score;
			index_of_best_move = move_num;
		}
			
	}
	// return the best move according to the random sampling
	return possible_moves[index_of_best_move];

}
