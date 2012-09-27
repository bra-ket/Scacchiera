

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "ChessBoard.h"
#include <iostream>
#include <vector>
#include "Move.h"


class Interface {
	private:
		ChessBoard * cb;

	public:
		Interface(ChessBoard * board);
		Move prompt();
        void noPiece(); // prints an invalid move notice
        void wrongPlayer();
        void selfCapture();
        void invalidPath();
        void obstructedPath();
        void moveCheck();
        void isCheck(); //at the end of the move we have a check
        void castlingNotAllowed();
        void enPassantNotAllowed();
		void validMove(); // prints a valid move notice
		void endGame(int code);
		char getPromotionType();
};

#endif /* INTERFACE_H_ */
