/*
 * UI.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "Interface.h"

Interface::Interface(ChessBoard * board) {
}

Interface::~Interface() {
}

void Interface::printBoard() {
	Position p;
	for (int i=0; i<8; i++) {
		p.y=i; // coordinata verticale della posizione
		for (int j=0; j<8; j++) {
			p.x = j; //coordinata orizzontale della posizione
			if(cb->isFree(p)==true)
				std::cout << 0 << "\t"; // se la casella è vuota printa uno zero
			else {
				if (cb->getPiece(p).getPlayer()==0) std::cout << "W"; // se è il pezzo è bianco
				else std::cout << "B"; // se è il pezzo è nero
				std::cout<<cb->getPiece(p).getType()<<"\t"; // se c'è un pezzo printa il char del tipo di pezzo
			}
		}
		std::cout << std::endl;
	}
}
