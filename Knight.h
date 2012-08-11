/*
 * Knight.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "Piece.h"
#include <stdlib.h>

class Knight: public Piece {
public:
	Knight(player p);
	virtual ~Knight();
    bool isvalid(Move m);
};

#endif /* KNIGHT_H_ */
