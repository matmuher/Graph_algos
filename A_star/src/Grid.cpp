#include "Grid.hpp"
#include "Point.hpp"

template<class ValueType>
Grid<ValueType>::Grid(size_t _size) : size{_size}, root{nullptr}
{
	root = new ValueType[size * size]; // what if I want to call special constructor?
}

template<class ValueType>
Grid<ValueType>::~Grid()
{
	delete[] root;
}

template<class ValueType>
Grid<ValueType>::Grid(size_t _size, ValueType filler) : Grid(_size)
{
	fill(filler);
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


// For compiller to know which version to generate
// REALLY? MANUALLY?
template class Grid<int>;
template class Grid<Point>;
template class Grid<AlgoState>;
template class Grid<Tile>;
template class Grid<Results>;