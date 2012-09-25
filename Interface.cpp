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

Move Interface::prompt(){ //presumiamo un formato es. "a4b3"
    std::string m;
    std::cout<<"Mossa: ";
    std::cin>>m;
    
    Position in,fin;
    if (isdigit(m[0])) in.x=atoi(&m[0]);
    else in.x=lettertonumber(m[0]); //se usa il formato con le lettere viene convertito in numero: la fila a è la 1 vedi funzione di conversione
    in.y=atoi(&m[1]);

    
    if (isdigit(m[2])) fin.x=atoi(&m[2]);
    else fin.x=lettertonumber(m[2]);
    fin.y=atoi(&m[3]);
    
    Move mossa(in,fin);
    return mossa;
}

char Interface::getPromotionType(){
	bool ok=false;
    char m;
	while (ok==false){
		std::cout<<"Promuovi? B per alfiere, Q per regina, N per cavallo, R per torre, X per non promuovere"<<std::endl;
		std::cin.get(m);
		if (m=='b') m='B';
		if (m=='q') m='Q';
		if (m=='n') m='N';
		if (m=='r') m='R';
		if (m=='x') m='X';
		if (m=='B' or m=='Q' or m=='N' or m=='R' or m=='X') ok=true;
	}
	
	if (m=='B') std::cout<<"Promosso ad alfiere"<<std::endl;
	if (m=='Q') std::cout<<"Promosso a regina"<<std::endl;
	if (m=='N') std::cout<<"Promosso a cavallo"<<std::endl;
	if (m=='R') std::cout<<"Promosso a torre"<<std::endl;
	if (m=='X') std::cout<<"Nessuna promozione"<<std::endl;
	
	return m;
	
}

int lettertonumber(char l) { //converte la lettera nella coordinata
    if (l=='a') return 1;
    if (l=='b') return 2;
    if (l=='c') return 3;
    if (l=='d') return 4;
    if (l=='e') return 5;
    if (l=='f') return 6;
    if (l=='g') return 7;
    if (l=='h') return 8;
}

void Interface::noPiece(){
	std::cout<<"Quella casella è vuota. Riprovare."<<std::endl;
}

void Interface::validMove(){
	std::cout<<"Mossa effettuata con successo"<<std::endl;
}

void Interface::endGame(){
    std::cout<<"Good game"<<std::endl;
}

void Interface::wrongPlayer(){
    std::cout<<"Quel pezzo non è tuo. Riprovare"<<std::endl;
}

void Interface::selfCapture(){
    std::cout<<"Non puoi catturare un pezzo tuo. Riprovare"<<std::endl;
}

void Interface::invalidPath(){
    std::cout<<"Quel pezzo non può muoversi là. Riprovare"<<std::endl;
}

void Interface::obstructedPath(){
    std::cout<<"Il percorso del tuo pezzo è ostruito. Riprovare"<<std::endl;
}

void Interface::moveCheck(){
    std::cout<<"Questa mossa mette il tuo re sotto scacco. Riprovare"<<std::endl;
}

void Interface::castlingNotAllowed(){
    std::cout<<"Questo arrocco non è permesso. Riprovare"<<std::endl;
}

void Interface::enPassantNotAllowed(){
    std::cout<<"Questa mossa in en passant non è permessa. Riprovare."<<std::endl;
}