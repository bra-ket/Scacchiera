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
	Position pKingW(1,5);
    Position pKingB(8,5);

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
 * - 9: promotion
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
		movePiece(m); // moves the king
		switch (castling) {
		case -1:
			return 7;
		case 1:
			// white right
			movePiece(1,1,6,1); // moves the white tower to the right
			getPiece(6,1)->setMoved();
			break;
		case 2:
			// white left
			movePiece(1,1,4,1); // moves the white tower to the left
			getPiece(4,1)->setMoved();
			break;
		case 3:
			// black right
			movePiece(1,8,4,8); // moves the black tower to the right
			getPiece(4,8)->setMoved();
			break;
		case 4:
			// black left
			movePiece(8,8,6,8); // moves the black tower to the left
			getPiece(6,8)->setMoved();
			break;
		} // switch
		moveKing(p,m.getD());
		return 0;
	} // if

	// detects and manages an "en passant" capture
	if (ps->getType() == 'P') {
		int enps = detectEnPassant(m);
		if (enps) {
			switch (enps) {
			case -1:
				return 8;
			case 1:
				movePiece(m); // moves the attacker's pawn
				pd = getPiece(m.getS().y, m.getD().x); // stores the captured pawn
				emptyBox(m.getS().y, m.getD().x); // empties the captured position
				if (isCheck(p)) {
					movePiece(m.getD(), m.getS()); // reverts the attacker's move
					putPiece(pd, m.getS().y, m.getD().x); // restore the captured piece
					return 6;
				} // if
				break;
			} // switch
		} // if
	} // if

	else

	{ // normal move
		if (!ps->isValid(m))
			return 4; // invalid path
		// the path is valid
		movePiece(m); // moves the piece
		// checks for a check status
		if (isCheck(p)) {
			movePiece(m.getD(), m.getS()); // reverts the move
			putPiece(pd, m.getS()); // restores the captured piece
			return 6;
		} // if

		if (!ps->hasMoved())
			ps->setMoved();

		resetEnPassant();

		if (ps->getType() == 'P') {
			if (m.getDelta().y == 2)
				((Pawn*)ps)->setEnPassant(); // can be captured "en passant" on the next turn
			else if (m.getD().x == '1' or m.getD().y == '8')
				return 9; // promotion
		} // if

		if (ps->getType() == 'K') {
			moveKing(p,m.getD());
		}
	} // else



    return 0; // normal move executed

} // doMove()


int ChessBoard::detectEnPassant(Move m){
	// sostituire l'if con l'istruzione ? :
    int c = (p == white) ? 1 : -1; // look, how smart!

    if (m.getS().y!=5 and m.getD().y!=5+c)
    	return 0;
    if (abs(m.getS().x-m.getD().x)!=1)
    	return 0;
    if (this->isFree(m.getD().x,5+2*c)==false and this->getPiece(m.getD().x,5+2*c)->getType()=='P') {
    		Pawn * pa = (Pawn *)(this->getPiece(m.getD().x,5+2*c));
    		if (pa->getEnPassant()==true) return 1;
    }

    return -1;
} // detectEnPassant()

