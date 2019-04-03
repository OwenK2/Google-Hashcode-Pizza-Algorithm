#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "problem.h"


class Strategy {
public:
	virtual ~Strategy() {};
	
	virtual Solution operator()(const Problem& p) const = 0;
};

#endif // _STRATEGY_H_