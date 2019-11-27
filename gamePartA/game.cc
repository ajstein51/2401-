// File: game.cxx

#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include "game.h"     // Provides definition of game class
#include "colors.h"   // Porivdes definition of color class
#include "move.h"     // Provides definition of the space class
using namespace std;

namespace main_savitch_14{
    //*************************************************************************
    // STATIC MEMBER CONSTANTS
    // const int game::SEARCH_LEVELS;
    
    //*************************************************************************
    // PUBLIC MEMBER FUNCTIONS

    game::who game::play( )
    // The play function should not be overridden. It plays one round of the
    // game, with the human player moving first and the computer second.
    // The return value is the winner of the game (or NEUTRAL for a tie).
    {
	restart( );
// Note that as you develop the game you will be gradually un-commenting 
// this function.	
	//while (!is_game_over( )) // un-comment this
	//{
	    display_status( );
	//    if (last_mover( ) == COMPUTER)
		make_human_move( );
	//    else
	//	make_computer_move( );
	//}
	display_status( );
	return HUMAN;
    }


    
    //*************************************************************************
    // OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)

    void game::display_message(const string& message) const
    {
	cout << message;
    }

    string game::get_user_move( ) const
    {
	string answer;
	
	display_message("Your(White/X) move, please: ");
	getline(cin, answer);
	return answer;
    }

    game::who game::winning( ) const
    {
	int value = evaluate( ); // Evaluate based on move that was just made.

	if (value > 0)
	    return last_mover( );
	else if (value < 0)
	    return next_mover( );
	else
	    return NEUTRAL;
    }



    //*************************************************************************
    // PRIVATE FUNCTIONS (these are the same for every game)
/*
    int game::eval_with_lookahead(int look_ahead, int beat_this)
    // Evaluate a board position with lookahead.
    // --int look_aheads:  How deep the lookahead should go to evaluate the move.
    // --int beat_this: Value of another move that we?re considering. If the
    // current board position can't beat this, then cut it short.
    // The return value is large if the position is good for the player who just
    // moved. 
    {
    	queue<string> moves;   // All possible opponent moves
	int value;             // Value of a board position after opponent moves
    	int best_value;        // Evaluation of best opponent move
    	game* future;          // Pointer to a future version of this game
	
        // Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
	    if (last_mover( ) == COMPUTER)
	            return evaluate( );
	    else
		return -evaluate( );
	}

        // Recursive case:
        // The level is above 0, so try all possible opponent moves. Keep the
	// value of the best of these moves from the opponent's perspective.
    	compute_moves(moves); 
	 assert(!moves.empty( ));
    	best_value = INT_MIN;
    	while (!moves.empty( ))
    	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(look_ahead-1, best_value);
	    delete future;
	    if (value > best_value)
	    {
		best_value = value;
	    }
	    moves.pop( );
    	}

    	// The value was calculated from the opponent's perspective.
    	// The answer we return should be from player's perspective, so multiply times -1:
    	return -best_value;
    }

    void game::make_computer_move( )
    {
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;
	
	// Compute all legal moves that the computer could make.
	//compute_moves(moves);
	//assert(!moves.empty( ));
	
	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
	    delete future;
	    if (value >= best_value)
	    {
		best_value = value;
		best_move = moves.front( );
	    }
	    moves.pop( );
	}
	    
	// Make the best move.
	make_move(best_move);
    }
*/
    void game::make_human_move( )
    {
        string move;

	move = get_user_move( );
	while (!is_legal(move))
	{
	    display_message("Illegal move.\n");
	    move = get_user_move( );
        }
	make_move(move);
    }


///////////////////////////////////////////////////////////
	// these are the functions i have written:
///////////////////////////////////////////////////////////

void othello::display_status()const{
	char row[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	cout << "    1    2    3    4    5    6    7    8  " << endl;
	for(int i = 0; i < 8; ++i){
		cout << row[i] << " ";
		for(int j = 0; j < 8; ++j){
			board[i][j].color_output();
		}
		cout << "\n";
	}
}

void othello::restart(){
	game::restart();
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			board[i][j].make_empty();
		}
	}
	board[3][3].make_white();
	board[4][4].make_white();
	board[3][4].make_black();
	board[4][3].make_black();
}