void ChessBoard::resetEnPassant(){
    int c;
    if (p==black) c=3;
    if (p==white) c=6;
    for (int i=1;i<=8;i++) {
    	if(!this->isFree(i,c) and this->getPiece(i,c)->getType()=='P') {
    		Pawn * pa = (Pawn *) (this->getPiece(i,c));
    		pa->removeEnPassant();
    	}
    }
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
	// checks for attacks from knights
	if ( isValid(p.x + 1, p.x + 2)
			and !isFree(p.x + 1, p.y + 2)
			and getPiece(p.x + 1, p.y + 2)->getType()=='N'
			and getPiece(p.x + 1, p.y + 2)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x + 1, p.y - 2)
			and !isFree(p.x + 1, p.y - 2)
			and getPiece(p.x + 1, p.y - 2)->getType()=='N'
			and getPiece(p.x + 1, p.y - 2)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x - 1, p.y + 2)
			and !isFree(p.x - 1, p.y + 2)
			and getPiece(p.x - 1, p.y + 2)->getType()=='N'
			and getPiece(p.x - 1, p.y + 2)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x - 1, p.y - 2)
			and !isFree(p.x - 1, p.y - 2)
			and getPiece(p.x - 1, p.y - 2)->getType()=='N'
			and getPiece(p.x - 1, p.y - 2)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x + 2, p.y + 1)
			and !isFree(p.x + 2, p.y + 1)
			and getPiece(p.x + 2, p.y + 1)->getType()=='N'
			and getPiece(p.x + 2, p.y + 1)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x + 2, p.y - 1)
			and !isFree(p.x + 2, p.y - 1)
			and getPiece(p.x + 2, p.y - 1)->getType()=='N'
			and getPiece(p.x + 2, p.y - 1)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x - 2, p.y + 1)
			and !isFree(p.x - 2, p.y + 1)
			and getPiece(p.x - 2, p.y + 1)->getType()=='N'
			and getPiece(p.x - 2, p.y + 1)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x - 2, p.y - 1)
			and !isFree(p.x - 2, p.y - 1)
			and getPiece(p.x - 2, p.y - 1)->getType()=='N'
			and getPiece(p.x - 2, p.y - 1)->getPlayer() == attacker )
		return true;

	// checks from attacks from pawns
	int dY = (attacker == white) ? 1 : -1;
	if ( isValid(p.x + 1, p.y + dY)
			and !isFree(p.x + 1, p.y + dY)
			and getPiece(p.x + 1, p.y + dY)->getType()=='P'
			and getPiece(p.x + 1, p.x - dY)->getPlayer() == attacker )
		return true;
	if ( isValid(p.x - 1, p.y + dY)
			and !isFree(p.x - 1, p.y + dY)
			and getPiece(p.x - 1, p.y + dY)->getType()=='P'
			and getPiece(p.x - 1, p.x - dY)->getPlayer() == attacker )
		return true;

	// checks for attacks from the King
	// this could be included as a special case in the code which checks
	// for attacks from the column, row, and diagonals but it's cleaner
	// to do it in a separate block
	Position q = getKingPosition(attacker);
	if (	   ( abs(p.x - q.x) == 1 and (p.y - q.y) == 1 ) // adjacent on a diagonal
			or ( abs(p.x - q.x) == 1 and (p.y - q.y) == 0 ) // adjacent on the row
			or ( abs(p.x - q.x) == 0 and (p.y - q.y) == 1 ) // adjacent on the column
		) // the attacker's king is on an adjacent cell
		return true;

	// checks for attacks from the column
	for (int i = p.y + 1; i <= 8; i++)
		if ( !isFree(p.x, i)
				and getPiece(p.x, i)->getPlayer() == attacker
				and ( getPiece(p.x, i)->getType() == 'R' or getPiece(p.x, i)->getType() == 'Q' ) )
			return true;
	for (int i = p.y - 1; i >= 1; i--)
		if ( !isFree(p.x, i)
				and getPiece(p.x, i)->getPlayer() == attacker
				and ( getPiece(p.x, i)->getType() == 'R' or getPiece(p.x, i)->getType() == 'Q' ) )
			return true;

	// checks for attacks from the row
	for (int i = p.x + 1; i <= 8; i++)
		if ( !isFree(i, p.y)
				and getPiece(i, p.y)->getPlayer() == attacker
				and ( getPiece(i, p.y)->getType() == 'R' or getPiece(i, p.y)->getType() == 'Q' ) )
			return true;
	for (int i = p.x - 1; i >= 1; i--)
		if ( !isFree(i, p.y)
				and getPiece(i, p.y)->getPlayer() == attacker
				and ( getPiece(i, p.y)->getType() == 'R' or getPiece(i, p.y)->getType() == 'Q' ) )
			return true;

	// checks for attacks from the NE-SW diagonal
	for (int i = 1; i <= min(8 - p.x, 8 - p.y); i++)
		if ( !isFree(p.x + i, p.y + i)
				and getPiece(p.x + i, p.y + i)->getPlayer() == attacker
				and ( getPiece(p.x + i, p.y + i)->getType() == 'B' or getPiece(p.x + i, p.y + i)->getType() == 'Q' ) )
			return true;
	for (int i = 1; i <= min(p.x - 1, p.y - 1); i++)
		if ( !isFree(p.x - i, p.y - i)
				and getPiece(p.x - i, p.y - i)->getPlayer() == attacker
				and ( getPiece(p.x - i, p.y - i)->getType() == 'B' or getPiece(p.x - i, p.y - i)->getType() == 'Q' ) )
			return true;

	// checks for attacks from the NW-SE diagonal
	for (int i = 1; i <= min(p.x - 1, 8 - p.y); i++)
		if ( !isFree(p.x - i, p.y + i)
				and getPiece(p.x - i, p.y + i)->getPlayer() == attacker
				and ( getPiece(p.x - i, p.y + i)->getType() == 'B' or getPiece(p.x - i, p.y + i)->getType() == 'Q' ) )
			return true;
	for (int i = 1; i <= min(8 - p.x, p.y - 1); i++)
		if ( !isFree(p.x + 1, p.y - 1)
				and getPiece(p.x + 1, p.y - 1)->getPlayer() == attacker
				and ( getPiece(p.x + 1, p.y - 1)->getType() == 'B' or getPiece(p.x + 1, p.y - 1)->getType() == 'Q' ) )
			return true;


	return false;


} // isAttacked()

