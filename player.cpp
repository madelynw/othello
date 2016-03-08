#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	current = new Board();
	mySide = side;
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
	std::vector<Move*> possible;
	int score;

	if(mySide == WHITE)
	{
		otherSide = BLACK;
	}
	
	current -> doMove(opponentsMove, otherSide);
	if(!(current->hasMoves(mySide)))
	{
		return NULL;
	}
	else
	{
		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++)
			{
				*my = Move(x,y);
				if(current -> checkMove(my, mySide))
				{
					Move *holder = new Move(my->getX(), my->getY());
					possible.push_back(holder);
				}
			}
		}
	}
	
	int maxscore = -100000000;
	for (int i = 0; i < (int) possible.size(); i++)
	{	
		// Create testboard to test possible moves.
		testboard = current->copy();
		testboard->doMove(possible[i], mySide);
		
		// Calculate initial score.
		score = testboard->count(mySide) - testboard->count(otherSide);
		
		// Get x and y values of possible move.
		int x = possible[i]->getX();
		int y = possible[i]->getY();
		
		// Weight the scores based on the move.
		// Corner cases
		if ((x == 0 && y == 0) || (x == 0 && y == 7) || \
		(x == 7 && y == 0) || (x == 7 && y == 7))
		{
			score *= 123;
		}
		// Bad edge cases
		else if ((x == 1 && y == 0) || (x == 6 && y == 0) || \
		(x == 0 && y == 1) || (x == 7 && y == 1) || \
		(x == 0 && y == 6) || (x == 7 && y == 6) || \
		(x == 1 && y == 7) || (x == 6 && y == 7))
		{
			score *= -23;
		}
		else if ((x == 2 && y == 2) || (x == 5 && y == 2) || \
		(x == 2 && y == 5) || (x == 5 && y == 5))
		{
			score *= 13;
		}
		// Good edge cases
		else if ((x == 0) || (x == 7) || (y == 0) || (y == 7))
		{
			score *= 29;
		}
		// Really bad corner giving moves
		else if ((x == 1 && y == 1) || (x == 6 && y == 6) || \
		(x == 1 && y == 6) || (x == 6 && y == 1))
		{
			score *= -100;
		}
		if (score > maxscore)
		{
			maxscore = score;
			my = possible[i];
		}
	}
	current -> doMove(my, mySide);
	return my;
}
