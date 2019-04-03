#ifndef _UTIL_H_
#define _UTIL_H_

#include <cstdio>
#include <string>
#include <ctime>
#include <vector>

class Grid; // Forward declaration of grid

struct Point {
	union {
		uint16_t x;
		uint16_t w;
	};

	union {
		uint16_t y;
		uint16_t h;
	};

	Point(uint16_t _x, uint16_t _y) : x(_x), y(_y) {}
	Point() : x(0), y(0) {};

	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const Point& rhs) const {
		return !(*this == rhs);
	}
};

struct Rect {
	Point pos;
	Point size;

	Rect(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h) : pos(_x, _y), size(_w, _h) {}
	Rect(Point _pos, Point _size) : pos(_pos), size(_size) {}
	Rect(uint16_t _x, uint16_t _y, Point _size) : pos(_x, _y), size(_size) {}
	Rect(Point _pos, uint16_t _w, uint16_t _h) : pos(_pos), size(_w, _h) {}

	bool in(const Point& p) const {
		return (p.x >= pos.x && p.y >= pos.y && p.x < pos.x + size.w && p.y < pos.y + size.h);
	}

	bool operator==(const Rect& rhs) const {
		return pos == rhs.pos && size == rhs.size;
	}

	bool operator!=(const Rect& rhs) const {
		return !(*this == rhs);
	}
};


void printGrid(Grid& g, Rect r);
void printGrid(Grid& g);

Grid generatePizza(uint16_t w, uint16_t h);
Grid generatePizza();


#endif // _UTIL_H_
