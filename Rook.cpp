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
}

Rook::~Rook() {
	// TODO Auto-generated destructor stub
}

bool Rook::isvalid(Move m){
    if (m.s.x==m.d.x) return true;
    if (m.s.y==m.d.y) return true;
    else return false;
}
