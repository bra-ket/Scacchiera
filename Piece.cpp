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
	 else return false;
	 }

void Piece::promote(Piece * p, char type){
	pla=p->getPlayer();
	delete &p;
	if (type=='B') p=new Bishop(pla);
	if (type=='N') p=new Knight(pla);
	if (type=='R') p=new Rook(pla);
	if (type=='Q') p=new Queen(pla);
	if (type=='P') p=new Pawn(pla);
	p->setMoved();
}
void Piece::setMoved(){
	moved=true;
}

bool Piece::hasMoved(){
	return moved;
}
