/*
Victor Han 
March 20th 2022
Header file containing definition for the main board class and declarations for its methods
*/
#ifndef ULTIMATE_H
#define ULTIMATE_H

#include "mini_board.h"

class Ultimate_bit_board
{
	private:
	// array of smaller boards to make the main game
	Mini_bit_board main_board [9];
	// bool to keep track of whose move it is 
	bool X_move;
	// int to keep track of which board will be played on next
	// -1 means any board can be played on
	// -2 means the game is over
	short next_board;
	
	// brute force functions for every winning combination
	
	inline bool left_vertical(bool X);
	inline bool middle_vertical(bool X);
	inline bool right_vertical(bool X);
	inline bool bottom_horizontal(bool X);
	inline bool middle_horizontal(bool X);
	inline bool top_horizontal(bool X);
	inline bool top_left_diagnol(bool X);
	inline bool bottom_left_diagnol(bool X);
	
	
	public:
	// public members to get private values
	short get_next_board()
	{
		return next_board;
	}
	bool get_X_move()
	{
		return X_move;
	}
	// default constructor 
	Ultimate_bit_board()
	{
		X_move = true;
		next_board = -1;
		for(int x = 0; x != 9; x++)
			main_board[x] = Mini_bit_board();
	}

	Ultimate_bit_board(int* gameinfo);
	Ultimate_bit_board(const uint_fast16_t *,const bool*,const short&);
	
	// function that puts moves into an array and returns the number of legal moves found
	//std::vector<uint_fast8_t> move_list();
	void move_list(uint_fast8_t *, uint_fast8_t &);
	// function to make the move and update other members of the board
	void make_move(uint_fast8_t move);
	void get_fields(uint_fast16_t*,bool*, short*);
	
	
	// methods to check if either player has won
	bool x_win();
	bool o_win();
	
	// method to print the board to he terminal
	void terminal_print();
	uint_fast8_t pick_move();
	int score_of_iteration();

	
};

//uint_fast8_t pick_move(Ultimate_bit_board game_state);
//int score_of_iteration(Ultimate_bit_board test_state);

#endif