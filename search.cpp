/*
Victor Han
March 23rd,2022
file containing the Monte Carlo Tree Search functions for the game
*/

#include "game.h"

// function that returns the result of one iteration
int score_of_iteration(Ultimate_bit_board test_state)
{
	// make moves until the game in this iteration is over
	std::vector<uint_fast8_t> possible_moves = test_state.move_list();
	while(possible_moves.size() != 0)
	{
		test_state.make_move(possible_moves[rand()%possible_moves.size()]);
		possible_moves = test_state.move_list();
	}
	// return -1 if o wins, 1 if x wins, and 0 if the game is drawn
	// this makes x favour higher scores and o favour lower scores
	if(test_state.o_win())
	{
		return -1;
	}
	else if(test_state.x_win())
	{
		return 1;
	}
	return 0;
}
// function that uses Monte Carlo Tree Search to select a move
uint_fast8_t pick_move(Ultimate_bit_board game_state)
{
	
	// get all moves and return 0 if there are no moves
	std::vector<uint_fast8_t> possible_moves = game_state.move_list();
	if(possible_moves.size() == 0)
	{
		return (uint_fast8_t)0;
	}
	// set the default move to 0
	int index_of_best_move = 0;
	int best_move_score = 0;
	// get the number of iterations per move
	const int iterations_per_move = MAX_ITERATIONS / possible_moves.size();
	// set best move score to lowest possible value for x, or highest possible value for o
	if(game_state.get_X_move())
	{
		best_move_score = -1 * iterations_per_move;
	}
	else
	{
		best_move_score = iterations_per_move;
	}
	// iterate through every move to see which one has the highest chance of victory
	for(int move_num = 0; move_num != possible_moves.size(); ++move_num)
	{
		
		int move_score = 0;
		// calculate the score of the random sample
		for(int iteration = 0; iteration < iterations_per_move; ++iteration)
		{
			// make a new board and play the move
			Ultimate_bit_board move_result = game_state;
			move_result.make_move(possible_moves[move_num]);
			// add the score of the iteration 
			move_score += score_of_iteration(move_result);
		}
		// if the current move score is greater than the previous best move and its x's turn
		// or if current move score is less than the previous best move and its o's turn
		if(((best_move_score < move_score) && game_state.get_X_move()) || ((best_move_score > move_score) && !game_state.get_X_move()))
		{
			// change best move to the current move
			best_move_score = move_score;
			index_of_best_move = move_num;
		}
			
	}
	
	// return the best move according to the random sampling
	return possible_moves[index_of_best_move];
}
