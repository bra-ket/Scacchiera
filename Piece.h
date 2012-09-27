
#ifndef PIECE_H_
#define PIECE_H_

#include "structures.h"
#include "Move.h"
#include <vector>

class Piece {
    
protected:
    player pl;
    char type;
    bool moved;
    std::vector<Delta> possibleMoves; 
    
    
public:
	Piece();
	virtual ~Piece();
	player getPlayer();
	char getType();

	virtual void setMoved();
	bool hasMoved();

    virtual bool isValid(Move m);
};

#endif /* PIECE_H_ */
