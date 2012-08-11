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
}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

bool Knight::isvalid(Move m) {
    if (abs(m.d.x-m.s.x)==2 and abs(m.d.y-m.s.y)==1) return true;
    if (abs(m.d.y-m.s.y)==2 and abs(m.d.x-m.s.x)==1) return true;
    else return false;
}