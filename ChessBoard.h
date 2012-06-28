/*
 * ChessBoard.h
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include "structures.h"
#include "Piece.h"

class ChessBoard {

private:
	 player p;
	 Piece * board[8][8];
	 Piece * kingW;
	 Piece * kingB;

public:
	ChessBoard();
	virtual ~ChessBoard();
	void switchPlayer();
	int doMove(Move m);
	bool isCheckmate();
    bool isFree(Position a);
    Piece * getPiece (Position a);

};

#endif /* CHESSBOARD_H_ */
