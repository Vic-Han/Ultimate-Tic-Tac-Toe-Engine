/*
Victor Han
March 20th,2022
header file with definition for local board class and delcarations for its methods
*/
#ifndef MINI_H
#define MINI_H

#include <iostream>
//#include <vector>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <string>
// class to represent a local board
class Mini_bit_board
{
	private:
	// bit representation of which squares x and o occupy
	uint_fast16_t x;
	uint_fast16_t o;
	
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
	// methods to return the bit representations
	uint_fast16_t get_x();
	uint_fast16_t get_o();
	// methods to return whether either player has won; general and specific
	bool get_win();
	
	bool get_x_win();
	bool get_o_win();
	// function that updates the board and the win status
	void move_and_update(uint_fast8_t pos, bool X);
	
	// function that returns a vector of moves in the sub board
	//std::vector<uint_fast8_t> mini_move_list();
	void mini_move_list(uint_fast8_t *, uint_fast8_t &);
	
	// default constructor
	Mini_bit_board()
	{
		x = 0x0;
		o = 0x0;
		x_win = 0;
		o_win = 0;
	}
	//Mini_bit_board(std::vector<int>);
	Mini_bit_board(uint_fast8_t *);
	Mini_bit_board(const uint_fast16_t&,const uint_fast16_t&,const bool,const bool);
	// testing function to print only one board
	friend void test_print(Mini_bit_board a);
};

#endif