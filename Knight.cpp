
#include "Knight.h"

Knight::Knight(player p) {
	// creating array of possible moves
    Delta d;
    for (int i=0; i<8; i++) possibleMoves.push_back(d);
    possibleMoves[0].x=2;
    possibleMoves[0].y=1;
    possibleMoves[1].x=1;
    possibleMoves[1].y=2;
    possibleMoves[2].x=-1;
    possibleMoves[2].y=2;
    possibleMoves[3].x=-2;
    possibleMoves[3].y=1;
    possibleMoves[4].x=-2;
    possibleMoves[4].y=-1;
    possibleMoves[5].x=1;
    possibleMoves[5].y=-2;
    possibleMoves[6].x=-1;
    possibleMoves[6].y=-2;
    possibleMoves[7].x=2;
    possibleMoves[7].y=-1;
    
	type='N';
    pl=p;
}
