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
    possible_move.x=0;
    if (pla==white) possible_move.y=+1;
    if (pla==black) possible_move.y=-1;
}

Pawn::~Pawn() {
	// TODO Auto-generated destructor stub
}

bool Pawn::isvalid(Move m) {
    Delta d=m.getdelta();
    if (d.x==possible_move.x and d.y==possible_move.y) return true;
    //TANTE COSE STRANE
    else return false;
    // fai in modo che autorizzi la mossa di due solo se non si e` mai mosso prima. l'enpassant lo becchiamo separatamente
}
