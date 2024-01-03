/*
Victor Han
March 23rd,2022
file containing the Monte Carlo Tree Search functions for the game
*/
#include "game.h"

// function that returns the result of one iteration
int mymax(int x, int y){
	if(x>y){
		return x;
	}
	return y;
}
int mymin(int x, int y){
	if(x>y){
		return y;
	}
	return x;
}
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
int Ultimate_bit_board::evaluate_random(const int &iterations){
	if(o_win()){
		return -1 * iterations;
	}
	else if(x_win()){
		return iterations;
	}
	int move_score = 0;
	for(int iteration = 0; iteration < iterations; ++iteration)
		{

			// make a new board and play the move
			uint_fast16_t board_contents[18];
			bool win_contents[18];
			get_fields(board_contents,win_contents);
			Ultimate_bit_board move_result(board_contents,win_contents,next_board,move_number,X_move);
			
			// add the score of the iteration 
			move_score += move_result.score_of_iteration();
		}
		return move_score;
}
int Ultimate_bit_board::alpha_beta_search(int alpha, int beta, const int &depth, const int &iterations_requested){
	if(alpha >= beta){
		return alpha;
	}
	if(o_win()){
		return -1 * iterations_requested;
	}
	if(x_win()){
		return iterations_requested;
	}
	if(depth == 0){
		return evaluate_random(iterations_requested); 
	}
	uint_fast8_t possible_moves[81];
	uint_fast8_t size = 0;
	move_list(possible_moves, size);
	if(size == 0){
		return 0;
	}
	int value = get_X_move() ? -1 * iterations_requested : iterations_requested;
	
	for(int move_num = 0; move_num != size; ++move_num)
	{

		uint_fast16_t board_contents[18];
		bool win_contents[18];
		get_fields(board_contents,win_contents);
		Ultimate_bit_board move_result(board_contents,win_contents,next_board,move_number,X_move);
			
		move_result.make_move(possible_moves[move_num]);
		if(get_X_move()){
			const int move_value = move_result.alpha_beta_search(alpha,beta,depth-1,iterations_requested);
			value = mymax(move_value,value);
			alpha = mymax(alpha,value);
		}
		else{
			const int move_value = move_result.alpha_beta_search(alpha,beta,depth-1,iterations_requested);
			value = mymin(move_value,value);
			beta = mymin(beta,value);
		}
	}
	
	return value;
}
uint_fast8_t Ultimate_bit_board::top_level_alpha_beta(const int& depth, const int& iterations_requested){
	uint_fast8_t possible_moves[81];
	uint_fast8_t size = 0;
	
	move_list(possible_moves, size);
	int alpha = -1 * iterations_requested, beta = iterations_requested;
	int value = get_X_move() ? alpha : beta;
	int best_move_index = 0;
	for(int move_num = 0; move_num != size; ++move_num)
	{

		uint_fast16_t board_contents[18];
		bool win_contents[18];
		get_fields(board_contents,win_contents);
		Ultimate_bit_board move_result(board_contents,win_contents,next_board,move_number,X_move);
			
		move_result.make_move(possible_moves[move_num]);
		if(get_X_move()){
			const int move_value = move_result.alpha_beta_search(alpha,beta,depth-1,iterations_requested);
			if(move_value > value){
				value = move_value;
				alpha = value;
				best_move_index = move_num;
			}
		}
		else{
			const int move_value = move_result.alpha_beta_search(alpha,beta,depth-1,iterations_requested);
			if(move_value < value){
				value = move_value;
				beta = value;
				best_move_index = move_num;
			}
		}
	}
	return possible_moves[best_move_index];
}
// function that uses Monte Carlo Tree Search to select a move
uint_fast8_t Ultimate_bit_board::pick_move()
{
	if(move_number > 55){
		return top_level_alpha_beta(30,0);
	}
	if(move_number > 50){
		return top_level_alpha_beta(20,5);
	}
	if(move_number > 45){
		return top_level_alpha_beta(11,5);
	}
	if(move_number > 40){
		return top_level_alpha_beta(10,10);
	}
	if(move_number > 35){
		return top_level_alpha_beta(9, 20);
	}
	if(move_number > 30){
		return top_level_alpha_beta(8, 100);
	}
	if(move_number > 25){
		return top_level_alpha_beta(7, 150);
	}
	if(move_number > 20){
		return top_level_alpha_beta(6, 1000);
	}
	if(move_number > 15){
		return top_level_alpha_beta(4, 3000);
	}
	if(move_number > 10){
		return top_level_alpha_beta(4, 1500);

	}
	if(move_number > 5){
		return top_level_alpha_beta(4, 1000);
	}
	return top_level_alpha_beta(2, 10000);
}
