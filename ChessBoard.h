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
#include "Box.h"

class ChessBoard {

private:
	 player p;
	 Box * board[8][8];
	 Piece * kingW;
	 Piece * kingB;

public:
	ChessBoard();
	virtual ~ChessBoard();
	void switchPlayer();

	int doMove(Move m);

	bool isFree(Position a);

    Piece * getPiece (Position a);

    int detectCastling(Move m);
    // controlla se m e` un arrocco e se e` una mossa valida
    // l'arrocco viene comandato spostando il re di due nella direzione in cui si vuole arroccare
    // valori di ritorno:
    // -1: arrocco non permesso
    // 0: la mossa non e` un arrocco
    // 1: arrocco bianco dx
    // 2: arrocco bianco sx
    // 3: arrocco nero dx
    // 4: arrocco nero sx
    // per controllare se e` permesso deve:

    // 1) verificare che la casella di partenza e quella in cui dovrebbe esserci la torre siano occupate
    // 2) verificare che il pezzo sulla casella di partenza e la torre sul lato dell'arrocco non siano mai stati mossi
    // questo garantisce che non possano essere pezzi diversi dal re e dalla torre
    // 2) verificare che le caselle di mezzo siano libere
    // 3) verificare che le caselle di mezzo non siano minacciate (usiamo il metodo isAttacked)

    int detectEnPassant(Move m);
    // controlla se m e` una presa en passant e se e` valida
    // valori di ritorno:
    // -1: presa en passant non permessa
    // 0: non e` una presa en passant
    // 1: e` una presa en passant valida
    // pensa a come implementare il logging delle mosse perche` qui ci serve
    // in linea di massima io farei una classe apposta per la singola entry che contenga la Move e l'eventuale pezzo preso

    bool isAttacked(Position p);
    // me ne occupo io
	bool isCheckmate(player p);
	// me ne occupo io
	bool isCheck(player p);
	// me ne occupo io
};

#endif /* CHESSBOARD_H_ */
