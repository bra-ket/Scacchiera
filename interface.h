//
//  interface.h
//  Chessboard
//
//  Created by Federico D'Ambrosio on 07/06/12.
//  Copyright (c) 2012 Federico D'Ambrosio. All rights reserved.
//

#ifndef Chessboard_interface_h
#define Chessboard_interface_h

class UI {
    Chessboard * c; // pointer to the chessboard
    void printBoard(); // print the chessboard 
    Move prompt(); // prompt the user for the move and check syntax
    
public:
    Chessboard();
    void turn(); // big
        
}



#endif
