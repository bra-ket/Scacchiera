#ifndef MOVE_H
#define MOVE_H_
#include "structures.h"
#include <stdlib.h>

class Move {
	  Position s; // position of the piece moved
      Position d; // destination of the piece moved
public:
	   Move(Position _s, Position _d);
	   Move(int sx, int sy, int dx, int dy);
	   ~Move();
	   Delta getdelta();
	   Position getS;
	   Position getP;
	   
		bool Move::operator==(const Move &other) const {
    		if (this->s.x==other->s.x && this->s.y==other->s.y && this->d.x==other->d.x 
    		&& this->d.y==other->d.y) return true;
    		else false;
      	}
      	bool Move::operator!=(const Move &other) const {
    		return !(*this == other);
  		}
};
#endif
