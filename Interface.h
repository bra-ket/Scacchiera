/*
 * Interface.h
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

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
		virtual ~Interface();
		Move prompt();
		void printBoard(); // prints the current state of the chessboard
		void invalidMove(); // prints an invalid move notice
		void validMove(); // prints a valid move notice
		void endGame();
		char getPromotionType();
};

#endif /* INTERFACE_H_ */
