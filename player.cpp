#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	Board *current = new Board();
	Side mySide = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() 
{
	delete &current;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
	Move *my = new Move(0,0);
	Side otherSide = WHITE;

	if(mySide == WHITE)
	{
		otherSide = BLACK;
	}
	current -> doMove(opponentsMove, otherSide); //make this opponent side
	std::cerr << "hi" << std::endl;
	if(!current->hasMoves(mySide))
	{
		return NULL;
	}
	else
	{
		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++)
			{
				my = new Move(x,y);
				if(current -> checkMove(my, mySide))
				{
					break;
				}
			}
		}
	}
	return my;
}
