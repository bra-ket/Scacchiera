/*
 * Piece.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "Piece.h"
#include <iostream>

Piece::Piece(){

}

Piece::~Piece(){
    
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
}

bool Piece::hasMoved(){
	return moved;
}