vector<Position> ChessBoard::checkAttackingPositions(Position p, player attacker) {
        vector<Position> positions;

    	if ( isValid(p.x + 1, p.x + 2)
    			and !isFree(p.x + 1, p.y + 2)
    			and getPiece(p.x + 1, p.y + 2)->getType()=='N'
    			and getPiece(p.x + 1, p.y + 2)->getPlayer() == attacker )
			return positions;
    	if ( isValid(p.x + 1, p.y - 2)
    			and !isFree(p.x + 1, p.y - 2)
    			and getPiece(p.x + 1, p.y - 2)->getType()=='N'
    			and getPiece(p.x + 1, p.y - 2)->getPlayer() == attacker )
    		return positions;
    	if ( isValid(p.x - 1, p.y + 2)
    			and !isFree(p.x - 1, p.y + 2)
    			and getPiece(p.x - 1, p.y + 2)->getType()=='N'
    			and getPiece(p.x - 1, p.y + 2)->getPlayer() == attacker )
    		return positions;
    	if ( isValid(p.x - 1, p.y - 2)
    			and !isFree(p.x - 1, p.y - 2)
    			and getPiece(p.x - 1, p.y - 2)->getType()=='N'
    			and getPiece(p.x - 1, p.y - 2)->getPlayer() == attacker )
    		return positions;
    	if ( isValid(p.x + 2, p.y + 1)
    			and !isFree(p.x + 2, p.y + 1)
    			and getPiece(p.x + 2, p.y + 1)->getType()=='N'
    			and getPiece(p.x + 2, p.y + 1)->getPlayer() == attacker )
    		return positions;
    	if ( isValid(p.x + 2, p.y - 1)
    			and !isFree(p.x + 2, p.y - 1)
    			and getPiece(p.x + 2, p.y - 1)->getType()=='N'
    			and getPiece(p.x + 2, p.y - 1)->getPlayer() == attacker )
    		return positions;
    	if ( isValid(p.x - 2, p.y + 1)
    			and !isFree(p.x - 2, p.y + 1)
    			and getPiece(p.x - 2, p.y + 1)->getType()=='N'
    			and getPiece(p.x - 2, p.y + 1)->getPlayer() == attacker )
    		return positions;
    	if ( isValid(p.x - 2, p.y - 1)
    			and !isFree(p.x - 2, p.y - 1)
    			and getPiece(p.x - 2, p.y - 1)->getType()=='N'
    			and getPiece(p.x - 2, p.y - 1)->getPlayer() == attacker )
    		return positions;


        // checks from attacks from pawns
        int dY = (attacker == white) ? 1 : -1;
        if ( isValid(p.x + 1, p.y + dY)
                        and !isFree(p.x + 1, p.y + dY)
                        and getPiece(p.x + 1, p.y + dY)->getType()=='P'
                        and getPiece(p.x + 1, p.x - dY)->getPlayer() == attacker )
        	return positions;
        if ( isValid(p.x - 1, p.y + dY)
                        and !isFree(p.x - 1, p.y + dY)
                        and getPiece(p.x - 1, p.y + dY)->getType()=='P'
                        and getPiece(p.x - 1, p.x - dY)->getPlayer() == attacker )
        	return positions;

        // checks for attacks from the King
        // this could be included as a special case in the code which checks
        // for attacks from the column, row, and diagonals but it's cleaner
        // to do it in a separate block
        Position q = getKingPosition(attacker);
        if (       ( abs(p.x - q.x) == 1 and (p.y - q.y) == 1 ) // adjacent on a diagonal
                        or ( abs(p.x - q.x) == 1 and (p.y - q.y) == 0 ) // adjacent on the row
                        or ( abs(p.x - q.x) == 0 and (p.y - q.y) == 1 ) // adjacent on the column
                ) // the attacker's king is on an adjacent cell
        	return positions;

        // checks for attacks from the column
        for (int i = p.y + 1; i <= 8; i++)
                if ( !isFree(p.x, i)
                                and getPiece(p.x, i)->getPlayer() == attacker
                                and ( getPiece(p.x, i)->getType() == 'R' or getPiece(p.x, i)->getType() == 'Q' ) )
                	return positions;
        for (int i = p.y - 1; i >= 1; i--)
                if ( !isFree(p.x, i)
                                and getPiece(p.x, i)->getPlayer() == attacker
                                and ( getPiece(p.x, i)->getType() == 'R' or getPiece(p.x, i)->getType() == 'Q' ) )
                	return positions;

        // checks for attacks from the row
        for (int i = p.x + 1; i <= 8; i++)
                if ( !isFree(i, p.y)
                                and getPiece(i, p.y)->getPlayer() == attacker
                                and ( getPiece(i, p.y)->getType() == 'R' or getPiece(i, p.y)->getType() == 'Q' ) )
                	return positions;
        for (int i = p.x - 1; i >= 1; i--)
                if ( !isFree(i, p.y)
                                and getPiece(i, p.y)->getPlayer() == attacker
                                and ( getPiece(i, p.y)->getType() == 'R' or getPiece(i, p.y)->getType() == 'Q' ) )
                	return positions;

        // checks for attacks from the NE-SW diagonal
        for (int i = 1; i <= min(8 - p.x, 8 - p.y); i++)
                if ( !isFree(p.x + i, p.y + i)
                                and getPiece(p.x + i, p.y + i)->getPlayer() == attacker
                                and ( getPiece(p.x + i, p.y + i)->getType() == 'B' or getPiece(p.x + i, p.y + i)->getType() == 'Q' ) )
                	return positions;
        for (int i = 1; i <= min(p.x - 1, p.y - 1); i++)
                if ( !isFree(p.x - i, p.y - i)
                                and getPiece(p.x - i, p.y - i)->getPlayer() == attacker
                                and ( getPiece(p.x - i, p.y - i)->getType() == 'B' or getPiece(p.x - i, p.y - i)->getType() == 'Q' ) )
                	return positions;

        // checks for attacks from the NW-SE diagonal
        for (int i = 1; i <= min(p.x - 1, 8 - p.y); i++)
                if ( !isFree(p.x - i, p.y + i)
                                and getPiece(p.x - i, p.y + i)->getPlayer() == attacker
                                and ( getPiece(p.x - i, p.y + i)->getType() == 'B' or getPiece(p.x - i, p.y + i)->getType() == 'Q' ) )
                	return positions;
        for (int i = 1; i <= min(8 - p.x, p.y - 1); i++)
                if ( !isFree(p.x + 1, p.y - 1)
                                and getPiece(p.x + 1, p.y - 1)->getPlayer() == attacker
                                and ( getPiece(p.x + 1, p.y - 1)->getType() == 'B' or getPiece(p.x + 1, p.y - 1)->getType() == 'Q' ) )
                	return positions;


        return positions;


} // checkAttackedPositions()

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

