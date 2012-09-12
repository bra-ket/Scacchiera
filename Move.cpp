#include "Move.h"

Move::Move(Position ns, Position nd){
    s = ns;
    d = nd;
}
        
					
Move::Move(int sx, int sy, int dx, int dy){
    Position s(sx,sy);
    Position d(dx,dy);
	s.x=sx;
	s.y=sy;
	d.x=dx;
	d.y=dy;
}

Move::~Move(){}

Delta Move::getDelta(){
	  Delta d;
	  d.x=this->d.x-this->s.x;
	  d.y=this->d.y-this->s.y;
	  return d;
	  
	  }
	  
Position Move::getS(){
	return s;
	}

Position Move::getD(){
	return d;
	}
