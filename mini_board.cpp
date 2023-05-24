
/*
Victor Han
March 21st, 2022
*/
//#include <emscripten.h>
#include "game.h"
// methods to get private values x and o


uint_fast16_t Mini_bit_board::get_x()
{
	return x;
}


uint_fast16_t Mini_bit_board::get_o()
{
	return o;
}

// methods to check if either player has won, and to check each individually
bool Mini_bit_board::get_win()
{
	return (o_win || x_win);
}


bool Mini_bit_board::get_x_win()
{
	return x_win;
}

bool Mini_bit_board::get_o_win()
{
	return o_win;
}

// makes the move on the local board

void Mini_bit_board::move(uint_fast8_t pos, bool X)
{
	if(X)
		x |= (1 << pos);
	
	else
		o |= (1 << pos);
}


// functions for each winning combination, 8 in total
// since its just a 3X3, it is easier to brute force every combination manually rather than make a general algorithm to find a sequence of a certain length


// winning sequence of bottom left, middle left, and top left

bool Mini_bit_board::left_vertical(bool X)
{
	if(X)
		return((x >> TOP_LEFT)&(x >> MIDDLE_LEFT)&(x >> BOTTOM_LEFT)&0x01);
	else
		return((o >> TOP_LEFT)&(o >> MIDDLE_LEFT)&(o >> BOTTOM_LEFT)&0x01);
}
// winning sequence of bottom middle, middle, and top middle

bool Mini_bit_board::middle_vertical(bool X)
{
	if(X)
		return((x >> TOP_MIDDLE)&(x >> MIDDLE)&(x >> BOTTOM_MIDDLE)&0x01);
	else
		return((o >> TOP_MIDDLE)&(o >> MIDDLE)&(o >> BOTTOM_MIDDLE)&0x01);
}
// winning sequence of bottom right, middle right, and top right

bool Mini_bit_board::right_vertical(bool X)
{
	if(X)
		return((x >> TOP_RIGHT)&(x >> MIDDLE_RIGHT)&(x >> BOTTOM_RIGHT)&0x01);
	else
		return((o >> TOP_RIGHT)&(o >> MIDDLE_RIGHT)&(o >> BOTTOM_RIGHT)&0x01);
}
// winning sequence of bottom left, bottom middle, and bottom right

bool Mini_bit_board::bottom_horizontal(bool X)
{
	if(X)
		return((x >> BOTTOM_LEFT)&(x >> BOTTOM_MIDDLE)&(x >> BOTTOM_RIGHT)&0x01);
	else
		return((o >> BOTTOM_LEFT)&(o >> BOTTOM_MIDDLE)&(o >> BOTTOM_RIGHT)&0x01);
}
// winning sequence of middle left, middle, and middle right

bool Mini_bit_board::middle_horizontal(bool X)
{
	if(X)
		return((x >> MIDDLE_LEFT)&(x >> MIDDLE)&(x >> MIDDLE_RIGHT)&0x01);
	else
		return((o >> MIDDLE_LEFT)&(o >> MIDDLE)&(o >> MIDDLE_RIGHT)&0x01);
}
// winning sequence of top left, top middle, and top right

bool Mini_bit_board::top_horizontal(bool X)
{
	if(X)
		return((x >> TOP_LEFT)&(x >> TOP_MIDDLE)&(x >> TOP_RIGHT)&0x01);
	else
		return((o >> TOP_LEFT)&(o >> TOP_MIDDLE)&(o >> TOP_RIGHT)&0x01);
}

// winning sequence of top left, middle, bottom right

bool Mini_bit_board::top_left_diagnol(bool X)
{
	if(X)
		return((x >> TOP_LEFT)&(x >> MIDDLE)&(x >> BOTTOM_RIGHT)&0x01);
	else
		return((o >> TOP_LEFT)&(o >> MIDDLE)&(o >> BOTTOM_RIGHT)&0x01);
}

// winning sequence of bottom left, middle and top right

bool Mini_bit_board::bottom_left_diagnol(bool X)
{
	if(X)
		return((x >> BOTTOM_LEFT)&(x >> MIDDLE)&(x >> TOP_RIGHT)&0x01) == 1;
	else
		return((o >> BOTTOM_LEFT)&(o >> MIDDLE)&(o >> TOP_RIGHT)&0x01) == 1;
}  

// updates the win status of the class by calling the methods for each possible winning combination

void Mini_bit_board::update_win_status(bool X)
{
	if(X)
		x_win |= ( left_vertical(X) || middle_vertical(X) ||  right_vertical(X) || bottom_horizontal(X) || middle_horizontal(X) || top_horizontal(X) || bottom_left_diagnol(X) || top_left_diagnol(X) );
	else
		o_win |= ( left_vertical(X) || middle_vertical(X) ||  right_vertical(X) || bottom_horizontal(X) || middle_horizontal(X) || top_horizontal(X) || bottom_left_diagnol(X) || top_left_diagnol(X) );
}

