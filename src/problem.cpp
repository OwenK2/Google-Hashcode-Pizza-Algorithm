#include "problem.h"

Problem::Problem(uint16_t w, uint16_t h, uint32_t mt, uint32_t ms) : min_top(mt), max_slice(ms), grid(w, h) {
	printf("Did standard constructor for Problem %p\n", this);
}
Problem::~Problem() {
	printf("Deleted Problem %p\n", this);
}

// Move constructor
Problem::Problem(Problem&& rhs) : grid(std::move(rhs.grid)), min_top(rhs.min_top), max_slice(rhs.max_slice) {
	printf("Did move constructor for Problem %p\n", this);
}

// Copy constructor
Problem::Problem(const Problem& rhs) : grid(rhs.grid), min_top(rhs.min_top), max_slice(rhs.max_slice) {
	printf("Did copy constructor for Problem %p\n", this);
}

Problem readInput(const char* path) {
	FILE* pFile = fopen(path, "r");

	uint16_t w, h;
	uint32_t mt, ms; // TODO: I think spec says max is 1000
	fscanf(pFile, "%hu %hu %u %u\n", &h, &w, &mt, &ms);
	Problem problem(w, h, mt, ms);
	printf("Created problem %p in readInput\n", &problem);

	char c;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			c = getc(pFile);
			switch (c) {
				case 'M':
					problem.grid(x, y) = MUSHROOM; break;
				case 'T':
					problem.grid(x, y) = TOMATO; break;
				default:
					problem.grid(x, y) = UNDEFINED; break;
			}
		}
		getc(pFile); // Throw away newline
	}

	fclose(pFile);

	return problem;
}
Problem randomProblem(uint16_t c, uint16_t r, uint16_t l, uint16_t h) {
	Problem problem(c, r, l, h);
	for(auto& it : problem.grid) {
		it = static_cast<Topping>(rand()%2 + 1);
	}
	return problem;
}