#include "Box.h"

Box::Box() {
	free = true; //in the beginning, the box is free
} // Box()

Box::~Box() {
	if (!free) //if it's not free delete the piece on it
		delete p;
} // ~Box()

bool Box::isFree() {
	return free;
} // isFree()

Piece* Box::getPiece () {
	if (!free)
		return p;
	else
		return 0; //if it's free, pointer to null
} // getPiece()

void Box::putPiece(Piece* q) {
	p = q; 
	if (q != NULL)
		free = false;
	else //if it's null pointer, the box is still free
		free = true;
} // putPiece()

void Box::empty() {
	p = NULL; //only change the pointer to null, the piece could be still living on some other boxes
	free = true; //the box is again free
} // emtpy();
