/*
 * Bishop.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Bishop.h"

Bishop::Bishop(player p) {
	type='B';
    pla=p;
    possibleMoves.get_allocator().allocate(32);
     for (int i=1; i<8; i++) {
		possibleMoves[4*i].x=i;
    	possibleMoves[4*i].y=i;
    	possibleMoves[4*i+1].x=i;
    	possibleMoves[4*i+1].y=-i;
		possibleMoves[4*i+2].x=-i;
    	possibleMoves[4*i+2].y=-i;
    	possibleMoves[4*i+3].x=-i;
    	possibleMoves[4*i+3].y=+i;
		}
}

Bishop::~Bishop() {
	// TODO Auto-generated destructor stub
}


