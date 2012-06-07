//
//  struct.h
//  Scacchiera
//
//  Created by Federico D'Ambrosio on 07/06/12.
//  Copyright (c) 2012 Federico D'Ambrosio. All rights reserved.
//

#ifndef Scacchiera_struct_h
#define Scacchiera_struct_h

struct Position {
    int x;
    int y;
};

struct Move {
    Position s; // position of the piece moved
    Position d; // destination of the piece moved
    
};



#endif
