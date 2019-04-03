#include "grid.h"
#include "util.h"

struct Problem {
	const uint32_t min_top, max_slice;
	Grid grid;

	Problem(uint16_t w, uint16_t h, uint32_t mt, uint32_t ms);
	~Problem();

	// Move constructor
	Problem(Problem&& rhs);

	// Copy constructor
	Problem(const Problem& rhs);
};

typedef std::vector<Rect> Solution;

Problem readInput(const char* path);
Problem randomProblem(uint16_t c, uint16_t r, uint16_t l, uint16_t h);