/*
 * ChessBoard.cpp
 *
 *  Created on: 16/giu/2012
 *      Author: massimiliano
 */


#include "Box.h"
#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	p = white;
    //TODO Generate all the pieces and alloc them
}

ChessBoard::~ChessBoard() {
	// TODO Auto-generated destructor stub
}

void ChessBoard::switchPlayer() {
	p = (p == white ? black : white);
} // switchPlayer

bool ChessBoard::isFree(Position p) {
    return board[p.x][p.y]->isFree();
} // isFree()


/* performs a move on the chessboard
 * return values:
 * - 0: valid move
 * - 1: no piece to move
 * - 2: player tries to move an opponent's piece
 * - 3: player tries to capture an own piece
 * - 4: invalid move due to invalid path
 * - 5: invalid move due to obstructed path
 * - 6: check on the player's move
 * - 7: castling not allowed
 * - 8: en passant not allowed
 */
int ChessBoard::doMove(Move m) {
	Piece * ps = this->getPiece(m.s); // content on the source position
	Piece * pd = this->getPiece(m.d); // content on the destination position
	if (ps == 0)
		return 1; // empty source position
	if (ps->getPlayer() != p)
		return 2; // player tries to move an opponent's piece
	if (pd->getPlayer() == p)
		return 3; // player tries to capture an own piece

	int castling = detectCastling(m);

	if (castling) {
		switch (castling) {
		case -1:
			return 7;
		case 1:
			// white right
			movePiece(m.s,m.d);
			break;
		case 2:
			// white left
			break;
		case 3:
			// black right
			break;
		case 4:
			// black left
			break;
		} // switch
		return 0;
	} // if

	int enps = detectEnPassant(m);

	if (enps) {
		switch (enps) {
		case -1:
			return 8;
		case 1:
			// effettuare la mossa
			break;
		} // switch
	} else { // normal move

		if (!ps->isValid(m))
			return 4; // invalid path
		movePiece(m.s,m.d);
	} // else

	if (isCheck(p)) {
		// rollback
		return 6;
	} // if

	// gestione promozione
} // doMove()


// ti consiglio di rifarlo facendo una cosa del genere:
// array di Move con i quattro arrocchi
// for che cerca la mossa nell'array e si ferma se la trova
// switch sull'indice per fare le verifiche a seconda del caso, mettendo eventualmente in AND le condizioni sulle caselle
// visto che sono due o tre
int ChessBoard::detectCastling(Move m){
	if (p==white) if (kingW->hasMoved()) return -1;
	if (p==black) if (kingB->hasMoved()) return -1;
	// in realta` e` inessenziale controllare quale sia il giocatore. doMove controlla di suo che il pezzo muovente sia di proprieta`
	// del giocatore corrente. manca il controllo sul fatto che la torre si sia mossa o meno
	Delta d[2];
	d[0].x=2;
	d[0].y=d[1].y=0;
	d[1].x=-2;
	// non capisco il perche` di un array a questo punto, visto che non devi iterare e devi solo controllare due casi.
	// l'array ha senso se fai un array di Move che contiene i quattro arrocchi possibili e confronti m con quello
	
	if (m.getdelta().x==d[0].x and m.getdelta().y==d[0].y){
 	   for (int i=1; i<2; i++) { // un ciclo con due sole iterazioni e che controlla posizioni predeterminate? forse conviene un OR
	   	   Position pos;
           pos.x=m.s.x+i;
           pos.y=m.s.y; // resta uguale, non ha senso assegnarlo ad ogni giro del for
           // questa cosa di costruire la pos apposta mi pare brutta, facciamo un overload di isFree(int x, int y) ?
           if(!isFree(pos[i])) return -1; //se non sono liberi
           if (isAttacked(pos[i])) return -1; //se sono sotto attacco
           // devi controllare anche che il re non sia sotto attacco
           }
   		if (p==white) return 1;
   		if (p==black) return 3;
		}
	
	if (m.getdelta().x==d[1].x and m.getdelta().y==d[1].y){
 	   for (int i=1; i<2; i++) {
	   	   Position pos;
           pos.x=m.s.x-i;
           pos.y=m.s.y;
           if(!isFree(pos[i])) return -1; //se non sono liberi
           if (isAttacked(pos[i])) return -1; //se sono sotto attacco
           }
   		if (p==white) return 2;
   		if (p==black) return 4;
		} 
        }
    
    else return 0; //la mossa non è un arrocco
}

bool ChessBoard::isAttacked(Position p, player attacker) {
	// check for attacks from knights

} // isAttacked()

void ChessBoard::movePiece(Position s, Position d) {
	putPiece(getPiece(s), d);
	emptyBox(s);
} // movePiece

void ChessBoard::putPiece(Piece * pc, Position ps) {
	board[ps.x][ps.y]->putPiece(pc);
} // putPiece()




