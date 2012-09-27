#ifndef STRUCTURES_H_
#define STRUCTURES_H_


enum player { white, black };


struct Position {
	int x;
	int y;
	Position(){};

	Position& operator=(const Position &rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	};

	// coordinates must be valid, otherwise unpredictable behaviour might occur
	Position (int _x, int _y){
		x=_x;
		y=_y;
	};
};

struct Delta {
	int x;
	int y;

	Delta() {
		x=0;
		y=0;
	};

	Delta& operator=(const Delta &rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	};

	bool operator==(Delta &other) const {
		if (other.x==x and other.y==y) return true;

		else return false;
	};
};


#endif /* STRUCTURES_H_ */
