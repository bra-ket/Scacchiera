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
}

King::~King() {
	// TODO Auto-generated destructor stub
}

bool King::isvalid(Move m){
    if (m.s.x==m.d.x and m.d.y-m.s.y==1) return true;
    if (m.s.y==m.d.y and m.d.x-m.s.x==1) return true;
    if (abs(m.d.x-m.s.x) == abs(m.d.y-m.s.y) == 1) return true;
    else return false;
}

