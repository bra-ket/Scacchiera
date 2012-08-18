/*
 * Queen.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef QUEEN_H_
#define QUEEN_H_

#include "Piece.h"
#include <stdlib.h>

class Queen: public Piece {
public:
	Queen(player p);
	virtual ~Queen();
};

#endif /* QUEEN_H_ */
