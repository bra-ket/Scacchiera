#include "Interface.h"
#include "ChessBoard.h"

int main() {

	// creating the chessboard
	ChessBoard * CB = new ChessBoard();

	// creating the interface
	Interface * UI = new Interface(CB);



	int outcome = 0; // result of the move
	bool checkmate = 0; // checkmate status
    
    bool endg = false; // is set to true in case of withdrawal or drawn match

	do {
		// printing the ChessBoard
        std::cout<< *CB <<std::endl;
		do {
			Move m = UI->prompt();

			// special moves
            Move withdrawal(10,10,10,10);
            Move draw(0,0,0,0);
            
            if (m == withdrawal) {
            	// withdrawal
                UI->endGame(CB->currentPlayer() + 3);
                endg = true;
                break;
            } // if

            if (m == draw) {
            	// draw match
                UI->endGame(0);
                endg = true;
                break;
			} // if

            // tells the checkboard to perform the move
            outcome = CB->doMove(m);

			switch (outcome) {
				case 0:
					// valid move
					UI->validMove();
                    if(CB->isCheck(CB->oppositePlayer()))
                    	// check status alert
                    	UI->isCheck();
					break;

				case 1:
					// no piece to move on the source position
					UI->noPiece();
					break;

				case 2:
					// player doesn't owen the piece on the source position
                    UI->wrongPlayer();
                    break;

                case 3:
                	// player tries to move onto an own piece
                    UI->selfCapture();
                    break;

                case 4:
                	// the selected piece can't perform that kind of move
                    UI->invalidPath();
                    break;

                case 5:
                	// the path is obstructed
                    UI->obstructedPath();
                    break;

                case 6:
                	// player tries to move into a check situation
                    UI->moveCheck();
                    break;

                case 7:
                	// player tries to do a castling when not allowed
                    UI->castlingNotAllowed();
                    break;

                case 8:
                	// player tries to do an en passant capture when not allowed
                    UI->enPassantNotAllowed();
                    break;

				case 9:
					// player got a pawn promoted
					char type = UI->getPromotionType();
					if (type !='X')
						// the player actually wants to promote the pawn
						CB->promote(m.getD(), type);
					outcome = 0;
					break;
			} // switch()

		} while(outcome); // exits when a correct move has been performed
        
		if (!endg) {
			// player has not withdrawn or chose to draw the match
			// checking for a chekmate situation
            checkmate = CB->isCheckMate();

            // switching the player
            CB->switchPlayer();
        } // if
	} while (!(checkmate or endg));
    
	if (checkmate) UI->endGame(CB->currentPlayer() + 1);

	// deleting objects
    delete CB;
    delete UI;

	return 0;
} // main
