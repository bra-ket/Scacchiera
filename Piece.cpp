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
	 Delta d=m.getDelta();
	 for (int i=0; i < (int) possibleMoves.size(); i++)
		 if (d.x==possibleMoves[i].x and d.y==possibleMoves[i].y)
			 return true;
	 return false;
} // isValid();


char Piece::getType() {
	return type;
} // getType

player Piece::getPlayer() {
	return pla;
} // getType


void Piece::setMoved(){
	moved=true;
}

bool Piece::hasMoved(){
	return moved;
}
