/*
 * Piece.h
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#ifndef PIECE_H_
#define PIECE_H_

#include "structures.h"

class Piece {
    
protected:
    player pla;
    char type;
    bool hasMoved;
    
public:
	Piece();
	virtual ~Piece();
	player getPlayer();
	char getType();

	void setMoved();
	bool hasMoved();

    virtual bool isValid(Move m);
};

#endif /* PIECE_H_ */
