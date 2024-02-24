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

std::ostream& operator<< (std::ostream& cout, Results results)
{
	switch(results)
	{
		case Results::Path:

			cout << 'V';
			break;

		case Results::Free:

			cout << 'o';
			break;

		default: // default - copypaste

			cout << '?';
			break;
	}

	return cout;
}

std::ostream& operator<< (std::ostream& cout, AlgoState algoState)
{
	switch(algoState)
	{
		case AlgoState::Checked:

			cout << 'C';
			break;

		case AlgoState::InProgress:

			cout << 'I';
			break;

		case AlgoState::Free:

			cout << '0';
			break;

		default:

			cout << '?';
			break;
	}

	return cout;
}

std::ostream& operator<< (std::ostream& cout, Tile tileType)
{
	switch(tileType)
	{
		case Tile::Obstacle:

			cout << 'X';
			break;

		case Tile::Free:

			cout << 'F';
			break;

		case Tile::Unknown:
		default:

			cout << '?';
			break;
	}

	return cout;
}

template<class ValueType>
class Grid
{
public:
 
	const size_t size;

	Grid(size_t _size);

	ValueType* operator[] (int row_id);  

	const ValueType* operator[] (int row_id) const;

	ValueType& at(const Point& point);

	const ValueType& at(const Point& point) const;

private:

	ValueType* root;
};

template<class ValueType>
Grid<ValueType>::Grid(size_t _size) : size{_size}, root{nullptr}
{
	root = new ValueType[size * size];
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

template<class ValueType>
void print(const Grid<ValueType>& graph)
{
	system("clear");

	for (size_t y = 0; y < graph.size; y++)
	{
		for (size_t x = 0; x < graph.size; x++)
		{
			std::cout << graph[y][x] << ' ';
		}

		std::cout << '\n';
	}

	std::cin.get();
}
