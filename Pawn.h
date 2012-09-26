/*
 * Pawn.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef PAWN_H_
#define PAWN_H_

#include "Piece.h"

class Pawn: public Piece {
    bool enPassant; //flag if liable of enpassant

public:
	Pawn(player p);
	virtual ~Pawn();
<<<<<<< HEAD
    virtual bool isValid(Move m);
=======
    bool isValid(Move m);
>>>>>>> CAZZO.
    bool getEnPassant();
	void setEnPassant();
    void removeEnPassant();
};

#endif /* PAWN_H_ */
