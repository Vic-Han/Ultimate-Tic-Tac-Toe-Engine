



/*
Victor Han
March 21st, 2022
file containing all the definitions for the methods in the ultimate board class
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
	return (left_vertical(true) || middle_vertical(true) ||  right_vertical(true) || bottom_horizontal(true) || middle_horizontal(true) || top_horizontal(true) || bottom_left_diagnol(true) || top_left_diagnol(true) );
	
}	
bool Ultimate_bit_board::o_win(){
	
	return (left_vertical(false) || middle_vertical(false) ||  right_vertical(false) || bottom_horizontal(false) || middle_horizontal(false) || top_horizontal(false) || bottom_left_diagnol(false) || top_left_diagnol(false) );
}

// method to make the move on the main board
void Ultimate_bit_board::make_move(uint_fast8_t move)
{
	// the four least significant bits(move & 0xf) represent where on the local board the piece will be placed
	// the 5th-8th least significant bits(move >> 4) represnt which local board to place the piece
	// bits 9-16 are not used
	main_board[move >> 4].move_and_update((move & 0xf),X_move);
	// switch whose move is it
	X_move = !X_move;
	// if either player wins the main board, the game is over
	if(x_win() || o_win())
	{
		next_board = NOWHERE;
	}
	// if the next board is occupied by either player, the next move can be placed on any board
	else if(main_board[move&0xf].get_win())
	{
		next_board = ANYWHERE;
	}
	// the next board is not yet occupied, so the next move must be placed there
	else
	{
		next_board = (move&0xf);
	}
	move_number++;
}
// method to get all legal moves
/*
std::vector<uint_fast8_t> Ultimate_bit_board::move_list()
{
	// the four least significant bits represent where on the local board to place the move
	// the 5-8th least significant bits represent which local board to place the move
	std::vector<uint_fast8_t> main_move_list;
	
	// moves can only be placed on one local board
	if(next_board > ANYWHERE)
	{
		// gets the moves, but only the location on the local board, not the local board itself
		main_move_list = main_board[next_board].mini_move_list();
		// add the local board to each element by shifting the number of the board to the 5th-8th bits
		for(int index = 0; index != main_move_list.size(); ++index)
		{
			main_move_list[index] |= (next_board << 4);
		}
	}
	
	// moves can be placed on any local board
	else if(next_board == ANYWHERE)
	{
		// iterate through every board
		for(int board_num = 0; board_num != 9; ++board_num)
		{
			// local board is already occupied, so cannot place moves here
			if(main_board[board_num].get_win())
			{
				continue;
			}
			// get the moves on the local board, but with the position of the local board itself
			std::vector<uint_fast8_t> temp_vec = main_board[board_num].mini_move_list();
			// add the local board to each element by shifting the number of the board to the 5th-8th bits, then add to main vector
			for(int index = 0; index != temp_vec.size(); ++index)
			{
				main_move_list.push_back( temp_vec[index] | (board_num << 4) );
			}
		}
	}
	return main_move_list;
}*/
void Ultimate_bit_board::move_list(uint_fast8_t *main_move_list, uint_fast8_t & size)
{
	// the four least significant bits represent where on the local board to place the move
	// the 5-8th least significant bits represent which local board to place the move
	// moves can only be placed on one local board
	if(next_board > ANYWHERE)
	{
		// gets the moves, but only the location on the local board, not the local board itself
		main_board[next_board].mini_move_list(main_move_list, size);
		// add the local board to each element by shifting the number of the board to the 5th-8th bits
		for(int index = 0; index != size; ++index)
		{
			main_move_list[index] |= (next_board << 4);
		}
	}
	
	// moves can be placed on any local board
	else if(next_board == ANYWHERE)
	{
		// iterate through every board
		for(int board_num = 0; board_num != 9; ++board_num)
		{
			// local board is already occupied, so cannot place moves here
			if(main_board[board_num].get_win())
			{
				continue;
			}
			// get the moves on the local board, but with the position of the local board itself
			uint_fast8_t size_bef = size;
			main_board[board_num].mini_move_list(main_move_list, size);
			// add the local board to each element by shifting the number of the board to the 5th-8th bits, then add to main vector
			for(int index = size_bef; index != size; ++index)
			{
				main_move_list[index] |= (board_num << 4);
			}
			
		}
	}
}
// method to print board to terminal
/*
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
						std::cout << " - ";
				}
			
				std::cout << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
		
	}
	
	
	
	
}*/

Ultimate_bit_board::Ultimate_bit_board(int *gameinfo)
{
	move_number = 0;
	next_board = gameinfo[0];
	if(gameinfo[1] == 1)
	{
		X_move = true;
	}
	else
	{
		X_move = false;
	}
	
	for(int outer = 0; outer < 9; outer++)
	{
		uint_fast8_t temp[9];
		for(int inner = 0; inner <  9; inner++ )
		{
			temp[inner] = gameinfo[(outer * 9) + inner + 2];
		}

		main_board[outer] = Mini_bit_board(temp);
	}

}
void Ultimate_bit_board::simulate_game(uint_fast8_t *movelist, int list_size){
	for(int move_num = 0; move_num < list_size; move_num++){
		make_move(movelist[move_num]);
	}

}
void Ultimate_bit_board::get_fields(uint_fast16_t * board_contents, bool *win_contents)
{	
	for(int x = 0; x < 9; x ++)
	{
		board_contents[x] = main_board[x].get_x();
		board_contents[x+9] = main_board[x].get_o();
		win_contents[x] = main_board[x].get_x_win();
		win_contents[x+9] = main_board[x].get_o_win();
	}
}
Ultimate_bit_board::Ultimate_bit_board(const uint_fast16_t *board_contents,const bool *win_contents, const short &nextBoard, const short &moveNumber, const bool xMove)
{
	X_move = xMove;
	move_number = moveNumber;
	next_board = nextBoard;
	for(int x = 0; x < 9; x++)
	{
		main_board[x] = Mini_bit_board(board_contents[x],board_contents[x+9],win_contents[x],win_contents[x+9]);
	}
}

