
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

	// returns owner player
	player getPlayer();

	// returns type ID
	char getType();

	// sets the piece as moved
	virtual void setMoved();

	// returns true if the piece has moved before, false otherwise
	bool hasMoved();

	// virtual to allow late-binding
    virtual bool isValid(Move m);
};

#endif /* PIECE_H_ */
