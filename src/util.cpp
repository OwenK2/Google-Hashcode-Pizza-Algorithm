#include "util.h"
#include "grid.h"
#include "problem.h"

void printGrid(Grid& g) {
	printGrid(g, Rect(0, 0, g.w, g.h));
}

void printGrid(Grid& g, Rect r) {
	for(auto it = g.begin(r); it != g.end(r); ++it) {
		char symbol;

		switch(*it) {
			case MUSHROOM:
				symbol = 'M';
				break;
			case TOMATO:
				symbol = 'T';
				break;
			default:
				symbol = '?';
		}

		printf("%c%c", symbol, it.position().x == r.pos.x + r.size.w - 1 ? '\n' : ' ');
	}
}

Grid generatePizza() {
	return generatePizza(rand() % 1000 + 1, rand() % 1000 + 1);
}

Grid generatePizza(uint16_t w, uint16_t h) {
	Grid g(w, h);

	for(auto& it : g) {
		it = static_cast<Topping>(rand()%2 + 1);
	}

	return g;
}