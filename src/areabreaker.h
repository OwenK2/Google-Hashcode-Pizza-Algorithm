#include "strategy.h"

struct Factors {
	uint16_t f1, f2;
	Factors(uint16_t _f1,uint16_t _f2) : f1(_f1), f2(_f2) {}
	~Factors() {}
};

class AreaBreaker : public Strategy {
	private:
		void makeSlice(Grid& g, Rect r) const;
		Factors bestArea(const Problem& p,int size) const;
		bool validSlice(const Problem& p,Rect r) const;
	public:
		Solution operator()(const Problem& p) const;
		~AreaBreaker();
};