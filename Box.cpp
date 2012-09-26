#include "Box.h"

Box::Box() {
	free = true;
} // Box()

Box::~Box() {
	if (!free)
		delete p;
} // ~Box()

bool Box::isFree() {
	return free;
} // isFree()

Piece* Box::getPiece () {
	if (!free)
		return p;
	else
		return NULL;
} // getPiece()

void Box::putPiece(Piece* q) {
	p = q;
	if (q != NULL)
		free = false;
	else
		free = true;
} // putPiece()

void Box::empty() {
	p = NULL;
	free = true;
} // emtpy();