void ChessBoard::movePiece(Move m){
	Position s=m.getS();
	Position d=m.getD();
	this->movePiece(s,d);
}

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
} // emptyBox

void ChessBoard::emptyBox(int x, int y){
	Position p(x,y);
	this->emptyBox(p);
} // emptyBox

bool ChessBoard::isValid(int x, int y) {
	return (x >= 1 and x <= 8 and y >= 1 and y <= 8);
} // isValid

bool ChessBoard::isCheckMate(player attacker) {
	player defender = (attacker == white) ? black : white;

	Position p = this->getKingPosition(defender);

	// checks if the king can move
	if (		( isFree(p.x, p.y + 1)  	and !isAttacked(p.x, p.y + 1, attacker)		) // N
			or	( isFree(p.x + 1, p.y + 1)  and !isAttacked(p.x + 1, p.y + 1, attacker)	) // NE
			or	( isFree(p.x + 1, p.y) 		and !isAttacked(p.x + 1, p.y, attacker)		) // E
			or	( isFree(p.x + 1, p.y - 1)	and !isAttacked(p.x + 1, p.y - 1, attacker)	) // SE
			or	( isFree(p.x, p.y -1)		and !isAttacked(p.x, p.y - 1, attacker)		) // S
			or  ( isFree(p.x - 1, p.y -1)	and !isAttacked(p.x - 1, p.y - 1, attacker)	) // SW
			or  ( isFree(p.x - 1, p.y)		and !isAttacked(p.x - 1, p.y, attacker)		) // W
			or  ( isFree(p.x - 1, p.y + 1)	and !isAttacked(p.x - 1, p.y + 1, attacker)	) // NW
		) // the king can move on at least one adjacent box
			return false;

} // isCheckmate

void ChessBoard::moveKing(player p, Position d){
	if (p == white) pKingW=d;
	if (p == black) pKingB=d;
}

Position ChessBoard::getKingPosition(player p){
	if (p == white) return pKingW;
	if (p == black) return pKingB
}
