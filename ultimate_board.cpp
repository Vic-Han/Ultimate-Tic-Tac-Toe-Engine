



/*
Victor Han
March 21st, 2022
*/
#include "game.h"



// winning sequence of bottom left, middle left, and top left
bool Ultimate_bit_board::left_vertical(bool X)
{
	if(X)
		return(main_board[TOP_LEFT].get_x_win() && main_board[MIDDLE_LEFT].get_x_win() && main_board[BOTTOM_LEFT].get_x_win());
	else
		return(main_board[TOP_LEFT].get_o_win() && main_board[MIDDLE_LEFT].get_o_win() && main_board[BOTTOM_LEFT].get_o_win());
}
// winning sequence of bottom middle, middle, and top middle
bool Ultimate_bit_board::middle_vertical(bool X)
{
	if(X)
		return(main_board[TOP_MIDDLE].get_x_win() && main_board[MIDDLE].get_x_win() && main_board[BOTTOM_MIDDLE].get_x_win());
	else
		return(main_board[TOP_MIDDLE].get_o_win() && main_board[MIDDLE].get_o_win() && main_board[BOTTOM_MIDDLE].get_o_win());
}
// winning sequence of bottom right, middle right, and top right
bool Ultimate_bit_board::right_vertical(bool X)
{
	if(X)
		return(main_board[TOP_RIGHT].get_x_win() && main_board[MIDDLE_RIGHT].get_x_win() && main_board[BOTTOM_RIGHT].get_x_win());
	else
		return(main_board[TOP_RIGHT].get_o_win() && main_board[MIDDLE_RIGHT].get_o_win() && main_board[BOTTOM_RIGHT].get_o_win());
}
// winning sequence of bottom left, bottom middle, and bottom right
bool Ultimate_bit_board::bottom_horizontal(bool X)
{
	if(X)
		return(main_board[BOTTOM_LEFT].get_x_win() && main_board[BOTTOM_MIDDLE].get_x_win() && main_board[BOTTOM_RIGHT].get_x_win());
	else
		return(main_board[BOTTOM_LEFT].get_o_win() && main_board[BOTTOM_MIDDLE].get_o_win() && main_board[BOTTOM_RIGHT].get_o_win());
}
// winning sequence of middle left, middle, and middle right
bool Ultimate_bit_board::middle_horizontal(bool X)
{
	if(X)
		return(main_board[MIDDLE_LEFT].get_x_win() && main_board[MIDDLE].get_x_win() && main_board[MIDDLE_RIGHT].get_x_win());
	else
		return(main_board[MIDDLE_LEFT].get_o_win() && main_board[MIDDLE].get_o_win() && main_board[MIDDLE_RIGHT].get_o_win());
}
// winning sequence of top left, top middle, and top right
bool Ultimate_bit_board::top_horizontal(bool X)
{
	if(X)
		return(main_board[TOP_LEFT].get_x_win() && main_board[TOP_MIDDLE].get_x_win() && main_board[TOP_RIGHT].get_x_win());
	else
		return(main_board[TOP_LEFT].get_o_win() && main_board[TOP_MIDDLE].get_o_win() && main_board[TOP_RIGHT].get_o_win());
}

// winning sequence of top left, middle, bottom right
bool Ultimate_bit_board::top_left_diagnol(bool X)
{
	if(X)
		return(main_board[TOP_LEFT].get_x_win() && main_board[MIDDLE].get_x_win() && main_board[BOTTOM_RIGHT].get_x_win());
	else
		return(main_board[TOP_LEFT].get_o_win() && main_board[MIDDLE].get_o_win() && main_board[BOTTOM_RIGHT].get_o_win());
}

// winning sequence of bottom left, middle and top right
bool Ultimate_bit_board::bottom_left_diagnol(bool X)
{
	if(X)
		return(main_board[BOTTOM_LEFT].get_x_win() && main_board[MIDDLE].get_x_win() && main_board[TOP_RIGHT].get_x_win());
	else
		return(main_board[BOTTOM_LEFT].get_o_win() && main_board[MIDDLE].get_o_win() && main_board[TOP_RIGHT].get_o_win() ) ;
}  

// updates the win status of the class by calling the methods for each possible winning combination
bool Ultimate_bit_board::x_win()
{
	return ( left_vertical(true) || middle_vertical(true) ||  right_vertical(true) || bottom_horizontal(true) || middle_horizontal(true) || top_horizontal(true) || bottom_left_diagnol(true) || top_left_diagnol(true) );
	
}	
bool Ultimate_bit_board::o_win(){
	
	return ( left_vertical(false) || middle_vertical(false) ||  right_vertical(false) || bottom_horizontal(false) || middle_horizontal(false) || top_horizontal(false) || bottom_left_diagnol(false) || top_left_diagnol(false) );
}



void Ultimate_bit_board::make_move(uint_fast8_t move)
{
	main_board[move >> 4].move_and_update((move & 0xf),X_move);
	X_move = !X_move;
	if(x_win() || o_win())
	{
		next_board = -2;
	}
	else if(main_board[move&0xf].get_win())
		next_board = -1;
	else
		next_board = (move&0xf);
	
}
std::vector<uint_fast8_t> Ultimate_bit_board::move_list()
{
	// the four least significant bits represent where on the sub board to place the move
	// the 5-8th least significant bits represent which sub board to place the move
	std::vector<uint_fast8_t> main_move_list;
	
	// moves can only be placed on one sub board
	if(next_board >= 0)
	{
		main_move_list = main_board[next_board].mini_move_list();
		for(int index = 0; index != main_move_list.size(); ++index)
		{
			main_move_list[index] |= (next_board << 4);
		}
	}
	
	// moves can be placed on any sub board
	else if(next_board == -1)
	{
		for(int board_num = 0; board_num != 9; ++board_num)
		{
			// sub board is already occupied, so cannot place moves here
			if(main_board[board_num].get_win())
			{
				continue;
			}
			
			std::vector<uint_fast8_t> temp_vec = main_board[next_board].mini_move_list();
			for(int index = 0; index != temp_vec.size(); ++index)
			{
				main_move_list.push_back( temp_vec[index] | (board_num << 4) );
				std::vector<int> retard;
				for(int x = 0; x < main_move_list.size(); x++)
				{
					retard.push_back(main_move_list[x]);
				}
				for(int x = 0; x < main_move_list.size(); x++)
				{
					std::cout << retard[x] << " ";
				}
			}
		}
	}
	
	
	return main_move_list;
}

void Ultimate_bit_board::terminal_print()
{
	
	for(int main_board_row = 0; main_board_row < 3; ++main_board_row)
	{
		for(int local_board_row = 0; local_board_row < 3; ++local_board_row)
		{
			for(int main_column = 0; main_column < 3; ++main_column)
			{
				int current_x = main_board[main_board_row*3+main_column].get_x();
				int current_o = main_board[main_board_row*3+main_column].get_o();
				
				current_x = (current_x >> (local_board_row*3)) & 0x7;
				current_o = (current_o >> (local_board_row*3)) & 0x7;
				
				for(int local_column = 0; local_column < 3; ++local_column)
				{
					if( ((current_o >> local_column) & 1) == 1)
						std::cout << " O ";
					else if(((current_x >> local_column) & 1) == 1)
							std::cout << " X ";
					else
						std::cout << " E ";
				}
			
				std::cout << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
		
	}
	
	
	
	
}


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
	if(a.x_win)
		std::cout << "X wins";
}

