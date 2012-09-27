#ifndef BOX_H_
#define BOX_H_

#include "Piece.h"

class Box {

private:
	Piece * p;
    bool free;

public:
	Box();
	virtual ~Box();

	// returns true if the box is free, false otherwise
	bool isFree();

	// returns the content of the box, if any, otherwise returns null
	Piece * getPiece();

	// puts the piece referenced by q in the box
	void putPiece(Piece * q);

	// empties the box (without destroying the content)
	void empty();

}; // Box

#endif /* BOX_H_ */
