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
	 for (int i=0; i<possibleMoves.size(); i++) if (d.x==possibleMoves[i].x and d.y==possibleMoves[i].y) return true;
	 else false;
	 }
