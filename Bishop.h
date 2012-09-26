#ifndef BISHOP_H_
#define BISHOP_H_

#include "Piece.h"
#include <stdlib.h>

class Bishop: public Piece {
public:
	Bishop(player p);
	virtual ~Bishop();
}; // Bishop

#endif /* BISHOP_H_ */
