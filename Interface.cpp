/*
 * UI.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "Interface.h"

int lettertonumber(char l);

Interface::Interface(ChessBoard * board) {
    cb=board; //alla fine è l'unica cosa che deve fare
}

Interface::~Interface() {
}

void Interface::printBoard() {
	Position p;
	for (int i=0; i<8; i++) { // coordinata verticale della posizione
		for (int j=0; j<8; j++) { //coordinata orizzontale della posizione
			if (cb->isFree(i,j)==true)
				std::cout << 0 << "\t"; // se la casella è vuota printa uno zero
			else {
				if (cb->getPiece(i,j)->getPlayer()== white) std::cout << "W"; // se è il pezzo è bianco
				else std::cout << "B"; // se è il pezzo è nero
				std::cout<<cb->getPiece(i,j)->getType()<<"\t"; // se c'è un pezzo printa il char del tipo di pezzo
			}
		}
		std::cout << std::endl;
	}
}

Move Interface::prompt(){ //presumiamo un formato es. "a4 b3"
    std::string m;
    std::cout<<"Mossa: ";
    std::cin>>m;
    if (m.length()!=5) throw "string_lenght"; //non ricordo se funzionano così le eccezioni, puoi darci un'occhiata?
    
    Position in,fin;
    if (isdigit(m[0])) in.x=m[0];
    else in.x=lettertonumber(m[0]); //se usa il formato con le lettere viene convertito in numero: la fila a è la 1 vedi funzione di conversione
    in.y=m[1];
    
    if (isdigit(m[3])) fin.x=m[3];
    else fin.x=lettertonumber(m[3]);
    fin.y=m[4];
    
    Move mossa(in,fin);
    return mossa;
}

char Interface::getPromotionType(){
	bool ok=false;
    char m;
	while (ok==false){
		std::cout<<"Promuovi? B per alfiere, Q per regina, N per cavallo, R per torre, X per non promuovere"<<endl;
		std::cin.get(m);
		if (m=='b') m='B';
		if (m=='q') m='Q';
		if (m=='n') m='N';
		if (m=='r') m='R';
		if (m=='x') m='X';
		if (m=='B' or m=='Q' or m=='N' or m=='R' or m=='X') ok=true;
	}
	
	if (m=='B') std::cout<<"Promosso ad alfiere"<<endl;
	if (m=='Q') std::cout<<"Promosso a regina"<<endl;
	if (m=='N') std::cout<<"Promosso a cavallo"<<endl;
	if (m=='R') std::cout<<"Promosso a torre"<<endl;
	if (m=='X') std::cout<<"Nessuna promozione"<<endl;
	
	return m;
	
}

int lettertonumber(char l) { //converte la lettera nella coordinata
    std::string m="abcdefgh";
    int i=1;
    while (l!=m[i]) {
        i++;
    }
    return i;
}

void Interface::invalidMove(){
	std::cout<<"Attenzione, mossa non valida. Riprovare."<<endl;
}

void Interface::validMove(){
	std::cout<<"Mossa effettuata con successo"<<endl;
}

void Interface::endGame(){
    std::cout<<"Good game"<<std::endl;
}
