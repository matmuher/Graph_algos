#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "Point.hpp"

namespace GA
{

enum class Tile
{
	No,
	Obstacle
};

enum class AlgoState
{
	No,
	Checked,
	InProgress
};

enum class MoveDirection
{
	No,
	Up,
	Down,
	Left,
	Right,
	Start,
	End
};

MoveDirection operator! (MoveDirection dir);

Point getShift(MoveDirection moveDirection);

template<class ValueType>
class Grid
{
public:
 
	const size_t size;

	Grid(size_t _size);

	Grid(size_t _size, ValueType filler);

	Grid(const Grid& other);

	Grid& operator= (const Grid& other);

	Grid(Grid&& other);

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

extern const std::map<MoveDirection, Point> shifts;
};
