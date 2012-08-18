/*
 * Rook.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Rook.h"

Rook::Rook(player p) {
    type='R';
    pla=p;
	possibleMoves.get_allocator().allocate(28);
    for (int i=1; i<8; i++) {
		int j=4*(i-1);
		possibleMoves[j].x=i;
    	possibleMoves[j].y=0;
    	possibleMoves[j+1].x=0;
    	possibleMoves[j+1].y=-i;
		possibleMoves[j+2].x=-i;
    	possibleMoves[j+2].y=0;
    	possibleMoves[j+3].x=0;
    	possibleMoves[j+3].y=+i;
		}


}

Rook::~Rook() {
	// TODO Auto-generated destructor stub
}

