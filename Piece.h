/*
 * Piece.h
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#ifndef PIECE_H_
#define PIECE_H_

class Piece {
public:
	Piece();
	virtual ~Piece();
	player getPlayer();
	char getType();
};

#endif /* PIECE_H_ */
