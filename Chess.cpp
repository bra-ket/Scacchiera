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
	ChessBoard * CB = new ChessBoard();
	Interface * UI = new Interface(CB);
	int result = 0; // result of a move
	bool checkmate = 0; // checkmate status

	do {
		UI->printBoard();
		do {
			Move m = UI->prompt();
			result = CB->doMove(m);

			switch (result) {
				case 0:
					UI->validMove();
					break;
				case 1:
					UI->noPiece();
					break;
                case 2:
                    UI->wrongPlayer();
                    break;
                case 3:
                    UI->selfCapture();
                    break;
                case 4:
                    UI->invalidPath();
                    break;
                case 5:
                    UI->obstructedPath();
                    break;
                case 6:
                    UI->moveCheck();
                    break;
                case 7:
                    UI->castlingNotAllowed();
                    break;
                case 8:
                    UI->enPassantNotAllowed();
                    break;
				case 9:
					char type = UI->getPromotionType();
					if (type!='X') CB->promote(m.getD(), type); //X se non si vuole fare promozione
					result = 0;
					break;
			} // switch
		} while(result);
		checkmate = CB->isCheckMate();
	} while (!checkmate);
	UI->endGame();
	return 0;
} // main
