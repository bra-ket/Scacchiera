/*
 * Box.cpp
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#include "Box.h"

Box::Box() {
    p=0;
}

Box::~Box() {
    if (p!=0) delete p;
}

bool Box::isFree(){
    if (p==0) return true;
    else return false;
}

Piece * Box::getPiece(){
    return p;
}

void Box::putPiece(Piece* q){
    p=q;
}

void Box::empty(){
    p=0;
}