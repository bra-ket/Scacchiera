//
//  interface.cc
//  Scacchiera
//
//  Created by Federico D'Ambrosio on 08/06/12.
//  Copyright (c) 2012 Federico D'Ambrosio. All rights reserved.
//

#include <iostream>
#include "interface.h"

void UI::printBoard() {
    Position p;
    for (int i=0; i<8; i++) {
        p.y=i; // coordinata verticale della posizione
        for (j=0; j<8; j++) {
            p.x=j; //coordinata orizzontale della posizione
            if(c->isFree(p)==true) std::cout<<0<<"\t"; // se la casella è vuota printa uno zero
            else {
                if (c->getPiece(p).getPlayer()==0) std::cout<<W; // se è il pezzo è bianco
                else std::cout<<B; // se è il pezzo è nero
                std::cout<<c->getPiece(p).getType()<<"\t"; // se c'è un pezzo printa il char del tipo di pezzo
            }
        }
        std::cout<<endl;
    }
}



