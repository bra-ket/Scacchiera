#include "Move.h"

Move::Move(Position _s, Position _d){
					s.x=_s.x;
					d.x=_d.x;
					s.y=_s.y;
					d.y=_d.y;
					}
					
Move::~Move(){}

Delta Move::getdelta(){
	  Delta d;
	  d.x=m.d.x-m.s.x;
	  d.y=m.d.y-m.s.y;
	  return d;
	  
	  }
