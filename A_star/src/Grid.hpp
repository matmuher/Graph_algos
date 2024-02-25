#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "Point.hpp"

enum class Tile
{
	Free,
	Obstacle,
	Unknown	
};

enum class AlgoState
{
	Free,
	Checked,
	InProgress
};

enum class Results
{
	Free,
	Path
};

template<class ValueType>
class Grid
{
public:
 
	const size_t size;

	Grid(size_t _size);

	Grid(size_t _size, ValueType filler);

	void fill(ValueType filler);

	void clear();

	ValueType* operator[] (int row_id);  

	const ValueType* operator[] (int row_id) const;

	ValueType& at(const Point& point);

	const ValueType& at(const Point& point) const;

	~Grid();

private:

	ValueType* root;
};