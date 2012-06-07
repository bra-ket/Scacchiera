//
//  chessboard.h
//  Scacchiera
//
//  Created by Federico D'Ambrosio on 07/06/12.
//  Copyright (c) 2012 Federico D'Ambrosio. All rights reserved.
//

#ifndef Scacchiera_chessboard_h
#define Scacchiera_chessboard_h

class Chessboard {
    Piece * board[8][8];
    Piece * kingW;
    Piece * kingB;
    bool player; // white 0, black 1
    void promote(Piece * promotee, char promoteTo);
    void rollBack();
    
public:
    Chessboard();
    bool doMove(Move m);
    bool isFree(Position a);
    Piece getPiece (Position a);
    void capture(Piece * attacker, Piece * captured);

    
}

#endif
