#ifndef MOVE_H
#define MOVE_H_
#include "structures.h"

class Move {
	  Position s; // position of the piece moved
      Position d; // destination of the piece moved
public:
	   Move(Position _s, Position _d);
	   ~Move();
	   Delta getdelta();
};
#endif
