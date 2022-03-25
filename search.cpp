/*
Victor Han
March 23rd,2022

*/

#include "game.h"

uint_fast8_t Ultimate_bit_board::pick_move()
{
	
	
	std::vector<uint_fast8_t> possible_moves = move_list();
	/*
	std::vector<int> retard;
	for(int x = 0; x < possible_moves.size(); x++)
	{
		retard.push_back(possible_moves[x]);
	}
	for(int x = 0; x < possible_moves.size(); x++)
	{
		std::cout << retard[x] << " ";
	}
	*/
	//std::cout << possible_moves.size() << std::endl;
	int index_of_best_move = 0;
	int best_move_score = 0;
	/*
	if(X_move)
	{
		best_move_score = -1;
	}
	else
	{
		best_move_score = 1;
	}
	
	for(int move_num = 0; move_num != 1; ++move_num)
	{
		std::cout << "dsafsdf" << std::endl;
		Ultimate_bit_board move_result = (*this);
		move_result.make_move(possible_moves[move_num]);
		int move_score = 0;
		
		for(int iteration = 0; iteration < 1; ++iteration)
		{
			move_score += move_result.score_of_iteration();
		}
		if((best_move_score < move_score && X_move) ||(best_move_score > move_score && !X_move))
		{
			best_move_score = move_score;
			index_of_best_move = move_num;
		}
		
	}
	*/
	//std::cout << possible_moves.size() << std::endl;
	
	return possible_moves[index_of_best_move];
}


int Ultimate_bit_board::score_of_iteration()
{
	std::vector<uint_fast8_t> possible_moves = move_list();
	if(possible_moves.size() == 0)
	{
		if(o_win())
		{
			return -1;
		}
		if(x_win())
		{
			return 1;
		}
		return 0;
		
	}

	Ultimate_bit_board temp = (*this);
	std::cout << &temp << " " << this << std::endl;
	srand(time(NULL));
	temp.make_move(possible_moves[rand()%possible_moves.size()]);
	return temp.score_of_iteration();
}
