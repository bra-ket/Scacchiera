#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include "structures.h"
#include "Piece.h"
#include "Pawn.h"
#include "Box.h"

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

class ChessBoard {

private:
    player p;
    Box * board[8][8];
    Position pKingW;
    Position pKingB;
    Piece * getPiece (Position a);
    void putPiece (Piece * pc, Position ps);
    void putPiece (Piece * pc, int x, int y);
    void movePiece(int sx, int sy,int dx, int dy);
    void movePiece(Position s, Position d);
    void movePiece(Move m);
    void emptyBox(Position p);
    void emptyBox(int x, int y);
	bool isFree(Position a);

	int detectCastling(Move m);
    // controlla se m e` un arrocco e se e` una mossa valida
    // l'arrocco viene comandato spostando il re di due nella direzione in cui si vuole arroccare
    // valori di ritorno:
    // -1: arrocco non permesso
    // 0: la mossa non e` un arrocco
    // 1: arrocco bianco dx
    // 2: arrocco bianco sx
    // 3: arrocco nero dx
    // 4: arrocco nero sx
    // per controllare se e` permesso deve:

    // 1) verificare che la casella di partenza e quella in cui dovrebbe esserci la torre siano occupate
    // 2) verificare che il pezzo sulla casella di partenza e la torre sul lato dell'arrocco non siano mai stati mossi
    // questo garantisce che non possano essere pezzi diversi dal re e dalla torre
    // 2) verificare che le caselle di mezzo siano libere
    // 3) verificare che le caselle di mezzo non siano minacciate (usiamo il metodo isAttacked)
    int detectEnPassant(Move m);
    // controlla se m e` una presa en passant e se e` valida
    // valori di ritorno:
    // -1: presa en passant non permessa
    // 0: non e` una presa en passant
    // 1: e` una presa en passant valida
    bool isAttacked(Position p, player attacker);
    bool isAttacked(int x, int y, player attacker);
	bool isCheckMate(player p);
	bool isValid(int x, int y);
	Position getKingPosition(player p);
	void moveKing(player p, Position d);
	vector<Position> getAttackingPositions(Position p, player attacker);
	bool simMove(Move m); // simulates a Move to test if it puts the player's king under check
	bool isFree(int x, int y);
	Piece * getPiece(int x, int y);
    
public:
	ChessBoard();
	virtual ~ChessBoard();
	void switchPlayer();
	player currentPlayer();
	player oppositePlayer();
	int doMove(Move m);
    void promote(Position p, char type);
    void resetEnPassant(player p);
    bool isCheckMate();
	bool isCheck(player p);

    
    friend ostream& operator<<(ostream& out,  ChessBoard& cb) // output
    {
        Position p;
        
        // prints x coordinates
        out << "  ";
        for (char c = 'a'; c <= 'h'; c++)
        out << "  " << c << "  ";
        out << endl;
        
        // prints the upper horizontal row
        out << "  ";
        for (int j = 0; j < 8; j++)
        out << " ____";
        out << endl;
        
        
        for (int i = 8; i >= 1; i--) {
            out << i << " ";
            
            // prints the left column element
            out << "|";
            
            for (int j = 1; j < 9; j++) {
                // horizontal scan
                
                
                if (cb.isFree(j,i)==true)
                    out << "    " << "|"; // se la casella è vuota printa uno zero
                else {
                    if (cb.getPiece(j,i)->getPlayer()== white)
                        out << " W"; // se è il pezzo è bianco
                    else out << " B"; // se è il pezzo è nero
                    
                    out << cb.getPiece(j,i)->getType() << " |"; // se c'è un pezzo printa il char del tipo di pezzo
                    
                    
                } // else
                
            } // for
            
            out << " " << i;
            
            out << std::endl;
            
            out << "  ";
            
            for (int j = 1; j < 9; j++)
                out << "|____";
            out << "|" << std::endl;
        } // for
        
        // prints x coordinates
        out << "  ";
        for (char c = 'a'; c <= 'h'; c++)
        out << "  " << c << "  ";
        out << endl;
        return out;
    }

}; // ChessBoard()

#endif /* CHESSBOARD_H_ */
