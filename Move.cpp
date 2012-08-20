#include "Move.h"

Move::Move(Position _s, Position _d){
    s=_s;
    d=_d;
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

Delta Move::getdelta(){
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
