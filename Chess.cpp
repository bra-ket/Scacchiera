//============================================================================
// Name        : Chess.cpp
// Author      : Massimiliano Lincetto, Federico D'Ambrosio
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Interface.h"
#include "ChessBoard.h"

using namespace std;

int main() {
	ChessBoard * cb = new ChessBoard();
	Interface * UI = new Interface(cb);
	int result = 0; // result of a move
	bool checkmate = 0; // checkmate status

	do {
		UI->printBoard();
		do {
			Move m = UI->prompt();
			result = cb->doMove(m);

			switch (result) {
				case 0:
					UI->validMove();
					break;
				case 1:
					UI->invalidMove();
					break;
			} // switch
		} while(result);
		checkmate = cb-> isCheckmate();
	} while (!checkmate);
	UI->endGame();
	return 0;
} // main
