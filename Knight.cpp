/*
 * Knight.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Knight.h"

Knight::Knight(player p) {
    Delta d;
    for (int i=0; i<56; i++) possibleMoves.push_back(d);
	type='N';
    pla=p;
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

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

