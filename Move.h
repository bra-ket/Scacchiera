#ifndef MOVE_H_
#define MOVE_H_

#include "structures.h"
#include <stdlib.h>

class Move {
	  const Position s; // position of the piece moved
      const Position d; // destination of the piece moved
public:
        Move(Position _s, Position _d);
        Move(int sx, int sy, int dx, int dy);
        ~Move();
        Delta getdelta();
	    Position getS();
	    Position getD();
	   
		bool operator==(Move &other) const{ //workaround
            if (other.getS().x==s.x and other.getS().y==s.y and other.getD().x==d.x and other.getD().y==d.y) return true;
            
    		else return false;
      	}
    
      	bool operator!=(Move &other) const {
    		return !(*this == other);
  		}
};

#endif
