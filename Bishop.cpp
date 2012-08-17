/*
 * Bishop.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Bishop.h"

Bishop::Bishop(player p) {
	type='B';
    pla=p;
}

Bishop::~Bishop() {
	// TODO Auto-generated destructor stub
}


// e` piu` immediato del controllo sull'array, ma visto che il controllo sull'array e` specifica richiesta della consegna io lo adotterei
// anche per questo pezzo
bool Bishop::isvalid(Move m) {
    if (abs(m.d.x-m.s.x) == abs(m.d.y-m.s.y)) return true;
    else return false;
}

