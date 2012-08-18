#include "Move.h"

Move::Move(Position _s, Position _d){
					s.x=_s.x;
					d.x=_d.x;
					s.y=_s.y;
					d.y=_d.y;
					}
Move::Move(int sx, int sy, int dx, int dy){
	s.x=sx;
	s.y=sy;
	d.x=dx;
	d.y=dy;
}
Move::~Move(){}

Delta Move::getdelta(){
	  Delta d;
	  d.x=m.d.x-m.s.x;
	  d.y=m.d.y-m.s.y;
	  return d;
	  
	  }
	  
Position Move::getS{
	return s;
	}
Position Move::getP{
	return p;
	}
