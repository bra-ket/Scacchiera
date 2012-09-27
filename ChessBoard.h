#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include "structures.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Box.h"
#include "Move.h"

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

class ChessBoard {


private:
    player cpl; // current player
    Box * board[8][8]; // cell matrix
    Position pKingW; // white king position
    Position pKingB; // black king position

    // gets the Piece on the Box at the Position a
    Piece * getPiece (Position a);

    // gets the Piece on the Box at the Position of coordinates (x,y)
    Piece * getPiece(int x, int y);

    // put the Piece referenced by pc on the Box at the Position ps
    void putPiece (Piece * pc, Position ps);

    // put the Piece referenced by pc on the Box at the Position of coordinates (x,y)
    void putPiece (Piece * pc, int x, int y);

    // performs the Move m on the piece
    void movePiece(Move m);

    // moves a Piece from the Position s to the Position d
    void movePiece(Position s, Position d);

    // moves a Piece from the Position of coordinates (sx, sy) to the position of coordinates (dx, dy)
    void movePiece(int sx, int sy,int dx, int dy);

    // empties the Box at the Position p
    void emptyBox(Position p);

    // empties the Box at the Position of coordinates (x,y)
    void emptyBox(int x, int y);

    // returns true if the Box at the Position a is free, false otherwise
	bool isFree(Position a);

	// returns true if the Box at the Position of coordinates (x,y) is free, false otherwise
	bool isFree(int x, int y);

	// returns:
	// 0  if the Move m is not a castling
	// -1 if the Move m is a castling but it's not currently allowed
	// a value >0 if Move m is an allowed castling:
	// 1  white right castling
	// 2  white left castling
	// 3  black right castling
	// 4  black left castling
	int detectCastling(Move m);


	// returns:
	// 0  if Move m is not an en-passant capture
	// -1 if Move m is an en-passant capture but it's not allowed
	// 1  if Move m is an en-passant capture and it's allowed
    int detectEnPassant(Move m);

    // returns true if the Position p is under attack by player attacker, false otherwise
    bool isAttacked(Position p, player attacker);

    // returns true if the Position of coordinates (x,y) is attacked by player attacker, false otherwise
    bool isAttacked(int x, int y, player attacker);

    // returns true if the player attacker has given checkmate to the opponent
	bool isCheckMate(player attacker);

	// returns true if (x,y) are valid coordinates for the ChessBoard
	bool isValid(int x, int y);

	// get the Position of the Box that stores the King of player p
	Position getKingPosition(player p);

	// sets to d the King position record of the player p
	// it doesn't actually move the piece on the ChessBoard
	void moveKing(player p, Position d);

	// gets all the positions of Boxes containing attacker's pieces which are attacking a given Position p
	vector<Position> getAttackingPositions(Position p, player attacker);

	// simulates a Move, test if it put the current player's King into check, then rollbacks the Move
	// returns the outcome of the test: true if the Move lead to a check situation for the current player, false otherwise
	bool simMove(Move m);
    
public:
	ChessBoard();
	virtual ~ChessBoard();

	// switches the current player
	void switchPlayer();

	// returns the current player
	player currentPlayer();

	// returns the opposite player
	player oppositePlayer();

	// performs the controls to check if Move m is allowed
	// return values:
	// 0: valid move
	// 1: no piece to move
	// 2: player tries to move an opponent's piece
	// 3: player tries to capture an own piece
	// 4: invalid move due to invalid path
	// 5: invalid move due to obstructed path
	// 6: check on the player's move
	// 7: castling not allowed
	// 8: en passant not allowed
	// 9: promotion
	int doMove(Move m);

	// promotes the piece on the Position p to the given type
	void promote(Position p, char type);

	// resets the en-passant flag for all the pawns of the player p
	void resetEnPassant(player p);

	// returns true if the current player has given a checkmate to the opponent, false otherwise
	bool isCheckMate();

	// returns true if the King owned by player p is under check
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
                	// if the box is free prints white saces
                    out << "    " << "|";
                else {
                    if (cb.getPiece(j,i)->getPlayer() == white)
                        out << " W"; // white piece
                    else
                    	out << " B"; // black piece
                    
                    // prints the piece type
                    out << cb.getPiece(j,i)->getType() << " |";

                } // else
                
            } // for
            
            out << " " << i; // prints the column number
            
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
    } // <<

}; // ChessBoard()

#endif /* CHESSBOARD_H_ */
