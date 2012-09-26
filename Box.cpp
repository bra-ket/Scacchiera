#include "Box.h"

Box::Box() {
    free = true;
} // Box()

Box::~Box() {
    if (!free) delete p;
}

bool Box::isFree(){
    return free;
}

Piece * Box::getPiece(){
    if (!free) return p;
    else return NULL;
}

void Box::putPiece(Piece* q){
    p=q;
    if (q != NULL)
    	free = false;
    else
    	free = true;
}

void Box::empty(){
    p=NULL;
    free=true;
}
