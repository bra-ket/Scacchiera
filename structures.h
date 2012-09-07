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
    Position(){}
    Position & operator=(const Position &rhs){
        x=rhs.x;
        y=rhs.y;
        return *this;
    };
    Position (int _x, int _y){
    	x=_x;
    	y=_y;
    }
};

struct Delta {
	   int x;
	   int y;
};


#endif /* STRUCTURES_H_ */
