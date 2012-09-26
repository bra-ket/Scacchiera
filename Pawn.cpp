/*
 * Pawn.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Pawn.h"
#include <iostream>

Pawn::Pawn(player p) {
    enPassant=false;
	type='P';
    pl=p;
    Delta d;
    for (int i=0;i<5;i++) possibleMoves.push_back(d);
    possibleMoves[0].x=0;
    possibleMoves[1].x=0;
    possibleMoves[2].x=1;
    possibleMoves[3].x=-1;
    if (pl==white) {
		possibleMoves[0].y=+1;
		possibleMoves[1].y=+2;
        possibleMoves[2].y=1;
        possibleMoves[3].y=1;
    }
    if (pl==black) {
		possibleMoves[0].y=-1;
		possibleMoves[1].y=-2;
        possibleMoves[2].y=-1;
        possibleMoves[3].y=-1;
    }
}

Pawn::~Pawn() {
	// TODO Auto-generated destructor stub
}

bool Pawn::isValid(Move m) {
    Delta d=m.getDelta();
    if (d==possibleMoves[0] or d==possibleMoves[2] or d==possibleMoves[3]) return true;
    if (!(this->hasMoved()) and d==possibleMoves[1]) return true;
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


