#include "ChessBoard.h"


using namespace std;

ChessBoard::ChessBoard() {
	cpl = white;
	pKingW = Position(5,1);
	pKingB = Position(5,8);

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++)
			// creating boxes
			board[i][j] = new Box;
	} // for

	// creating pawns
	for (int i=1; i<9; i++) {
		Pawn * pw = new Pawn(white);
		Pawn * pb = new Pawn(black);
		this->putPiece(pw, i,2);
		this->putPiece(pb, i,7);
	} // for

	// creating rooks
	Rook * r1w = new Rook(white);
	this->putPiece(r1w, 1,1);
	Rook * r2w = new Rook(white);
	this->putPiece(r2w, 8,1);

	Rook * r1b = new Rook(black);
	this->putPiece(r1b, 1,8);
	Rook * r2b = new Rook(black);
	this->putPiece(r2b, 8,8);

	// creating knights
	Knight * n1w = new Knight(white);
	this->putPiece(n1w,2,1);
	Knight * n2w = new Knight(white);
	this->putPiece(n2w,7,1);

	Knight * n1b = new Knight(black);
	this->putPiece(n1b,2,8);
	Knight * n2b = new Knight(black);
	this->putPiece(n2b,7,8);

	// creating bishops
	Bishop * b1w = new Bishop(white);
	this->putPiece(b1w,3,1);
	Bishop * b2w = new Bishop(white);
	this->putPiece(b2w,6,1);

	Bishop * b1b = new Bishop(black);
	this->putPiece(b1b,3,8);
	Bishop * b2b = new Bishop(black);
	this->putPiece(b2b,6,8);

	// creating queens
	Queen * qw = new Queen(white);
	this->putPiece(qw, 4,1);

	Queen * qb = new Queen(black);
	this->putPiece(qb, 4,8);

	// creating kings
	King * kw = new King(white);
	this->putPiece(kw,5,1);

	King * kb = new King(black);
	this->putPiece(kb,5,8);



} // ChessBoard

ChessBoard::~ChessBoard() {
	// deleting boxes
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			delete board[i][j];
	} // for

} // ~ChessBoard

void ChessBoard::switchPlayer() {
	cpl = (cpl == white ? black : white);
} // switchPlayer

bool ChessBoard::isFree(Position p) {
	// array indexes are one unit less than each coordinate
	return board[p.x-1][p.y-1]->isFree();
} // isFree

bool ChessBoard::isFree(int x,int y){
	Position a(x,y);
	return (isFree(a));
} // isFree()

