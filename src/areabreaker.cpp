#include "areabreaker.h"
#include <algorithm>

AreaBreaker::~AreaBreaker() {}

bool AreaBreaker::validSlice(const Problem& p,Rect r) const{
	if(not(p.grid.in(r))) {return false;}
	uint32_t m = 0;
	uint32_t t = 0;
	for(auto it = p.grid.begin(r); it != p.grid.end(r); ++it) {
		if(*it == MUSHROOM) ++m;
		else if(*it == TOMATO) ++t;
		else {return false;}
	}	
	if(m < p.min_top || t < p.min_top || r.size.w*r.size.h > p.max_slice) {
		// printf("Checking slice %i %i %i %i : invalid\n", r.pos.x,r.pos.y,r.size.w,r.size.h);
		// if(m < p.min_top) printf("\t Because: not enough mushroom\n");
		// if(t < p.min_top) printf("\t Because: not enough tomato\n");
		// if(r.size.w*r.size.h > p.max_slice) printf("\t Because: slice too big\n");
		return false;
	}
	else {
		// printf("Checking slice %i %i %i %i : valid\n", r.pos.x,r.pos.y,r.size.w,r.size.h);
		return true;
	}
}

Factors AreaBreaker::bestArea(const Problem& p,int size) const{
	std::vector<int> factors;
	Factors best(0,0);
	for(int i = 1;i <= size;++i) {
		if(size % i == 0) {
			factors.push_back(i);
		}
	}
	for(int i = 0;i < factors.size();++i) {
		for(int j = i;j < factors.size();++j) {
			int f1 = factors[i];
			int f2 = factors[j];
			if(f1 * f2 == size) {
				if(f1 < p.grid.w || f2 < p.grid.h) {
					best.f1 = f1;
					best.f2 = f2;
				}
				else if(f2 < p.grid.w || f1 < p.grid.h) {
					best.f1 = f2;
					best.f2 = f1;
				}
			}
		}
	}
	return best;
}
void AreaBreaker::makeSlice(Grid& g,Rect r) const {
	for(auto it = g.begin(r); it != g.end(r); ++it) {
		g(it.position()) = UNDEFINED;
	}
}

Solution AreaBreaker::operator()(const Problem& p) const {
	Grid g(p.grid);
	Solution slices;
	for(int area = p.max_slice;area >= p.min_top*2;--area) {
		Factors dim = bestArea(p,area);
		for(auto it = g.begin(); it != g.end(); ++it) {
			Point index = it.position();
			if(g(index) == UNDEFINED) {continue;}
			Rect slice(index,dim.f1,dim.f2);
			if(validSlice(p,slice)) {
				makeSlice(g,slice);
				slices.push_back(slice);
			}
			else {
				slice.size.w = dim.f2;
				slice.size.h = dim.f1;
				if(validSlice(p,slice)) {
					makeSlice(g,slice);
					slices.push_back(slice);
				}
			}
		}
	}
	// printGrid(g);
	// for(auto it = slices.begin(); it != slices.end(); ++it) {
	// 	printf("Slice Found at: %i %i %i %i\n", it->pos.x, it->pos.y, it->size.x, it->size.y);
	// }
	int score = 0;
	for(auto it = g.begin(); it != g.end(); ++it) {
		if(g(it.position()) == UNDEFINED) {
			++score;
		}
	}
	float percent = (float)score / (g.w*g.h) * 100;
	printf("\n\e[1mScore: %i out of %i (%f%c)\e[0m\n\n", score,g.w*g.h, percent, '%');
	return slices;
}