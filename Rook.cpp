
#include "Rook.h"

Rook::Rook(player p) {
    type='R';
    pl=p;
    Delta d;
    for (int i=0; i<28; i++) possibleMoves.push_back(d);
    for (int i=1; i<8; i++) {
		int j=4*(i-1);
		possibleMoves[j].x=i;
    	possibleMoves[j].y=0;
    	possibleMoves[j+1].x=0;
    	possibleMoves[j+1].y=-i;
		possibleMoves[j+2].x=-i;
    	possibleMoves[j+2].y=0;
    	possibleMoves[j+3].x=0;
    	possibleMoves[j+3].y=+i;
		}


}