int ChessBoard::doMove(Move m) {

    Piece * ps = this->getPiece(m.getS()); // content of the source position

	Piece * pd = this->getPiece(m.getD()); // content of the destination position

	if (isFree(m.getS())) {
		// source position is emtpy
		return 1;
	} // if

	if (ps->getPlayer() != cpl)
		// player tries to move an opponent's piece
		return 2;

	if (!isFree(m.getD())) {
		if (pd->getPlayer() == cpl)
			// player tries to move onto an own piece
			return 3;
	} // if

	// test the Move for castlings
	int castling = detectCastling(m);

	if (castling) {
		// the Move is a castling
		switch (castling) {
		case -1:
			// now allowed
			return 7;
		case 1:
			// white right
			movePiece(m);
			movePiece(8,1,6,1); // moves the white tower to the right
			getPiece(6,1)->setMoved(); // sets the rook as moved
			break;
		case 2:
			// white left
			movePiece(m);
			movePiece(1,1,4,1); // moves the white tower to the left
			getPiece(4,1)->setMoved(); // sets the rook as moved
			break;
		case 3:
			// black right
			movePiece(m);
			movePiece(1,8,4,8); // moves the black tower to the right
			getPiece(4,8)->setMoved(); // sets the rook as moved
			break;
		case 4:
			// black left
			movePiece(m);
			movePiece(8,8,6,8); // moves the black tower to the left
			getPiece(6,8)->setMoved(); // sets the rook as moved
			break;
		} // switch

		// sets the King as moved and updates its position
		getPiece(m.getD())->setMoved();
		moveKing(cpl, m.getD());

		// regular move
		return 0;
	} // if

	// tests for an en-passant capture
	int enps = detectEnPassant(m);

	if (enps) {
		// en-passant capture detected
		switch (enps) {
		case -1:
			// now allowed
			return 8;
		case 1:
			// allowed
			movePiece(m); // moves the attacker's pawn
			pd = getPiece(m.getD().x, m.getS().y); // stores the captured pawn
			emptyBox(m.getD().x, m.getS().y); // empties the captured position
			if (isCheck(cpl)) {
				// check on the player's king, rollbacking the move
				movePiece(m.getD(), m.getS()); // reverting the attacker's move
				putPiece(pd, m.getD().x, m.getS().y); // restoring the captured piece
				return 6;
			} // if
			break;
		} // switch
	} // if

	else

	{ // normal move

		// checking if the path is allowed for the piece
		if (!ps->isValid(m))
			// invalid path
			return 4;

		// checking if the move is allowed for the pawn
		if (ps->getType() == 'P') {
			if (!isFree(m.getD()) and m.getS().x == m.getD().x)
				// the pawn can't capture on forward
				return 4;

			if (isFree(m.getD()) and m.getS().x != m.getD().x)
				// the pawn can't move on diagonal if it's not capturing
				return 4;

			int step = (cpl == white) ? 1 : -1;
			if (m.getDelta().y == 2 and !isFree(m.getS().x, m.getS().y + step))
				// the pawn tries to move of two but the path is blocked
				return 6;
		} // if

		// checking if the path is free
		int dx = m.getDelta().x; // x distance
		int dy = m.getDelta().y; // y distance

		char type = getPiece(m.getS())->getType(); // type of the moving piece

		if ((type == 'Q' or type == 'R' or type == 'B') and (abs(dx) > 1 or abs(dy) > 1)) {
			// (1) only queens, rooks or bishops are subject to obstructed path issues
			// (2) no need to check the path if the destination is an adjacent box

			// we have to scan each box between the source and the destination
			// so we define a step for each coordinate, depending on the path to be scanned
			// if either dx or dy are zero, the corresponding step is set to zero and the coordinate will be kept constant
			int sx = (dx == 0) ? 0 : ((dx > 0) ? 1 : -1);
			int sy = (dy == 0) ? 0 : ((dy > 0) ? 1 : -1);

			// starting with the adjacent box
			int i = sx, j = sy;

			do {
				if (!isFree(m.getS().x + i, m.getS().y + j))
					// found an occupied box
					return 5;
				i += sx;
				j += sy;
				// while moving on the column i == dx == 0 but j != dy
				// while moving on the row j == dy == 0 but x != dx
				// while moving on the diagonal j != dy and x != dx
				// when the destination position is reached i == dx and j == dx, the cycle exits
			} while ((i != dx) or (j != dy));
		} // if

		// the path is valid
		movePiece(m); // moves the piece

		// if the moved piece is a king, updates its position
		if (ps->getType() == 'K')
			moveKing(cpl, m.getD());

		// checks for a check status
		if (isCheck(cpl)) {
			// player's under check, rollbacking the move
			movePiece(m.getD(), m.getS()); // reverts the move
			putPiece(pd, m.getD()); // restores the captured piece
			if (ps->getType() == 'K')
				// restores the previous king position
				moveKing(cpl, m.getS());
			return 6;
		} // if

		// updating moved flag
		if (!ps->hasMoved())
			ps->setMoved();

		// resetting en-passant flags
		resetEnPassant(this->oppositePlayer());
        
		// special cases for the pawn
		if (ps->getType() == 'P') {
			if (abs(m.getDelta().y) == 2) {
				// moved of two
				// en passant capture allowed on the next turn
				((Pawn*)ps)->setEnPassant();
			} // if
            
			if (m.getD().y == 1 or m.getD().y == 8)
				// pawn can be promoted
				return 9;
				
		} // if

	} // else


    delete pd; // deletes the captured piece, if any
	return 0; // regular move

} // doMove()


int ChessBoard::detectEnPassant(Move m) {

	if (getPiece(m.getS())->getType() != 'P')
		// moving piece is not a pawn
		return 0;

	if (!isFree(m.getD()))
		// the pawn is capturing another piece
		return 0;


	if ( m.getS().y != ((cpl == white) ? 5 : 4) and m.getD().y != ((cpl == white) ? 6 : 3))
		// vertical source or destination position not coherent with an en passant capture
		return 0;

	if (abs(m.getDelta().x) != 1)
		// horizontal distance between source and destination is not coherent with a pawn attack
		return 0;

	// possible position of the attacked pawn
	Position takenPiece(m.getD().x, m.getS().y);

	if (this->isFree(takenPiece) == false and this->getPiece(takenPiece)->getType()=='P' and this->getPiece(takenPiece)->getPlayer() != cpl) {
		// the pawn is on the right place for an en-passant capture
		Pawn * pa = (Pawn *)(this->getPiece(m.getD().x,m.getS().y));

		if (pa->getEnPassant() == true)
			// the pawn can actually be taken
			return 1; //taken
	} // if

	return -1;
	//invalid enpassant
} // detectEnPassant()

