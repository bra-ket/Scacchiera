/*
 * ChessBoard.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */


#include "Box.h"
#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	p = white;
    //TODO Generate all the pieces and alloc them
}

ChessBoard::~ChessBoard() {
	// TODO Auto-generated destructor stub
}

void ChessBoard::switchPlayer() {
	p = (p == white ? black : white);
}


/* performs a move on the chessboard
 * return values:
 * - 0: valid move
 * - 1: no piece to move
 * - 2: player tries to move an opponent's piece
 * - 3: player tries to capture an own piece
 * - 4: invalid move due to invalid path
 * - 5: invalid move due to obstructed path
 * - 6: check on the player's move
 */
int ChessBoard::doMove(Move m) {
	Piece * ps = this->getPiece(m.s); // content on the source position
	Piece * pd = this->getPiece(m.d); // content on the destination position

	if (ps == 0)
		return 1; // empty source position

	if (ps->getPlayer() != p)
		return 2; // player tries to move an opponent's piece

	if (pd->getPlayer() == p)
		return 3; // player tries to capture an own piece

	switch (detectSpecial(m)) {
		case 0: // normal move
			if (!ps->isValid())
				return 4; // invalid path
			board[m.d.x][m.d.y]->putPiece(ps); // moves the piece on the destination box
			board[m.s.x][m.s.y]->empty(); // empties the source box
			break;
		case 1: // castling
			castling(m);
			break;
		case 2: // en passant
			enPassant(m);
			break;
	} // switch
} // doMove()

bool ChessBoard::isFree(Position p) {
    return board[p.x][p.y]->isFree();
} // isFree()
