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
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"

using namespace std;

ChessBoard::ChessBoard() {
	p = white;
	pKingW = Position(5,1);
    pKingB = Position(5,8);

    for (int i=0;i<8;i++){
        for (int j=0; j<8; j++){
            board[i][j]= new Box;
        }
    }
    for (int i=1; i<9; i++) {
        Pawn * pw = new Pawn(white);
        Pawn * pb = new Pawn(black);
        this->putPiece(pw, i,2);
        this->putPiece(pb, i,7);
    }
    
    Rook * r1w = new Rook(white);
    this->putPiece(r1w, 1,1);
    Rook * r2w = new Rook(white);
    this->putPiece(r2w, 8,1);
    
    Rook * r1b = new Rook(black);
    this->putPiece(r1b, 1,8);
    Rook * r2b = new Rook(black);
    this->putPiece(r2b, 8,8);
    
    Knight * n1w = new Knight(white);
    this->putPiece(n1w,2,1);
    Knight * n2w = new Knight(white);
    this->putPiece(n2w,7,1);
    
    Knight * n1b = new Knight(black);
    this->putPiece(n1b,2,8);
    Knight * n2b = new Knight(black);
    this->putPiece(n2b,7,8);
    
    Bishop * b1w = new Bishop(white);
    this->putPiece(b1w,3,1);
    Bishop * b2w = new Bishop(white);
    this->putPiece(b2w,6,1);
    
    Bishop * b1b = new Bishop(black);
    this->putPiece(b1b,3,8);
    Bishop * b2b = new Bishop(black);
    this->putPiece(b2b,6,8);
    
    Queen * qw = new Queen(white);
    this->putPiece(qw, 4,1);
    
    Queen * qb = new Queen(black);
    this->putPiece(qb, 4,8);
    
    King * kw = new King(white);
    this->putPiece(kw,5,1);
    
    King * kb = new King(black);
    this->putPiece(kb,5,8);
    
    
    //TODO Generate all the pieces and alloc them
}

ChessBoard::~ChessBoard() {
	for (int i=0; i<8; i++) {
        for (int j=0;j<8;j++){
            delete board[i][j];
        }
    }
   
}

void ChessBoard::switchPlayer() {
	p = (p == white ? black : white);
} // switchPlayer

bool ChessBoard::isFree(Position p) {
    return board[p.x-1][p.y-1]->isFree();
}

