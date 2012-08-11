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
}

Queen::~Queen() {
	// TODO Auto-generated destructor stub
}

bool Queen::isvalid(Move m){
    if (m.s.x==m.d.x) return true;
    if (m.s.y==m.d.y) return true;
    if (abs(m.d.x-m.s.x) == abs(m.d.y-m.s.y)) return true;    
    else return false;
}


