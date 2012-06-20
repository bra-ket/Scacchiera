/*
 * ChessBoard.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	p = white;
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
	Piece * ps = this->getPiece(m.s); // piece on the source position
	Piece * pd = this->getPiece(m.d); // piece on the destination position
	if (ps == 0)
		return 1;
	if (ps->getPlayer() != p)
		return 2;
	if (pd->getPlayer() == p)
		return 3;
	int outcome = this->getPiece(m.s)->moveTo(m.d);
	switch (outcome) {
		case 0:
			board[m.d.x][m.d.y] = ps; // moves the piece on the destination position
			board[m.s.x][m.s.y] = 0; // empties the source position
			/* a questo punto abbiamo ancora in memoria il  puntatore al pezzo eventualmente catturato quindi possiamo fare un controllo sullo scacco
			 * ed eventualmente annullare la mossa, senza bisogno di metodi esterni per il capture o il rollback. Serve implementare un metodo
			 * getKing(player) che e` piu` elegante rispetto al fare un if qui dentro per prendere il re bianco o nero a seconda del giocatore
			 */
			return 0;
		case 1:
			return 3;
		case 2:
			return 4;
	} // switch
}
