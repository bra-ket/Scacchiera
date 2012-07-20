/*
 * Box.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef BOX_H_
#define BOX_H_

class Box {
private:
	Piece * p;

public:
	Box();
	virtual ~Box();
	bool isFree();
	Piece * getPiece();
	bool putPiece(Piece* p);
};

#endif /* BOX_H_ */
