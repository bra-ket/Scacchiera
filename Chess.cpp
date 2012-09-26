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
    int nplayer;
    if (CB->currentPlayer()==white) nplayer=1;
    if (CB->currentPlayer()==black) nplayer=2;

	do {
		UI->printBoard();
		do {
			Move m = UI->prompt();
            Move abandon(10,10,10,10);
            Move draw(0,0,0,0);
            
            if (m==abandon) {
                UI->endGame(nplayer+2); //abbandono
                break;
            }
            if (m==draw) {
                UI->endGame(0); //patta
                break;
                }
            result = CB->doMove(m); //effettua la mossa, restituisce odice

			switch (result) {
				case 0:
					UI->validMove();
                    player other;
                    if (CB->currentPlayer()==white) other=black;
                    if (CB->currentPlayer()==black) other=white;
                    if(CB->isCheck(other)) UI->isCheck(); //se ha messo sotto scacco il re avversario, avvisa
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
		CB->switchPlayer();
	} while (!checkmate);
    
	UI->endGame(nplayer);
    delete CB;
    delete UI;
	return 0;
} // main
