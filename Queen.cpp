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
    for (int i=1; i<8; i++) {
		int j=8*(i-1);
		possible_moves[j].x=i;
    	possible_moves[j].y=i;
    	possible_moves[j+1].x=i;
    	possible_moves[j+1].y=-i;
		possible_moves[j+2].x=-i;
    	possible_moves[j+2].y=-i;
    	possible_moves[j+3].x=-i;
    	possible_moves[j+3].y=+i;
    	possible_moves[j+4].x=0;
    	possible_moves[j+4].y=i;
    	possible_moves[j+5].x=i;
    	possible_moves[j+5].y=0;
    	possible_moves[j+6].x=0;
    	possible_moves[j+6].y=-i;
    	possible_moves[j+7].x=-i;
    	possible_moves[j+7].y=0;
		}
	nmoves=56;
}

Queen::~Queen() {
	// TODO Auto-generated destructor stub
}



