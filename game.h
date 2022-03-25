
/*
Victor Han
March 20th, 2022

*/

#ifndef GAME_H
#define GAME_H



#include <iostream>
#include <vector>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
//#include <string>


#define TOP_LEFT 0
#define TOP_MIDDLE 1
#define TOP_RIGHT 2
#define MIDDLE_LEFT 3
#define MIDDLE 4
#define MIDDLE_RIGHT 5
#define BOTTOM_LEFT 6
#define BOTTOM_MIDDLE 7
#define BOTTOM_RIGHT 8
	
//#define X 'x'
//#define O 'o'

class Ultimate_bit_board;
class Mini_bit_board;

class Mini_bit_board
{
	private:
	// bit representation of which squares x and o occupy
	unsigned short x;
	unsigned short o;
	
	// members that keep track of whether either player has won on this board
	bool x_win;
	bool o_win;
	
	// method that updates the board
	void move(uint_fast8_t pos, bool X);
	
	// brute force functions to check every possible winning combination
	
	inline bool left_vertical(bool X);
	inline bool middle_vertical(bool X);
	inline bool right_vertical(bool X);
	inline bool bottom_horizontal(bool X);
	inline bool middle_horizontal(bool X);
	inline bool top_horizontal(bool X);
	inline bool top_left_diagnol(bool X);
	inline bool bottom_left_diagnol(bool X);
	
	// methods to update whether either player has won on the board
	
	// optimized method
	void update_win_status(int pos, bool X);
	// basic method
	void update_win_status(bool X);
	
	
	public:
	unsigned short get_x();
	unsigned short get_o();
	// methods to return whether either player has won; general and specific
	bool get_win();
	
	bool get_x_win();
	bool get_o_win();
	// function that updates the board and the win status
	void move_and_update(uint_fast8_t pos, bool X);
	
	// function that returns a vector of moves in the sub board
	std::vector<uint_fast8_t> mini_move_list();
	
	
	// default constructor
	Mini_bit_board()
	{
		x = 0;
		o = 0;
		x_win = 0;
		o_win = 0;
	}
	// testing function
	friend void test_print(Mini_bit_board a);
};
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
	
	
	
	inline bool left_vertical(bool X);
	inline bool middle_vertical(bool X);
	inline bool right_vertical(bool X);
	inline bool bottom_horizontal(bool X);
	inline bool middle_horizontal(bool X);
	inline bool top_horizontal(bool X);
	inline bool top_left_diagnol(bool X);
	inline bool bottom_left_diagnol(bool X);
	
	
	public:
	short get_next_board()
	{
		return next_board;
	}
	bool get_X_move()
	{
		return X_move;
	}
	Ultimate_bit_board()
	{
		X_move = true;
		next_board = -1;
		for(int x = 0; x != 9; x++)
			main_board[x] = Mini_bit_board();
	}
	
	Ultimate_bit_board(Ultimate_bit_board* old_board)
	{
		X_move = old_board-> get_X_move();
		next_board =old_board-> get_next_board();
		
		for(int x = 0; x != 9; x++)
			main_board[x] = Mini_bit_board();
	}
	
	// function that puts moves into an array and returns the number of legal moves found
	std::vector<uint_fast8_t> move_list();
	
	void make_move(uint_fast8_t move);
	
	
	
	// methods to check if either player has won
	bool x_win();
	bool o_win();
	
	void terminal_print();
	
	
	
	
	
	uint_fast8_t pick_move();
	int score_of_iteration();
};

#endif