/*
Victor Han
March 21st, 2022
*/
#include "game.h"

int main()
{
	Ultimate_bit_board master_board;
	
	srand (time(NULL));
	int input;
	//std::vector<uint_fast8_t> a = master_board.move_list();
	std::vector<uint_fast8_t> move_history;
	//while(a.size()>0)
	{	

		//int m = rand() % a.size();
		//move_history.push_back(a[m]);
		master_board.make_move(17);
		
		master_board.terminal_print();
		
		//a = master_board.move_list();
		//if(a.size() == 0)
		{
			//break;
		} 

		master_board.make_move(master_board.pick_move());
		
		master_board.terminal_print();
		//a = master_board.move_list();
		//if(a.size() == 0)
		{
			//break;
		} 

	}
	/*
	for(int c =0; c < move_history.size();c++)
	{
		std::cout << (int)move_history[c] << ",";
	}
	*/
	/*
	std::vector<uint_fast8_t> a ={102,99,53,84,67,52,66,32,2,34,39,117,81,22,101,85,87,116,65,17,21,82,33,18,37,86,103,119,115,51,54,96,0,1,20,69,97,23,114,36,71,118,100,70,70,71,112,3,55,113,19,49,37,50,38,39,71,33,129,1,65,53,7,67,5,4,64,6,134,135,129,3,4,133,132,7,131,131,130};
	for(int board_num = 0; board_num != a.size(); ++board_num)
	{
		master_board.make_move(a[board_num]);
		
	}
	
	master_board.terminal_print();
	std::cout << master_board.get_next_board() << master_board.o_win() << master_board.x_win();
	a = master_board.move_list();
	std::cout << a.size();
	*/
	//master_board.terminal_print();
	return 0;
}