// optimized version that only checks the lines relavant to the move just made
// ie. if the move is bottom left, will only check the diagnol, bottom row, and leftmost column 


void Mini_bit_board::update_win_status(int pos, bool X)
{
	bool win = false;
	switch(pos)
	{
		case TOP_LEFT:
			win = top_left_diagnol(X) || left_vertical(X) || top_horizontal(X);
			break;
		case TOP_MIDDLE:
			win = top_horizontal(X) || middle_vertical(X);
			break;
		case TOP_RIGHT:
			win = bottom_left_diagnol(X) || top_horizontal(X) || right_vertical(X);
			break;
		case MIDDLE_LEFT:
			win = left_vertical(X) || middle_horizontal(X);
			break;
		case MIDDLE:
			win = top_left_diagnol(X) || middle_horizontal(X) || middle_vertical(X) || bottom_left_diagnol(X);
			break;
		case MIDDLE_RIGHT:
			win = middle_horizontal(X) || right_vertical(X);
			break;
		case BOTTOM_LEFT:
			win = bottom_horizontal(X) || left_vertical(X) || bottom_left_diagnol(X);
			break;
		case BOTTOM_MIDDLE:
			win = bottom_horizontal(X) || middle_vertical(X);
			break;
		case BOTTOM_RIGHT:
			win = bottom_horizontal(X) || left_vertical(X) || top_left_diagnol(X);
			break;

	}
	if(X)
	{
		x_win = win;
	}
	else
	{
		o_win = win;
	}
}

// method that calls the other methods to fully update the local board

void Mini_bit_board::move_and_update(uint_fast8_t pos, bool X)
{
	move(pos,X);
	update_win_status(X);
	
}
// methods that checks all legal moves in a local board
// only gives the position on the local board, excludes which local board is chosen
/*
std::vector<uint_fast8_t> Mini_bit_board::mini_move_list()
{
	// combines x and o to get the "occupied" spaces, then xor with a "full" int to get the empty spaces 
	
	uint_fast16_t empty = (x|o) ^ 0x1ff;
	// vector to store all movxes
	std::vector<uint_fast8_t> mini_movelist;
	// loop through the empty spaces
	for(int pos = 0; pos != 9; pos++)
	{
		// if bit n is true in empty, add this move to the vector
		if(((empty >> pos) & 1) == 1)
		{
			mini_movelist.push_back(pos);
		}
	}
	return mini_movelist;
}*/

void Mini_bit_board::mini_move_list(uint_fast8_t * mini_movelist, uint_fast8_t & size)
{
	// combines x and o to get the "occupied" spaces, then xor with a "full" int to get the empty spaces 
	
	uint_fast16_t empty = (x|o) ^ 0x1ff;
	// vector to store all movxes
	// loop through the empty spaces
	for(int pos = 0; pos != 9; pos++)
	{
		// if bit n is true in empty, add this move to the vector
		if(((empty >> pos) & 1) == 1)
		{
			mini_movelist[size++] = pos;
		}
	}
}
/*
EMSCRIPTEN_KEEPALIVE
void test_print(Mini_bit_board a)
{
	unsigned short temp_x = a.x;
	unsigned short temp_o = a.o;
	for(int hor = 0; hor != 3; hor++)
	{
		for(int vert = 0; vert != 3; vert++)
		{
			if( (temp_o & 1) == 1)
				std::cout << " O ";
			else if((temp_x & 1) == 1)
				std::cout << " X ";
			else
				std::cout << " E ";
			
			
			temp_x = temp_x >> 1;
			temp_o = temp_o >> 1;
		}
		std::cout << std::endl;
	}	
}*/
/*
Mini_bit_board::Mini_bit_board(std::vector<int> board_info)
{
	for(int pos = 0; pos< 9; pos++)
	{
		if(board_info[pos] == 2)
		{
			o |= 1 << pos;
		}
		else if(board_info[pos] == 1)
		{
			x |= 1 << pos;
		}	
	}
	update_win_status(true);
	update_win_status(false);
}*/

Mini_bit_board::Mini_bit_board(uint8_t* board_info)
{
	o_win = false; x_win = false;
	x = 0, o = 0;
	for(int pos = 0; pos< 9; pos++)
	{
		if(board_info[pos] == 2)
		{
			o |= 1 << pos;
		}
		else if(board_info[pos] == 1)
		{
			x |= 1 << pos;
		}	
	}
	update_win_status(true);
	update_win_status(false);
	//std::cout << get_x() << " " << get_o() << "          ";
	//std::cout << get_win() << " " << get_o_win() <<std::endl;
}
Mini_bit_board::Mini_bit_board(const uint_fast16_t& x_val ,const uint_fast16_t& o_val,const bool x_w,const bool o_w)
{
	x = x_val;
	o = o_val;
	x_win = x_w;
	o_win = o_w;
}