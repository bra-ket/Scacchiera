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
	  Delta possible_move;
public:
	Pawn(player p);
	virtual ~Pawn();
    bool isvalid(Move m);
};

#endif /* PAWN_H_ */