void ChessBoard::resetEnPassant(player p){
	for (int i = 1; i <= 8;i++){
		for (int j = 1; j <= 8; j++){
			if (!isFree(i,j) and getPiece(i, j)->getType()=='P' and getPiece(i,j)->getPlayer()==p) {
				Pawn * pointer =(Pawn*)getPiece(i,j);
				pointer->removeEnPassant();
			} // if

		} // for
	} // for
} // resetEnPassant

int ChessBoard::detectCastling(Move m){
	std::vector<Move *> castling(4);

	// possible castling moves
	castling[0]=new Move(5,1,7,1);
	castling[1]=new Move(5,1,3,1);
	castling[2]=new Move(5,8,7,8);
	castling[3]=new Move(5,8,3,8);

	int nrook = 0;

	for(int i = 0; i< (int)castling.size(); i++) {
		if (*castling[i]==m) {
			nrook = i+1;
			break;
		} // if
	} // for

	if (nrook == 0)
		// not a castling
		return 0;

	if(this->getPiece(m.getS())->hasMoved())
		// king has moved before
		return -1;

	switch (nrook) {
	case 1:
		if (this->getPiece(8,1)->hasMoved())
			// rook has moved before
			return -1;
		if (this->isAttacked(7,1,black) or this->isAttacked(6,1,black) or this->isAttacked(5,1,black))
			// the king's path is attacked
			return -1;

		if (!this->isFree(7,1) or !this->isFree(6,1))
			// the king's path is obstructed
			return -1;
		break;

	case 2:
		if (this->getPiece(1,1)->hasMoved()) return -1;
		if (this->isAttacked(3,1,black) or this->isAttacked(4,1,black) or this->isAttacked(5,1,black)) return -1;
		if (!this->isFree(2,1) or !this->isFree(3,1) or !this->isFree(4,1)) return -1;
		break;

	case 3:
		if (this->getPiece(8,8)->hasMoved()) return -1;
		if (this->isAttacked(7,8,white) or this->isAttacked(6,8,white) or this->isAttacked(5,8,white)) return -1;
		if (!this->isFree(7,8) or !this->isFree(6,8)) return -1;
		break;

	case 4:
		if (this->getPiece(1,8)->hasMoved()) return -1;
		if (this->isAttacked(3,8,white) or this->isAttacked(4,8,white) or this->isAttacked(5,8,white)) return -1;
		if (!this->isFree(2,8) or !this->isFree(3,8) or !this->isFree(4,8)) return -1;
		break;
	} // switch

	for (int i=0; i<4; i++)
		delete castling[i];

	return nrook;
} // detectEnPassant

bool ChessBoard::isAttacked(Position p, player attacker) {
	vector<Position> atcPos = getAttackingPositions(p, attacker);
	if (atcPos.size() > 0)
		// at least one attack on p by attacker
		return true;
	else
		return false;
} // isAttacked

