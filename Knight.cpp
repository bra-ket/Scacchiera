/*
 * Knight.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Knight.h"

Knight::Knight(player p) {
	type='N';
    pla=p;
    for (int i=1; i<8; i++) {
		possible_moves[4*i].x=i;
    	possible_moves[4*i].y=i;
    	possible_moves[4*i+1].x=i;
    	possible_moves[4*i+1].y=-i;
		possible_moves[4*i+2].x=-i;
    	possible_moves[4*i+2].y=-i;
    	possible_moves[4*i+3].x=-i;
    	possible_moves[4*i+3].y=+i;
		}
	nmoves=32; // come fanno a essere 32? ne ha solo 8 a disposizione! c'e` qualcosa di sbagliato
}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

