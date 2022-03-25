
/*
Victor Han
March 21st, 2022
*/
#include "game.h"


unsigned short Mini_bit_board::get_x()
{
	return x;
}
unsigned short Mini_bit_board::get_o()
{
	return o;
}

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

void Mini_bit_board::move(uint_fast8_t pos, bool X)
{
	if(X)
		x |= (1 << pos);
	
	else
		o |= (1 << pos);
}

/*
   0   1   2

   3   4   5

   6   7   8
*/


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
		return((x >> BOTTOM_LEFT)&(x >> MIDDLE)&(x >> TOP_RIGHT)&0x01);
	else
		return((o >> BOTTOM_LEFT)&(o >> MIDDLE)&(o >> TOP_RIGHT)&0x01);
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
	
}

void Mini_bit_board::move_and_update(uint_fast8_t pos, bool X)
{
	move(pos,X);
	update_win_status(X);
	
}

std::vector<uint_fast8_t> Mini_bit_board::mini_move_list()
{
	// combines x and o to get the "occupied" spaces, then xor with a "full" int to get the empty spaces 
	uint_fast8_t empty = (x|o) ^ 0x1ff;
	std::vector<uint_fast8_t> mini_movelist;
	for(int pos = 0; pos != 9; pos++)
	{
		if((empty >> pos) & 1)
		{
			mini_movelist.push_back(pos);
		}
	}
	return mini_movelist;
}

