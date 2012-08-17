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
      std::vector<Move> possible_moves;
      
public:
	Bishop(player p);
	virtual ~Bishop();
    bool isvalid(Move m);
};

#endif /* BISHOP_H_ */
