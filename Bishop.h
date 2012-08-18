/*
 * Bishop.h
 *
 *  Created on: 20/lug/2012
 *      Author: massimiliano
 */

#ifndef BISHOP_H_
#define BISHOP_H_

#include "Piece.h"
#include <stdlib.h>

class Bishop: public Piece {
      
public:
	Bishop(player p);
	virtual ~Bishop();
};

#endif /* BISHOP_H_ */
