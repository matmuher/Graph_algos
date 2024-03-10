#include "Grid.hpp"
#include "Point.hpp"
#include "Print.hpp"

#include <cstring>
#include <algorithm>

namespace GA
{

template<class ValueType>
Grid<ValueType>::Grid(size_t _size)
:
	size{_size},
	root{nullptr}
{
	root = new ValueType[size * size]; // what if I want to call special constructor?
}

template<class ValueType>
Grid<ValueType>::Grid(size_t _size, ValueType filler) : Grid(_size)
{
	fill(filler);
}

template<class ValueType>
Grid<ValueType>::Grid(const Grid& other)
:
	Grid(other.size)
{
	std::cout << "Copy ctor\n";
	std::memcpy(this->root, other.root, sizeof(ValueType) * size * size);
}



template<class ValueType>
Grid<ValueType>& Grid<ValueType>::operator= (const Grid<ValueType>& other)
{
	std::cout << "Operator=\n";
	std::memcpy(this->root, other.root, sizeof(ValueType) * size * size);
}

template<class ValueType>
Grid<ValueType>::Grid(Grid&& other)
:
	size{other.size},
	root{nullptr}
{
	std::cout << "Move ctor\n";
	std::swap(this->root, other.root);
	const_cast<size_t&>(other.size) = 0;
}

template<class ValueType>
Grid<ValueType>::~Grid()
{
	delete[] root;
}

template<class ValueType>
void Grid<ValueType>::fill(ValueType filler)
{
	for(int tile_id = 0; tile_id < int(size * size); tile_id++)
	{
		root[tile_id] = filler;
	}
}

template<class ValueType>
void Grid<ValueType>::clear()
{
	fill(ValueType());
}

template<class ValueType>
ValueType* Grid<ValueType>::operator[] (int row_id)
{
	return root + row_id * size;
}

template<class ValueType>
ValueType& Grid<ValueType>::at(const Point& point)
{
	const Grid& thisGrid = *this;
	return const_cast<ValueType&>(thisGrid.at(point)); // avoid copypaste
}

template<class ValueType>
const ValueType& Grid<ValueType>::at(const Point& point) const
{
	return *(root + point.y * size + point.x);
}

template<class ValueType>
const ValueType* Grid<ValueType>::operator[] (int row_id) const
{
	return root + row_id * size;
}

#define OPPOSITS(dir, reverse)			\
			case dir: return reverse;	\
			case reverse: return dir;	\

MoveDirection operator! (MoveDirection moveDirection)
{
	using enum MoveDirection;

	switch(moveDirection)
	{
		OPPOSITS(Up, Down)
		OPPOSITS(Right, Left)

		default: return No;
	}

	return No;
}

#undef OPPOSITS

#define RET_SHIFT(Dir, x_shift, y_shift)	 						\
						case Dir: return Point{x_shift, y_shift};	\

Point getShift(MoveDirection moveDirection)
{
	using enum MoveDirection;

	switch(moveDirection)
	{
		RET_SHIFT(Up, 	 0,  1)
		RET_SHIFT(Down,  0, -1)
		RET_SHIFT(Right, 1,  0)
		RET_SHIFT(Left, -1,  0)
		RET_SHIFT(No,	 0,  0)
	}

	return Zeros;
}

#undef RET_SHIFT

// For compiller to know which version to generate
// REALLY? MANUALLY?
template class Grid<int>;
template class Grid<Point>;
template class Grid<AlgoState>;
template class Grid<Tile>;
template class Grid<MoveDirection>;
template class Grid<char>;
template class Grid<MaChar>;
template class Grid<Color>;

};