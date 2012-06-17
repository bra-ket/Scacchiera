/*
 * ChessBoard.h
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <structures.h>

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
    void promote(Piece * promotee, char promoteTo);
    void rollBack();
    bool isFree(Position a);
    Piece getPiece (Position a);
    void capture(Piece * attacker, Piece * captured);

};

#endif /* CHESSBOARD_H_ */
