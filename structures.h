/*
 * structures.h
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_


enum player { white, black };


struct Position {
    int x;
    int y;
};

struct Move {
    Position s; // position of the piece moved
    Position d; // destination of the piece moved

};



#endif /* STRUCTURES_H_ */
