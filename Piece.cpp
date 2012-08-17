/*
 * Piece.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "Piece.h"

Piece::Piece() {
	// TODO Auto-generated constructor stub

}

Piece::~Piece() {
	// TODO Auto-generated destructor stub
}

bool Piece::isValid(Move m){
	 Delta d=m.getdelta();
	 for (int i=0; i<nmoves; i++) if (d.x==possible_moves[i].x and d.y==possible_moves[i].y) return true;
	 else false;
	 }
