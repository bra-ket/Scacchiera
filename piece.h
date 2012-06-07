//
//  piece.h
//  Scacchiera
//
//  Created by Federico D'Ambrosio on 07/06/12.
//  Copyright (c) 2012 Federico D'Ambrosio. All rights reserved.
//

#ifndef Scacchiera_piece_h
#define Scacchiera_piece_h

class Piece {
    Position p;
    const bool player;
    const char type;
    std::vector <Move> possibleMoves;
    
    
public:
    Piece();
    ~Piece();
    char getType();
    bool move(Position d);
    
};



#endif
