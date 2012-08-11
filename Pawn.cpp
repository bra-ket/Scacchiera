/*
 * Pawn.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Pawn.h"

Pawn::Pawn(player p) {
	type='P';
    pla=p;
}

Pawn::~Pawn() {
	// TODO Auto-generated destructor stub
}

bool Pawn::isvalid(Move m) {
    if (m.d.y-m.s.y==1) return true;
    //prima mossa doppio
    //presa
    else return false;
}