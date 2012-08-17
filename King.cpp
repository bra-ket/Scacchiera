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
    possible_moves[0].x=1;
    possible_moves[0].y=1;
    possible_moves[1].x=1;
    possible_moves[1].y=0;
	possible_moves[2].x=1;
    possible_moves[2].y=-1;
    possible_moves[3].x=0;
    possible_moves[3].y=-1;
    possible_moves[4].x=-1;
    possible_moves[4].y=-1;
    possible_moves[5].x=-1;
    possible_moves[5].y=0;
    possible_moves[6].x=-1;
    possible_moves[6].y=1;
    possible_moves[7].x=0;
    possible_moves[7].y=1;
 	nmoves=8;
}

King::~King() {
	// TODO Auto-generated destructor stub
}


