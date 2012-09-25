/*
 * Pawn.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Pawn.h"

Pawn::Pawn(player p) {
    enPassant=false;
	type='P';
    pla=p;
    Delta d;
    possibleMoves.push_back(d);
    possibleMoves.push_back(d);
    possibleMoves[0].x=0;
    possibleMoves[1].x=0;
    if (pla==white) {
		possibleMoves[0].y=+1;
		possibleMoves[1].y=+2;
    }
    if (pla==black) {
		possibleMoves[0].y=-1;
		possibleMoves[1].y=-2;
    }
}

Pawn::~Pawn() {
	// TODO Auto-generated destructor stub
}

bool Pawn::isvalid(Move m) {
    Delta d=m.getDelta();
    if (d.x==possibleMoves[0].x and d.y==possibleMoves[0].y) return true;
    if (!this->hasMoved() and d.x==possibleMoves[1].x and d.y==possibleMoves[1].y) return true;
    else return false;
}

bool Pawn::getEnPassant(){
    return enPassant;
    
}

void Pawn::setEnPassant(){
    enPassant=true;
}

void Pawn::removeEnPassant(){
    enPassant=false;
}


