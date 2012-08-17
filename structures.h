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

struct Delta {
	   int x;
	   int y;
};



#endif /* STRUCTURES_H_ */