vector<Position> ChessBoard::getAttackingPositions(Position p, player attacker) {
	vector<Position> positions;

	// checks from attacks from knights
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

	// checks for attacks from the king
	// this could be included as a special case in the code which checks
	// for attacks from the column, row, and diagonals but it's cleaner
	// to do it in a separate block
	Position q = getKingPosition(attacker);
	if (       ( abs(p.x - q.x) == 1 and (p.y - q.y) == 1 ) // adjacent on a diagonal
			or ( abs(p.x - q.x) == 1 and (p.y - q.y) == 0 ) // adjacent on the row
			or ( abs(p.x - q.x) == 0 and (p.y - q.y) == 1 ) // adjacent on the column
	) // the attacker's king is on an adjacent cell
		positions.push_back(q);

	// checks for attacks from rooks or queens on the column
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
	// checks for attacks from rooks or queens on the rank
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

	// checks for attacks from bishops or queens on the NE-SW diagonal
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
	// checks for attacks from bishops or queens on the NW-SE diagonal
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

} // getAttackedPositions()

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
	Position s(sx,sy),d(dx,dy);
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
	if (   (isValid(kp.x, kp.y + 1)
			and (isFree(kp.x, kp.y + 1) or getPiece(kp.x, kp.y + 1)->getPlayer() == attacker)
			and !isAttacked(kp.x, kp.y + 1, attacker)) // N

			or
			(isValid(kp.x + 1, kp.y + 1)
			and (isFree(kp.x + 1, kp.y + 1) or getPiece(kp.x + 1, kp.y + 1)->getPlayer() == attacker)
			and !isAttacked(kp.x + 1, kp.y + 1, attacker)) // NE

			or
			(isValid(kp.x + 1, kp.y)
			and ( isFree(kp.x + 1, kp.y) or getPiece(kp.x + 1, kp.y)->getPlayer() == attacker)
			and !isAttacked(kp.x + 1, kp.y, attacker)) // E

			or
			(isValid(kp.x + 1, kp.y - 1)
			and ( isFree(kp.x + 1, kp.y - 1) or getPiece(kp.x + 1, kp.y - 1)->getPlayer() == attacker)
			and !isAttacked(kp.x + 1, kp.y - 1, attacker)) // SE

			or
			(isValid(kp.x, kp.y -1)
			and ( isFree(kp.x, kp.y - 1) or getPiece(kp.x, kp.y -1)->getPlayer() == attacker)
			and !isAttacked(kp.x, kp.y - 1, attacker)) // S

			or
			(isValid(kp.x - 1, kp.y -1)
			and ( isFree(kp.x - 1, kp.y -1) or getPiece(kp.x - 1, kp.y -1)->getPlayer() == attacker)
			and !isAttacked(kp.x - 1, kp.y - 1, attacker)) // SW

			or
			(isValid(kp.x - 1, kp.y)
			and ( isFree(kp.x - 1, kp.y) or getPiece(kp.x - 1, kp.y)->getPlayer() == attacker)
			and !isAttacked(kp.x - 1, kp.y, attacker)) // W

			or
			(isValid(kp.x - 1, kp.y + 1) and ( isFree(kp.x - 1, kp.y + 1) or getPiece(kp.x - 1, kp.y + 1)->getPlayer() == attacker)
			and !isAttacked(kp.x - 1, kp.y + 1, attacker)) // NW
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
	// the only remaining possibility is that the attacking piece can be captured

	// the case in which the piece can be taken by the king itself is managed in the first if-block

	// the case in which the attacking piece is a pawn that can be captured en passant has to be managed separately
	if (getPiece(ap)->getType() == 'P' and ((Pawn*) getPiece(ap))->getEnPassant()) {
		// the pawn could be taken enPassant
		bool sim_r = false;
		bool sim_l = false;

		Piece* pd = getPiece(ap); // stores the captured pawn
		emptyBox(ap); // empties the captured piece's position
		if (!isFree(ap.x + 1, ap.y) and getPiece(ap.x + 1, ap.y)->getPlayer() == defender and getPiece(ap.x + 1, ap.y)->getType() == 'P')
			// possible capture from the right
			sim_r = simMove(Move(ap.x + 1, ap.y, ap.x, ap.y - ((attacker == white) ? 1 : -1))); // simulates the capture
		if (!isFree(ap.x - 1, ap.y) and getPiece(ap.x - 1, ap.y)->getPlayer() == defender and getPiece(ap.x - 1, ap.y)->getType() == 'P')
			// possible capture from the left
			sim_l = simMove(Move(ap.x - 1, ap.y, ap.x, ap.y - ((attacker == white) ? 1 : -1))); // simulates the capture
		putPiece(pd, ap); // restores the captured piece
		if (sim_r or sim_l)
			// the attacker pawn can be captured en passant
			return false;
	} // if

	vector<Position> ps = getAttackingPositions(ap, defender);

	for (int k = 0; k < (int)ps.size(); k++)
		if (simMove(Move(ps[k], ap)))
			// the attacker can be taken
			return false;

	return true;
} // isCheckmate

bool ChessBoard::isCheckMate(){
	return(isCheckMate(cpl));
}

void ChessBoard::moveKing(player p, Position d){
	if (p == white) pKingW=d;
	if (p == black) pKingB=d;
}

Position ChessBoard::getKingPosition(player p){
	if (p == white) return pKingW;
	else return pKingB;
}

bool ChessBoard::isCheck(player p){
	player attacker = (p == white) ? black : white;


	Position kp = this->getKingPosition(p);

	return (isAttacked(kp,attacker));
} // isCheck()

bool ChessBoard::simMove(Move m){
	Piece * pd = this->getPiece(m.getD());
	movePiece(m); //moves
	bool check=this->isCheck(cpl); //checks
	movePiece(m.getD(), m.getS()); //reverts
	if (pd!=0) putPiece(pd, m.getS()); //restore captured piece, if any
	return check;

}

void ChessBoard::promote(Position pos, char type){
	Piece* piece=NULL;
	if (type=='B') piece = new Bishop (cpl);
	if (type=='N') piece = new Knight (cpl);
	if (type=='Q') piece = new Queen (cpl);
	if (type=='R') piece = new Rook (cpl);
	this->emptyBox(pos);
	this->putPiece(piece,pos);
} // promote

player ChessBoard::currentPlayer() {
	return cpl;
};

player ChessBoard::oppositePlayer() {
	return (cpl == white) ? black : white;
};


	