bool othello::is_legal(const string& move)const{
	int x, y;
	x = (int)(move[0]-'A');
	y = (int)(move[1]-'1');
	
	if(x < 8 && x >= 0 && y < 8 && y >= 0){

	// Checks all eight sides to make sure its a legal move, will return true if it is legal and false if not
		if(board[x][y].is_black() && board[x][y + 1].is_white()){
			return false;
		}	
		else if(board[x][y].is_black() && board[x][y - 1].is_white()){
			return false;
		}
		else if(board[x][y].is_black() && board[x - 1][y].is_white()){
			return false;
		}
		else if(board[x][y].is_black() && board[x + 1][y].is_white()){
			return false;
		}
		
		else if(board[x][y].is_black() && board[x+1][y-1].is_white()){
			return false;
		}
		else if(board[x][y].is_black() && board[x+1][y+1].is_white()){
			return false;
		}
		else if(board[x][y].is_black() && board[x+1][y-1].is_white()){
			return false;
		}
		else if(board[x][y].is_black() && board[x+1][y+1].is_white()){
			return false;
		}
		else{
			return true;
		}
		
	// starting stuff for white 
		if(board[x][y].is_white() && board[x][y + 1].is_black()){
			return false;
		}	
		else if(board[x][y].is_white() && board[x][y - 1].is_black()){
			return false;
		}
		else if(board[x][y].is_white() && board[x - 1][y].is_black()){
			return false;
		}
		else if(board[x][y].is_white() && board[x + 1][y].is_black()){
			return false;
		}
		
		else if(board[x][y].is_white() && board[x+1][y-1].is_black()){
			return false;
		}
		else if(board[x][y].is_white() && board[x+1][y+1].is_black()){
			return false;
		}
		else if(board[x][y].is_white() && board[x+1][y-1].is_black()){
			return false;
		}
		else if(board[x][y].is_white() && board[x+1][y+1].is_black()){
			return false;
		}
		else{
			return true;
		}
	}
}

void othello::make_move(const string& move){ // just hard coded 
	if(is_legal(move)){
	if(move == "C5" || move == "C6" || move == "D6"){
		board[3][4].flip();
	}
	if(move == "F3" || move == "F4" || move == "E3"){
		board[4][3].flip();
	}
	}
}




/* Un-needed functions i think?
// The functions below are for the is_legal() function:
bool othello::top_left(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x+1][y-1].is_white()){
		return true;
	}
	return false;
}

bool othello::top_right(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x+1][y+1].is_white()){
		return true;
	}
		return false;
}

bool othello::bottom_left(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x-1][y-1].is_white()){
		return true;
	}
	return false;
}

bool othello::bottom_right(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x-1][y+1].is_white()){
		return true;
	}
		return false;
}

bool othello::look_up(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x][y + 1].is_white()){
		return true;
	}
		return false;
}

bool othello::look_down(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x][y - 1].is_white()){
		return true;
	}
		return false;
}

bool othello::look_left(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x - 1][y].is_white()){
		return true;
	}
		return false;
}

bool othello::look_right(const string& move){
	int x, y;
	x = int(move[0]-'A');
	y = int(move[1] - '1');
	if(board[x][y].is_black() && board[x + 1][y].is_white()){
		return true;
	}
		return false;
}
*/

// just to get the warnings/errors gone
void othello::victory(){
 cout << endl;
}

void othello::compute_moves(std::queue<std::string>& moves)const{
cout << endl;
}

game* othello::clone()const{
	return 0;
}

bool othello::is_game_over()const{
	int j, total;
	// basic counter to 6-
	for(int i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			total++;
		}
	}
	// If total moves hits 60 then the game is over
	if(total == 60)
		return true;
	else 
		return false;
}

int othello::evaluate()const{
	int x = 0, y = 0;
	return x+y;
}






















} // THIS NEEDS TO BE AT THE END OF EVERYTHING