

#include "Piece.h"
#include <iostream>

Piece::Piece(){

}

Piece::~Piece(){
    
}


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


bool Piece::isValid(Move m){
    Delta d=m.getDelta();
    // checks if the Delta of the Move is allowed for this piece
    for (int i=0; i < (int) possibleMoves.size(); i++)
        if (d==possibleMoves[i])
            return true;
    return false;
} // isValid();
