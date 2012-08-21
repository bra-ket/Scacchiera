/*
 * ChessBoard.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */


#include "Box.h"
#include "Move.h"
#include "ChessBoard.h"
#include "Pawn.h"
#include "structures.h"

ChessBoard::ChessBoard() {
	p = white;
    //TODO Generate all the pieces and alloc them
}

ChessBoard::~ChessBoard() {
	// TODO Auto-generated destructor stub
}

void ChessBoard::switchPlayer() {
	p = (p == white ? black : white);
} // switchPlayer

bool ChessBoard::isFree(Position p) {
    return board[p.x-1][p.y-1]->isFree();
}

bool ChessBoard::isFree(int x,int y){
	Position a;
	a.x=x;
	a.y=y;
	return (this->isFree(a));
} // isFree()


/* performs a move on the chessboard
 * return values:
 * - 0: valid move
 * - 1: no piece to move
 * - 2: player tries to move an opponent's piece
 * - 3: player tries to capture an own piece
 * - 4: invalid move due to invalid path
 * - 5: invalid move due to obstructed path
 * - 6: check on the player's move
 * - 7: castling not allowed
 * - 8: en passant not allowed
 */
int ChessBoard::doMove(Move m) {
	Piece * ps = this->getPiece(m.getS()); // content on the source position
	Piece * pd = this->getPiece(m.getD()); // content on the destination position
	if (ps == 0)
		return 1; // empty source position
	if (ps->getPlayer() != p)
		return 2; // player tries to move an opponent's piece
	if (pd->getPlayer() == p)
		return 3; // player tries to capture an own piece

	int castling = detectCastling(m);

	if (castling) {
		movePiece(m.getS(),m.getD()); // moves the king
		switch (castling) {
		case -1:
			return 7;
		case 1:
			// white right
			movePiece(1,8,6,1); // moves the white tower to the right
			break;
		case 2:
			// white left
			movePiece(1,1,4,1); // moves the white tower to the left
			break;
		case 3:
			// black right
			movePiece(1,8,4,8); // moves the black tower to the right
			break;
		case 4:
			// black left
			movePiece(8,8,6,8); // moves the black tower to the left
			break;
		} // switch
		return 0;
	} // if
    //aggiungi un if che faccia il check dell'enpassant solo per i pedoni
	int enps = detectEnPassant(m);

	if (enps) {
		switch (enps) {
		case -1:
			return 8;
		case 1:
			// effettuare la mossa
			break;
		} // switch
	} else { // normal move

		if (!ps->isValid(m))
			return 4; // invalid path
		movePiece(m.getS(),m.getD());
	} // else

	if (isCheck(p)) {
		// rollback
		return 6;
	} // if

	// gestione promozione

    //fine turno, svuoto enPassant avversari
    resetEnPassant();
    
} // doMove()

int ChessBoard::detectEnPassant(Move m){
    // if (this->getPiece(m.getS().y-m.getD().y==2) this->getPiece(m.getS())->setEnPassant(); //come evito questo errore? va spostato
    int c;
    if (p==white) c=1;
    else c=-1;
    if (m.getS().y!=5 and m.getD().y!=5+c) return 0;
    if (abs(m.getS().x-m.getD().x)!=1) return 0;
    if (this->isFree(m.getD().x,5+2*c)==false and this->getPiece(m.getD().x,5+2*c)->getType()=='P' and this->getPiece(m.getD().x,5+2*c)->(Pawn*)getEnPassant()==true) return 1; //come faccio ad evitare questo errore?
    else return -1;
}

void ChessBoard::resetEnPassant(){
    int c;
    if (p==black) c=3;
    if (p==white) c=6;
    for (int i=1;i<=8;i++) if(!this->isFree(i,c) and this->getPiece(i,c)->getType()=='P') this->(Pawn*)getPiece(i,c)->removeEnPassant();
}

int ChessBoard::detectCastling(Move m){
	std::vector<Move *> castling(4);
	castling[0]=new Move(5,1,7,1);
	castling[1]=new Move(5,1,3,1);
	castling[2]=new Move(5,8,7,8);
	castling[3]=new Move(5,8,3,8);
	
	int nrook=0;
	for(int i=0; i<castling.size();i++){
		if (*castling[i]==m) {
			nrook=i+1;
			break;
		}
	}
	
	if (nrook==0) return 0; //non un arrocco
	if(this->getPiece(m.getS())->hasMoved()) return -1;
	if (nrook==1) {
		if (this->getPiece(8,1)->hasMoved()) return -1;
		if (this->isAttacked(1,7,black) or this->isAttacked(1,6,black) or this->isAttacked(1,5,black)) return -1;
		if (!this->isFree(1,7) or !this->isFree(1,6)) return -1;
	}
	if (nrook==2) {
		if (this->getPiece(1,1)->hasMoved()) return -1;
		if (this->isAttacked(1,3,black) or this->isAttacked(1,4,black) or this->isAttacked(1,5,black)) return -1;
		if (!this->isFree(1,2) or !this->isFree(1,3) or !this->isFree(1,4)) return -1;
	}
	if (nrook==3) {
		if (this->getPiece(8,8)->hasMoved()) return -1;
		if (this->isAttacked(8,7,white) or this->isAttacked(8,6,white) or this->isAttacked(8,5,white)) return -1;
		if (!this->isFree(8,7) or !this->isFree(8,6)) return -1;
	}
	if (nrook==4) {
		if (this->getPiece(1,8)->hasMoved()) return -1;
		if (this->isAttacked(8,3,white) or this->isAttacked(8,4,white) or this->isAttacked(8,5,white)) return -1;
		if (!this->isFree(8,2) or !this->isFree(8,3) or !this->isFree(8,4)) return -1;
	}
    for (int i=0; i<4; i++) delete castling[i];
    
	return nrook;
}

bool ChessBoard::isAttacked(Position p, player attacker) {
	// check for attacks from knights

} // isAttacked()

bool ChessBoard::isAttacked(int x, int y, player attacker){
    Position p;
    p.x=x;
    p.y=y;
    return(this->isAttacked(p,attacker));
}

void ChessBoard::movePiece(Position s, Position d) {
	putPiece(getPiece(s), d);
	emptyBox(s);
} // movePiece

void ChessBoard::movePiece(int sx,int sy,int dx, int dy) {
	Position s,d;
    s.x=sx;
    s.y=sy;
    d.x=dx;
    d.y=dy;
    this->movePiece(s,d);
} // movePiece

void ChessBoard::putPiece(Piece * pc, Position ps) {
	board[ps.x][ps.y]->putPiece(pc);
} // putPiece()

Piece * ChessBoard::getPiece(int x, int y){
	return (board[x-1][y-1]->getPiece());
}
Piece * ChessBoard::getPiece (Position a){
	int x=a.x;
	int y=a.y;
	return this->getPiece(x,y);
}

void ChessBoard::emptyBox(Position p){
    board[p.x-1][p.y-1]->empty();
}

