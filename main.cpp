/*
Victor Han
March 21st, 2022
*/
#include "game.h"
// method to check if a certain value is in the vector
// used to see if a move entered is in the legal move list
bool move_legal(std::vector<uint_fast8_t> legal_moves,uint_fast8_t movetried)
{
	for(int c = 0; c != legal_moves.size(); c++)
	{
		if(legal_moves[c] == movetried)
		{
			return true;
		}
	}
	return false;
}
int main()
{
	Ultimate_bit_board master_board;
	
	srand (time(NULL));
	int input  = 0;
	std::vector<uint_fast8_t> a = master_board.move_list();
	while(a.size()>0)
	{	
		
		a = master_board.move_list();
		if(a.size() == 0)
		{
			break;
		} 
		uint_fast8_t move = pick_move(master_board);
		master_board.make_move(move);
	
		
		uint_fast8_t user_move = (uint_fast8_t)10;
		move_legal(a,user_move);
		while(!move_legal(a,user_move))
		{
			system("CLS");
			master_board.terminal_print();
			std::cout << "Which board? " << master_board.get_next_board();
			std::cin >> input;
			while(!std::cin >> input)
			{
				std::cout << "Enter a number you idiot";
				std::cin >> input;
			}
			user_move = (input << 4);
			std::cout << "Which spot? ";
			std::cin >> input;
			while(!std::cin >> input)
			{
				std::cout << "Enter a number";
				std::cin >> input;
			}
			user_move |= input;
			
			
			
			
		}

		master_board.make_move(user_move);
		//system("CLS");
		//master_board.terminal_print();
	}
	std::cout << master_board.x_win() << " " << master_board.o_win();
	return 0;
}