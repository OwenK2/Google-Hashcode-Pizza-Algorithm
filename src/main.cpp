#include "grid.h"
#include "util.h"
#include "areabreaker.h"
#include <fstream>


void writeSolution(const char* name, Solution s) {
	std::ofstream file(name, std::ofstream::out);
	file << s.size();
	for(auto slice : s) {
		file << std::endl << slice.pos.x << " " << slice.pos.y << " " << slice.size.w << " " << slice.size.h;
	}
	file.close();
}

int main(int argc, char const *argv[]) {
	srand(time(0)); //must seed the random generator first

	// Problem p = readInput("b_small.in");
	Problem p = randomProblem(100, 100, 3, 10);
	printf("Problem: %i %i %i %i\n", p.grid.w, p.grid.h, p.min_top, p.max_slice);
	// printGrid(p.grid);
	

	printf("Creating solver...\n");
	AreaBreaker solver;
	Solution s = solver(p);
	printf("Created solver\n");
	//Write solution to google formatted output file
	writeSolution("solution.txt", s);
	

	return 0;
}