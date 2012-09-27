#include "Box.h"

Box::Box() {
	// the box is created free
	free = true;
} // Box()

Box::~Box() {
	// if the box is not free, deletes the piece on it
	if (!free)
		delete p;
} // ~Box()

bool Box::isFree() {
	return free;
} // isFree()

Piece* Box::getPiece () {
	if (!free)
		// returns the pointer to the piece
		return p;
	else
		// if the box is free, returns a null pointer
		return 0;

} // getPiece()

void Box::putPiece(Piece* q) {
	// assigns the pointer
	p = q; 
	// set the status
	if (q != NULL)
		free = false;
	else
		// null pointer, the box is still free
		free = true;
} // putPiece()

void Box::empty() {
	// piece is not destroyed
	p = NULL;
	// updating status
	free = true;
} // emtpy();
