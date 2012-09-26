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

bool Piece::isValid(Move m){
	 Delta d=m.getDelta();
	 for (int i=0; i < (int) possibleMoves.size(); i++)
		 if (d==possibleMoves[i])
			 return true;
	 return false;
} // isValid();


char Piece::getType() {
	return type;
} // getType

player Piece::getPlayer() {
	return pl;
} // getType


void Piece::setMoved(){
	moved=true;
    std::cout<<"IL PEZZO È MOSSO "<<moved<<std::endl;
}

bool Piece::hasMoved(){
	return moved;
}
