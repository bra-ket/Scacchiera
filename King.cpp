/*
 * King.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "King.h"

King::King(player p) {
	type='K';
    pla=p;
    possibleMoves.get_allocator().allocate(8);
    possibleMoves[0].x=1;
    possibleMoves[0].y=1;
    possibleMoves[1].x=1;
    possibleMoves[1].y=0;
	possibleMoves[2].x=1;
    possibleMoves[2].y=-1;
    possibleMoves[3].x=0;
    possibleMoves[3].y=-1;
    possibleMoves[4].x=-1;
    possibleMoves[4].y=-1;
    possibleMoves[5].x=-1;
    possibleMoves[5].y=0;
    possibleMoves[6].x=-1;
    possibleMoves[6].y=1;
    possibleMoves[7].x=0;
    possibleMoves[7].y=1;
 
}

King::~King() {
	// TODO Auto-generated destructor stub
}


