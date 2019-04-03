#include "grid.h"

// CONSTRUCTORS AND DESTRUCTOR

Grid::Grid(uint16_t _w, uint16_t _h, Topping init) : w(_w), h(_h), max(_w * _h) {
	grid = new Topping[w * h];
	memset(grid, init, sizeof(Topping) * w * h);
	printf("Did standard constructor for Grid %p\n", this);
}

Grid::~Grid() {
	printf("Deleting grid %p from %p\n", grid, this);
	delete[] grid;
}

Grid::Grid(const Grid& rhs) : w(rhs.w), h(rhs.h), max(rhs.max) {
	grid = new Topping[w * h];
	memcpy(grid, rhs.grid, sizeof(Topping) * w * h);
	printf("Did copy constructor for Grid %p\n", this);
}

Grid::Grid(Grid&& rhs) : w(rhs.w), h(rhs.h), max(rhs.max) {
	grid = rhs.grid;
	rhs.grid = nullptr;
	printf("Did move constructor for Grid %p\n", this);
}

// ACCESS FUNCTIONS

Topping& Grid::at(uint16_t x, uint16_t y) {
	// Throws an error if x and y are out of bounds
	if (x >= w || y >= h) throw std::out_of_range("Index out of range");
	return grid[x + y*w];
}

Topping Grid::at(uint16_t x, uint16_t y) const {
	if (x >= w || y >= h) throw std::out_of_range("Index out of range");
	return grid[x + y*w];
}

Topping& Grid::at(Point p) {
	if (p.x >= w || p.y >= h) throw std::out_of_range("Index out of range");
	return grid[p.x + p.y*w];
}
Topping Grid::at(Point p) const {
	if (p.x >= w || p.y >= h) throw std::out_of_range("Index out of range");
	return grid[p.x + p.y*w];
}

Topping& Grid::operator()(uint16_t x, uint16_t y) {
	if (x >= w || y >= h) throw std::out_of_range("Index out of range");
	return grid[x + y*w];
}

Topping Grid::operator()(uint16_t x, uint16_t y) const {
	if (x >= w || y >= h) throw std::out_of_range("Index out of range");
	return grid[x + y*w];
}
Topping& Grid::operator()(Point p) {
	if (p.x >= w || p.y >= h) throw std::out_of_range("Index out of range");
	return grid[p.x + p.y*w];
}

Topping Grid::operator()(Point p) const {
	if (p.x >= w || p.y >= h) throw std::out_of_range("Index out of range");
	return grid[p.x + p.y*w];
}

bool Grid::in(Point p) const {
	return p.x <= w && p.y <= h;
}
bool Grid::in(Rect r) const {
	return r.pos.x+r.size.x <= w && r.pos.y+r.size.y <= h;
}

// ITERATOR

Grid::iterator::iterator(Grid& _g, Rect _r, Point _p) : g(_g), rect(_r), pos(_p) {}
Grid::iterator::~iterator() {}

Point Grid::iterator::position() const {
	return pos;
}

Topping& Grid::iterator::operator*() const {
	return g(pos.x, pos.y); // will be meaningless if grid.end()
}

Grid::iterator& Grid::iterator::operator++() {
	if (!rect.in(pos)) return *this; // end

	++pos.x;
	if (pos.x >= rect.pos.x + rect.size.w) {
		pos.x = rect.pos.x;
		++pos.y;
	}
	// The return type for this function is a REFERENCE to an iterator
	// C++ will automatically create references to objects
	// However "this" is a pointer. So we must dereference the pointer (*this)
	// in order to access the actual object. Then c++ will get a reference to 
	// the actual object.
	return *this;
}

bool Grid::iterator::operator==(const Grid::iterator& rhs) const {
	// Checks if the addresses of the grid objects are the same
	return (&(rhs.g) == &g) && (rhs.pos == pos) && (rhs.rect == rect);
}

bool Grid::iterator::operator!=(const Grid::iterator& rhs) const {
	return !(*this == rhs);
}

Grid::iterator Grid::begin() {
	return iterator(*this, Rect(0, 0, w, h), Point(0, 0));
}

Grid::iterator Grid::begin(Rect r) {
	return iterator(*this, r, r.pos);
}

Grid::iterator Grid::end() {
	return iterator(*this, Rect(0, 0, w, h), Point(0, h));
}

Grid::iterator Grid::end(Rect r) {
	return iterator(*this, r, Point(r.pos.x, r.pos.y + r.size.h));
}

// CONST ITERATOR

Grid::const_iterator::const_iterator(const Grid& _g, Rect _r, Point _p) : g(_g), rect(_r), pos(_p) {}
Grid::const_iterator::~const_iterator() {}

Point Grid::const_iterator::position() const {
	return pos;
}

Topping Grid::const_iterator::operator*() const {
	return g(pos.x, pos.y); // will be meaningless if grid.end()
}

Grid::const_iterator& Grid::const_iterator::operator++() {
	if (!rect.in(pos)) return *this; // end

	++pos.x;
	if (pos.x >= rect.pos.x + rect.size.w) {
		pos.x = rect.pos.x;
		++pos.y;
	}
	// The return type for this function is a REFERENCE to an const_iterator
	// C++ will automatically create references to objects
	// However "this" is a pointer. So we must dereference the pointer (*this)
	// in order to access the actual object. Then c++ will get a reference to 
	// the actual object.
	return *this;
}

bool Grid::const_iterator::operator==(const Grid::const_iterator& rhs) const {
	// Checks if the addresses of the grid objects are the same
	return (&(rhs.g) == &g) && (rhs.pos == pos) && (rhs.rect == rect);
}

bool Grid::const_iterator::operator!=(const Grid::const_iterator& rhs) const {
	return !(*this == rhs);
}

Grid::const_iterator Grid::begin() const {
	return const_iterator(*this, Rect(0, 0, w, h), Point(0, 0));
}

Grid::const_iterator Grid::begin(Rect r) const {
	return const_iterator(*this, r, r.pos);
}

Grid::const_iterator Grid::end() const {
	return const_iterator(*this, Rect(0, 0, w, h), Point(0, h));
}

Grid::const_iterator Grid::end(Rect r) const {
	return const_iterator(*this, r, Point(r.pos.x, r.pos.y + r.size.h));
}