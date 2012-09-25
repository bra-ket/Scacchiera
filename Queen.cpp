/*
 * Queen.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Queen.h"

Queen::Queen(player p) {
	type='Q';
    pla=p;
    Delta d;
    for (int i=0; i<56; i++) possibleMoves.push_back(d);
    for (int i=1; i<8; i++) {
		int j=8*(i-1);
		possibleMoves[j].x=i;
    	possibleMoves[j].y=i;
    	possibleMoves[j+1].x=i;
    	possibleMoves[j+1].y=-i;
		possibleMoves[j+2].x=-i;
    	possibleMoves[j+2].y=-i;
    	possibleMoves[j+3].x=-i;
    	possibleMoves[j+3].y=+i;
    	possibleMoves[j+4].x=0;
    	possibleMoves[j+4].y=i;
    	possibleMoves[j+5].x=i;
    	possibleMoves[j+5].y=0;
    	possibleMoves[j+6].x=0;
    	possibleMoves[j+6].y=-i;
    	possibleMoves[j+7].x=-i;
    	possibleMoves[j+7].y=0;
		}
}

Queen::~Queen() {
	// TODO Auto-generated destructor stub
}



