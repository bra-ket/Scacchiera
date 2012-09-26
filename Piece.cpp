/*
 * Piece.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "Piece.h"
#include <iostream>

Piece::Piece() {
	// TODO Auto-generated constructor stub

}

Piece::~Piece() {
	// TODO Auto-generated destructor stub
}

virtual bool Piece::isValid(Move m){
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
    std::cout<<"IL PEZZO È MOSSO "<<moved<<std::endl;
}

bool Piece::hasMoved(){
	return moved;
}
