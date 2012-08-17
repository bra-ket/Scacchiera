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
	nmoves=56; // io ne conto 28 al massimo. 7 in ogni direzione
    for (int i=1; i<8; i++) {
		int j=4*(i-1);
		possible_moves[j].x=i;
    	possible_moves[j].y=0;
    	possible_moves[j+1].x=0;
    	possible_moves[j+1].y=-i;
		possible_moves[j+2].x=-i;
    	possible_moves[j+2].y=0;
    	possible_moves[j+3].x=0;
    	possible_moves[j+3].y=+i;
		}


}

Rook::~Rook() {
	// TODO Auto-generated destructor stub
}