bool ChessBoard::isFree(int x,int y){
	Position a(x,y);
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

	cout << "entered doMove" << endl;

	cout << "getting piece on source:" << m.getS().x << " " << m.getS().y << endl;

	Piece * ps = this->getPiece(m.getS()); // content on the source position

	cout << "got piece on source " << ps << endl;

	cout << "getting piece on destination:" << m.getD().x << " " << m.getD().y << endl;

	Piece * pd = this->getPiece(m.getD()); // content on the destination position

	cout << "got piece on destination " << pd << endl;

	if (isFree(m.getS())) {
		cout << "doMove returning 1" << endl;
		return 1; // empty source position
	}

	cout << "source not free" << endl;

	if (ps->getPlayer() != p)
		return 2; // player tries to move an opponent's piece

	cout << "player is moving an own piece" << endl;

	if (!isFree(m.getD())) {
		cout << "destination not free" << endl;
		if (pd->getPlayer() == p)
				return 3; // player tries to capture an own piece
	} // if

	cout << "player is not trying to capture an own piece" << endl;

	int castling = detectCastling(m);

	cout << "detected castling?" << endl;

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

	else

	{ // normal move

		cout << "normal move" << endl;
		if (!ps->isValid(m))
			return 4; // invalid path

		if (ps->getType() == 'P') {
			if (!isFree(m.getD()) and m.getS().x == m.getD().x)
				// the pawn can't capture on forward
				return 4;
			if (isFree(m.getD()) and m.getS().x != m.getD().x)
				// the pawn can't move on diagonal if it's not capturing
				return 4;
		} // if


		if (ps->getType() == 'K' and isAttacked(m.getD(), oppositePlayer()))
			// the king can't capture a defended piece
			return 6;

		// checking for obstructed path

        int dx = m.getD().x - m.getS().x; // x distance
        int dy = m.getD().y - m.getS().y; // y distance
        char type = getPiece(m.getS())->getType();

		if ((type == 'Q' or type == 'R' or type == 'B') and (abs(dx) > 1 or abs(dy) > 1)) {
			cout << "checking for obstructed path" << endl;
			// (1) only queens, rooks or bishops are subject to obstructed path issues
			// (2) no need to check if the destination is an adjacent box

		    // we have to scan each box between the source and the destination
		    // so we define a step for each coordinate, depending on the path to be scanned
			// if either dx or dy are zero, the corresponding step is set to zero and the coordinate will be kept constant
			int sx = (dx == 0) ? 0 : ((dx > 0) ? 1 : -1);
			int sy = (dy == 0) ? 0 : ((dy > 0) ? 1 : -1);

			int i = sx, j = sy;

			do {
				if (!isFree(m.getS().x + i, m.getS().y + j))
						return 5;
				i += sx;
				j += sy;
				// while moving on the column i == dx == 0 but j != dy
				// while moving on the row j == dy == 0 but x != dx
				// while moving on the diagonal j != dy and x != dx
				// when the attacking piece's position is reached i == dx and j == dx, the cycle exits
			} while ((i != dx) or (j != dy));
		} // if

		// the path is valid
		cout << "moving piece" << endl;
		movePiece(m); // moves the piece
		cout << "piece moved" << endl;

		// checks for a check status
		if (isCheck(p)) {
			cout << "check!" << endl;
			movePiece(m.getD(), m.getS()); // reverts the move
			putPiece(pd, m.getD()); // restores the captured piece
			return 6;
		} // if

		cout << "checked for checks" << endl;

		if (!ps->hasMoved())
			ps->setMoved();
		cout << "set moved" << endl;
		resetEnPassant();
		cout << "reset enps" << endl;
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
    for (int i = 1; i < 9; i++) {
    	if(!this->isFree(i,c) and this->getPiece(i,c)->getType()=='P') {
    		Pawn * pa = (Pawn *) (this->getPiece(i,c));
    		pa->removeEnPassant();
    	}
    }
}

int ChessBoard::detectCastling(Move m){
	cout << "detecting castling" << endl;
	std::vector<Move *> castling(4);
	castling[0]=new Move(5,1,7,1);
	castling[1]=new Move(5,1,3,1);
	castling[2]=new Move(5,8,7,8);
	castling[3]=new Move(5,8,3,8);
	
	int nrook=0;

	cout << m.getS().x << " " << m.getS().y << " " << m.getD().x << " " << m.getD().y << endl;

	for(int i=0; i< (int)castling.size();i++){
		cout << (*castling[i]).getS().x << " " << (*castling[i]).getS().y << " " << (*castling[i]).getD().x << " " << (*castling[i]).getD().y << endl;
		if (*castling[i]==m) {
			cout << "castling move!" << endl;
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
    vector<Position> atcPos = getAttackingPositions(p, attacker);
    if (atcPos.size() > 0)
        return true;
    else
        return false;
} // isAttacked

vector<Position> ChessBoard::getAttackingPositions(Position p, player attacker) {
        vector<Position> positions;

    	if ( isValid(p.x + 1, p.x + 2)
    			and !isFree(p.x + 1, p.y + 2)
    			and getPiece(p.x + 1, p.y + 2)->getType()=='N'
    			and getPiece(p.x + 1, p.y + 2)->getPlayer() == attacker )
			positions.push_back(Position(p.x + 1, p.x + 2));
    	if ( isValid(p.x + 1, p.y - 2)
    			and !isFree(p.x + 1, p.y - 2)
    			and getPiece(p.x + 1, p.y - 2)->getType()=='N'
    			and getPiece(p.x + 1, p.y - 2)->getPlayer() == attacker )
    		positions.push_back(Position(p.x + 1, p.y - 2));
    	if ( isValid(p.x - 1, p.y + 2)
    			and !isFree(p.x - 1, p.y + 2)
    			and getPiece(p.x - 1, p.y + 2)->getType()=='N'
    			and getPiece(p.x - 1, p.y + 2)->getPlayer() == attacker )
    		positions.push_back(Position(p.x - 1, p.y + 2));
    	if ( isValid(p.x - 1, p.y - 2)
    			and !isFree(p.x - 1, p.y - 2)
    			and getPiece(p.x - 1, p.y - 2)->getType()=='N'
    			and getPiece(p.x - 1, p.y - 2)->getPlayer() == attacker )
    		positions.push_back(Position(p.x - 1, p.y - 2));
    	if ( isValid(p.x + 2, p.y + 1)
    			and !isFree(p.x + 2, p.y + 1)
    			and getPiece(p.x + 2, p.y + 1)->getType()=='N'
    			and getPiece(p.x + 2, p.y + 1)->getPlayer() == attacker )
    		positions.push_back(Position(p.x + 2, p.y + 1));
    	if ( isValid(p.x + 2, p.y - 1)
    			and !isFree(p.x + 2, p.y - 1)
    			and getPiece(p.x + 2, p.y - 1)->getType()=='N'
    			and getPiece(p.x + 2, p.y - 1)->getPlayer() == attacker )
    		positions.push_back(Position(p.x + 2, p.y - 1));
    	if ( isValid(p.x - 2, p.y + 1)
    			and !isFree(p.x - 2, p.y + 1)
    			and getPiece(p.x - 2, p.y + 1)->getType()=='N'
    			and getPiece(p.x - 2, p.y + 1)->getPlayer() == attacker )
    		positions.push_back(Position(p.x - 2, p.y + 1));
    	if ( isValid(p.x - 2, p.y - 1)
    			and !isFree(p.x - 2, p.y - 1)
    			and getPiece(p.x - 2, p.y - 1)->getType()=='N'
    			and getPiece(p.x - 2, p.y - 1)->getPlayer() == attacker )
    		positions.push_back(Position(p.x - 2, p.y - 1));


        // checks from attacks from pawns
        int dY = (attacker == white) ? 1 : -1;
        if ( isValid(p.x + 1, p.y + dY)
                        and !isFree(p.x + 1, p.y + dY)
                        and getPiece(p.x + 1, p.y + dY)->getType()=='P'
                        and getPiece(p.x + 1, p.x - dY)->getPlayer() == attacker )
        	positions.push_back(Position(p.x + 1, p.y + dY));
        if ( isValid(p.x - 1, p.y + dY)
                        and !isFree(p.x - 1, p.y + dY)
                        and getPiece(p.x - 1, p.y + dY)->getType()=='P'
                        and getPiece(p.x - 1, p.x - dY)->getPlayer() == attacker )
        	positions.push_back(Position(p.x - 1, p.y + dY));

        // checks for attacks from the King
        // this could be included as a special case in the code which checks
        // for attacks from the column, row, and diagonals but it's cleaner
        // to do it in a separate block
        Position q = getKingPosition(attacker);
        if (       ( abs(p.x - q.x) == 1 and (p.y - q.y) == 1 ) // adjacent on a diagonal
                        or ( abs(p.x - q.x) == 1 and (p.y - q.y) == 0 ) // adjacent on the row
                        or ( abs(p.x - q.x) == 0 and (p.y - q.y) == 1 ) // adjacent on the column
                ) // the attacker's king is on an adjacent cell
        	positions.push_back(q);

        // checks for attacks from the column
        for (int i = p.y + 1; i <= 8; i++)
                if ( !isFree(p.x, i) ) {
                	if (getPiece(p.x, i)->getPlayer() == attacker and (getPiece(p.x, i)->getType() == 'R' or getPiece(p.x, i)->getType() == 'Q' ))
                		positions.push_back(Position(p.x, i));
                	break;
                } // if
        for (int i = p.y - 1; i >= 1; i--)
                if ( !isFree(p.x, i)) {
                	if (getPiece(p.x, i)->getPlayer() == attacker and ( getPiece(p.x, i)->getType() == 'R' or getPiece(p.x, i)->getType() == 'Q' ))
                		positions.push_back(Position(p.x, i));
                	break;
                } // if
        // checks for attacks from the row
        for (int i = p.x + 1; i <= 8; i++)
                if ( !isFree(i, p.y)) {
                	if ( getPiece(i, p.y)->getPlayer() == attacker and ( getPiece(i, p.y)->getType() == 'R' or getPiece(i, p.y)->getType() == 'Q' ))
                		positions.push_back(Position(i, p.y));
                	break;
                } // if
        for (int i = p.x - 1; i >= 1; i--)
                if ( !isFree(i, p.y)) {
                	if (getPiece(i, p.y)->getPlayer() == attacker and ( getPiece(i, p.y)->getType() == 'R' or getPiece(i, p.y)->getType() == 'Q' ) )
                		positions.push_back(Position(i, p.y));
					break;
                } // if

        // checks for attacks from the NE-SW diagonal
        for (int i = 1; i <= min(8 - p.x, 8 - p.y); i++)
                if ( !isFree(p.x + i, p.y + i)) {
                	if (getPiece(p.x + i, p.y + i)->getPlayer() == attacker and ( getPiece(p.x + i, p.y + i)->getType() == 'B' or getPiece(p.x + i, p.y + i)->getType() == 'Q' ) )
                		positions.push_back(Position(p.x + i, p.y + i));
                	break;
                } // if
        for (int i = 1; i <= min(p.x - 1, p.y - 1); i++)
                if ( !isFree(p.x - i, p.y - i)) {
                	if (getPiece(p.x - i, p.y - i)->getPlayer() == attacker and ( getPiece(p.x - i, p.y - i)->getType() == 'B' or getPiece(p.x - i, p.y - i)->getType() == 'Q' ) )
                		positions.push_back(Position(p.x - i, p.y - 1));
                	break;
                } // if
        // checks for attacks from the NW-SE diagonal
        for (int i = 1; i <= min(p.x - 1, 8 - p.y); i++)
                if ( !isFree(p.x - i, p.y + i)) {
                	if (getPiece(p.x - i, p.y + i)->getPlayer() == attacker and ( getPiece(p.x - i, p.y + i)->getType() == 'B' or getPiece(p.x - i, p.y + i)->getType() == 'Q' ) )
                		positions.push_back(Position(p.x - i, p.y + i));
                	break;
                } // if
        for (int i = 1; i <= min(8 - p.x, p.y - 1); i++)
                if ( !isFree(p.x + 1, p.y - 1)) {
                	if (getPiece(p.x + 1, p.y - 1)->getPlayer() == attacker and ( getPiece(p.x + 1, p.y - 1)->getType() == 'B' or getPiece(p.x + 1, p.y - 1)->getType() == 'Q' ) )
                		positions.push_back(Position(p.x + 1, p.y - 1));
                	break;
                } // if

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
	board[ps.x-1][ps.y-1]->putPiece(pc);
} // putPiece()

void ChessBoard::putPiece(Piece * pc, int x, int y){
    Position p(x,y);
    this->putPiece(pc, p);
}

Piece * ChessBoard::getPiece(int x, int y) {
    Position p(x,y);
	return (this->getPiece(p));
} // getPiece

Piece * ChessBoard::getPiece (Position a) {
    if (!board[a.x-1][a.y-1]->isFree())
		return (board[a.x-1][a.y-1]->getPiece());
	else return NULL;
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

        Position kp = this->getKingPosition(defender);

        // checks if the king is attacked
        if (!isAttacked(kp, attacker))
                // the king is not under attack
                return false;
        // isvalid!
        // checks if the king can move
        if (            ( isValid(kp.x, kp.y + 1)       and ( isFree(kp.x, kp.y + 1)            or getPiece(kp.x, kp.y + 1)->getPlayer() == attacker            )       and !isAttacked(kp.x, kp.y + 1, attacker)       ) // N
                        or      ( isValid(kp.x + 1, kp.y + 1) and ( isFree(kp.x + 1, kp.y + 1)  or getPiece(kp.x + 1, kp.y + 1)->getPlayer() == attacker        )       and !isAttacked(kp.x + 1, kp.y + 1, attacker)   ) // NE
                        or      ( isValid(kp.x + 1, kp.y)       and ( isFree(kp.x + 1, kp.y)            or getPiece(kp.x + 1, kp.y)->getPlayer() == attacker            )       and !isAttacked(kp.x + 1, kp.y, attacker)               ) // E
                        or      ( isValid(kp.x + 1, kp.y - 1) and ( isFree(kp.x + 1, kp.y - 1)  or getPiece(kp.x + 1, kp.y - 1)->getPlayer() == attacker        )       and !isAttacked(kp.x + 1, kp.y - 1, attacker)   ) // SE
                        or      ( isValid(kp.x, kp.y -1)                and ( isFree(kp.x, kp.y - 1)            or getPiece(kp.x, kp.y -1)->getPlayer() == attacker             )       and !isAttacked(kp.x, kp.y - 1, attacker)               ) // S
                        or  ( isValid(kp.x - 1, kp.y -1)        and ( isFree(kp.x - 1, kp.y -1) or getPiece(kp.x - 1, kp.y -1)->getPlayer() == attacker )       and !isAttacked(kp.x - 1, kp.y - 1, attacker)   ) // SW
                        or  ( isValid(kp.x - 1, kp.y)   and ( isFree(kp.x - 1, kp.y)            or getPiece(kp.x - 1, kp.y)->getPlayer() == attacker            )       and !isAttacked(kp.x - 1, kp.y, attacker)               ) // W
                        or  ( isValid(kp.x - 1, kp.y + 1)       and ( isFree(kp.x - 1, kp.y + 1)        or getPiece(kp.x - 1, kp.y + 1)->getPlayer() == attacker        )       and !isAttacked(kp.x - 1, kp.y + 1, attacker)   ) // NW
                )
                        // the king can move on at least one adjacent box
                        return false;

        vector<Position> atcPos = getAttackingPositions(kp, attacker);

        if (atcPos.size() > 1)
                // multiple attack, since the king can't move this is a checkmate situation
                return true;

        // single attack, may not be a checkmate situation
        Position ap = atcPos[0];
        int dx = ap.x - kp.x; // x distance
        int dy = ap.y - kp.y; // y distance

        if ((getPiece(ap)->getType() != 'N') and (abs(dx) > 1 or abs(dy) > 1)) {
                // the attack may be shielded if
                // (1) the attacker is not a knight
                // (2) there is at least one space between the attacker and the king


                // we have to scan each box between the attacker and the king
                // so we define a step for each coordinate, depending on the path to be scanned
                // if either dx or dy are zero, the corresponding step is set to zero and the coordinate will be kept constant
                int sx = (dx == 0) ? 0 : ((dx > 0) ? 1 : -1);
                int sy = (dy == 0) ? 0 : ((dy > 0) ? 1 : -1);

                int i = sx, j = sy;

                do {
                    if (isAttacked(ap.x + i, ap.y + j, defender)) {
                        // the position is reachable from at least one defender's piece, but it may be pinned
                        vector<Position> ps = getAttackingPositions(Position(ap.x + i, ap.y + j), defender);
                        for (int k = 0; k < (int)ps.size(); k++)
                            if (simMove(Move(ps[k], Position(ap.x + i, ap.y + j))))
                                // the attack can be shielded
                                return false;
                    } // if

                    i += sx;
                    j += sy;

                // while moving on the column i == dx == 0 but j != dy
                // while moving on the row j == dy == 0 but x != dx
                // while moving on the diagonal j != dy and x != dx
                // when the attacking piece's position is reached i == dx and j == dx, the cycle exits
                } while ((i != dx) or (j != dy));
        } // if

        // the attack can't be shielded
        // the only remaining possibility is that the attacking piece can be taken
        // the case in which the piece can be taken by the king itself is managed in the first if-block
        vector<Position> ps = getAttackingPositions(Position(ap), defender);
        for (int k = 0; k < (int)ps.size(); k++)
            if (simMove(Move(ps[k], ap)))
            	// the attacker can be taken
                return false;

        return true;
} // isCheckmate

bool ChessBoard::isCheckMate(){
    return(isCheckMate(p));
}

void ChessBoard::moveKing(player p, Position d){
	if (p == white) pKingW=d;
	if (p == black) pKingB=d;
}

Position ChessBoard::getKingPosition(player p){
	cout << "entered getkingposition" << endl;
	cout << pKingW.x << " " << pKingW.y << endl;
	cout << pKingB.x << " " << pKingB.y << endl;
	if (p == white) return pKingW;
	else return pKingB;
}

bool ChessBoard::isCheck(player p){
    player attacker = (p == white) ? black : white;
	
	cout << "checking for check" << endl;

	Position kp = this->getKingPosition(p);

	cout << "got king position " << kp.x << " " << kp.y <<  endl;

	return (isAttacked(kp,attacker));
} // isCheck()

bool ChessBoard::simMove(Move m){
    Piece * pd = this->getPiece(m.getD());
    movePiece(m); //moves
    bool check=this->isCheck(p); //checks
    movePiece(m.getD(), m.getS()); //reverts
    if (pd!=0) putPiece(pd, m.getS()); //restores eventual taken piece
    return check;
	
}

void ChessBoard::promote(Position p, char type){ //condition already checked
    Piece* piece=NULL;
	if (type=='B') piece = new Bishop (this->p);
	if (type=='N') piece = new Knight (this->p);
	if (type=='Q') piece = new Queen (this->p);
	if (type=='R') piece = new Rook (this->p);
	this->emptyBox(p);
	this->putPiece(piece,p);
} // promote

player ChessBoard::currentPlayer() {
	return p;
};
	
player ChessBoard::oppositePlayer() {
	return (p == white) ? black : white;
};

	
	
