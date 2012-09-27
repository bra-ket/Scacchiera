/*
 * UI.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */

#include "Interface.h"

int lettertonumber(char l);

Interface::Interface(ChessBoard * board) {
    cb=board; 
}

Interface::~Interface(){
    
}


Move Interface::prompt(){ //presumiamo un formato es. "a4b3"
    std::string m;
    bool check=false;
    while (!check) {
        m.clear();
        std::cout<<std::endl<<"Giocatore ";
        if (cb->currentPlayer()==white) std::cout<<"BIANCO";
        if (cb->currentPlayer()==black) std::cout<<"NERO";
        std::cout<<". Mossa: ";
        std::cin>>m;
        
        if (m.compare("XXXX")==0) {
            Move abandon(10,10,10,10); //fake move just to notify of abandon 
            return abandon;
        }//abandon
        
        if (m.compare("0000")==0) {
            Move draw(0,0,0,0); //fake move just to notify of draw 
            return draw;
        }//draw
        
        check=true;
        if (m.size()!=4) check=false; //string lenght
        
        else if (m[0]!='a' and m[0]!='b' and m[0]!='c' and m[0]!='d' and m[0]!='e' and m[0]!='f' and m[0]!='g' and m[0]!='h') check=false;
        else if (atoi(&m[1])>8 or atoi(&m[1])<1) check=false;
        else if (m[2]!='a' and m[2]!='b' and m[2]!='c' and m[2]!='d' and m[2]!='e' and m[2]!='f' and m[2]!='g' and m[2]!='h') check=false;
        else if (atoi(&m[3])>8 or atoi(&m[3])<1) check=false;
        //check if string is valid 
        
        if (check==false) std::cout<<"Mossa in formato non valido (es. a2a4). Riprovare."<<std::endl;
        //if it's not ok, redo

    }
        
        
    Position in,fin;
    in.x=lettertonumber(m[0]);
    in.y=atoi(&m[1]);
    fin.x=lettertonumber(m[2]);
    fin.y=atoi(&m[3]);
    
    Move mossa(in,fin);
    return mossa;
}

char Interface::getPromotionType(){
	bool ok=false;
    char m;
	do {
		std::cout<<"Promuovi? B per alfiere, Q per regina, N per cavallo, R per torre, X per non promuovere";
		std::cin.get(m);
		if (m=='b') m='B';
		if (m=='q') m='Q';
		if (m=='n') m='N';
		if (m=='r') m='R';
		if (m=='x') m='X';
		if (m=='B' or m=='Q' or m=='N' or m=='R' or m=='X') ok=true;
	}while (!ok);
	
	if (m=='B') std::cout<<"Promosso ad alfiere"<<std::endl;
	if (m=='Q') std::cout<<"Promosso a regina"<<std::endl;
	if (m=='N') std::cout<<"Promosso a cavallo"<<std::endl;
	if (m=='R') std::cout<<"Promosso a torre"<<std::endl;
	if (m=='X') std::cout<<"Nessuna promozione"<<std::endl;
	
	return m;
	
}

void Interface::noPiece(){
	std::cout<<"Quella casella è vuota. Riprovare."<<std::endl;
}

void Interface::validMove(){
	std::cout<<"Mossa effettuata con successo."<<std::endl;
}

void Interface::endGame(int code){
    switch (code) {
        case 0:
            std::cout<<"Partita patta."<< std::endl;
            break;
        case 1:
            std::cout<<"Scacco matto, vittoria per il bianco."<< std::endl;
            break;
        case 2:
            std::cout<<"Scacco matto, vittoria per il nero."<< std::endl;
            break;
        case 3:
            std::cout<<"Il bianco si ritira, vittoria per il nero."<< std::endl;
            break;
        case 4:
            std::cout<<"Il nero si ritira, vittoria per il bianco."<< std::endl;
            break;
    } // switch

    std::cout<<*cb<<std::endl;

    std::cout <<"Good game!"<< std::endl;
    
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

void Interface::isCheck(){
    std::cout<<"Scacco al re ";
    if (cb->currentPlayer()==white) std::cout<<"NERO";
    if (cb->currentPlayer()==black) std::cout<<"BIANCO";
    std::cout<<"."<<std::endl;
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
    return -1;
}