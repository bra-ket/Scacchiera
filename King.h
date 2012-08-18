/*
 * King.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef KING_H_
#define KING_H_
#include <vector>

#include "Piece.h"
#include <stdlib.h>

class King: public Piece {
public:
	King(player p);
	virtual ~King();
    bool isvalid(Move m);
};

#endif /* KING_H_ */
