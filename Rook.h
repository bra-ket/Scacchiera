/*
 * Rook.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef ROOK_H_
#define ROOK_H_

#include <vector>
#include "Piece.h"
#include "Box.h"

class Rook: public Piece {
    
public:
	Rook();
	virtual ~Rook();
    bool isvalid(Move m);
};

#endif /* ROOK_H_ */
