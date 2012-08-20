/*
 * Box.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Box.h"

Box::Box() {
    p=NULL;
}

Box::~Box() {
    if (p!=NULL) delete p;
}

bool Box::isFree(){
    if (p==NULL) return true;
    else return false;
}

Piece * Box::getPiece(){
    return p;
}

void Box::putPiece(Piece* q){
    p=q;
}

void Box::empty(){
    p=NULL;
}