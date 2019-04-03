#ifndef _GRID_H_
#define _GRID_H_

#include <cstring>
#include <cstdint>
#include <stdexcept>
#include "util.h"

// uint8_t is an unsigned 8 bit integer type
// it occupies only one byte so it's space efficient
enum Topping : uint8_t {
	UNDEFINED,
	MUSHROOM,
	TOMATO
};

class Grid {
// Protected instead of private so that iterator can access
protected:
	Topping* grid;

	const uint32_t max; // w * h

public:
	// uint16_t is an unsigned 16 bit integer type
	// it occupies two bytes, for a total of 65536 possibilities
	// the spec says it will be a max of 1000 so this is perfect
	const uint16_t w, h;

	Grid(uint16_t _w, uint16_t _h, Topping init = UNDEFINED);
	~Grid();

	// Copy constructor
	Grid(const Grid& rhs);

	// Move constructor
	Grid(Grid&& rhs);

	// Copy assignment operator is deleted due to const qualifications
	Grid& operator=(const Grid& rhs) = delete;

	// returns a reference to the topping, which can be modified
	// i.e. you can do grid.at(5, 10) = MUSHROOM;
	Topping& at(uint16_t x, uint16_t y);

	// this is the const version of the above function
	// if we're dealing with a const grid, this will be called instead
	// note that it does NOT return a reference
	Topping at(uint16_t x, uint16_t y) const;

	Topping& at(Point p);
	Topping at(Point p) const;

	// same thing as at, but allows you to call it directly as a functor
	// i.e. grid(5, 10)
	Topping& operator()(uint16_t x, uint16_t y);
	Topping operator()(uint16_t x, uint16_t y) const;
	Topping& operator()(Point p);
	Topping operator()(Point p) const;

	//Check if point is inside grid
	bool in(Point p) const;
	bool in(Rect r) const;

	// here I define iterator structures so we can loop through the pizza
	// you can use something like
	// for (auto it : grid) { ... } where it is the topping

	friend class iterator;
	friend class const_iterator;

	class iterator {
	friend Grid;
	
	private:
		// A reference to the grid that this iterator acts on
		Grid& g;

		// The position within the grid that this iterator is pointing to
		Point pos;

		// This is the slice to iterate over. This may be the whole pizza.
		Rect rect;

	protected:
		// This constructor is protected, so that only the friend class "Grid"
		// can create a new one. This hides the implementation details.
		iterator(Grid& _g, Rect _r, Point _p);

	public:
		// Destructors have to be public
		~iterator();

		//gets current index of iterator
		Point position() const;

		// Overloads the dereferencing operator
		// That way, if you have a Grid::iterator it, then you can
		// use *it to access the Topping. When using range based for loops
		// this automatically happens.
		Topping& operator*() const;

		// Overloads the ++ operator, allowing the iterator to
		// increment one step forward.
		iterator& operator++();

		// Overloads equality operators to check if iterators are the same.
		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
	};

	class const_iterator {
	friend Grid;
	
	private:
		const Grid& g;
		Point pos;
		Rect rect;

	protected:
		const_iterator(const Grid& _g, Rect _r, Point _p);

	public:
		~const_iterator();

		Point position() const;
		Topping operator*() const;
		const_iterator& operator++();

		bool operator==(const const_iterator& rhs) const;
		bool operator!=(const const_iterator& rhs) const;
	};


	// This returns an iterator to the beginning of the grid (0, 0).
	iterator begin();
	iterator begin(Rect r);

	const_iterator begin() const;
	const_iterator begin(Rect r) const;

	// Returns an iterator to the end of the grid (index w*h, so it's past the end)
	iterator end();
	iterator end(Rect r);

	const_iterator end() const;
	const_iterator end(Rect r) const;
};


#endif // _GRID_H_