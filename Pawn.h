
#ifndef PAWN_H_
#define PAWN_H_

#include "Piece.h"

class Pawn: public Piece {
    bool enPassant; //flag if liable of enpassant

public:
	Pawn(player p);
    bool isValid(Move m); // checks if m is a valid move for the Pawn
    bool getEnPassant(); // returns true if the pawn can be captured en-passant
	void setEnPassant(); // flags the pawn when it can be captured en-passant
    void removeEnPassant(); // removes the flag
};

#endif /* PAWN_H_ */
