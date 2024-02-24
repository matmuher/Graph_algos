#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "Point.hpp"

enum class TileType
{
	Unknown,
	Obstacle,
	Free,
	Path,

// Algo state enum

	Checked,
	InProgress
};

std::ostream& operator<< (std::ostream& cout, TileType tileType)
{
	switch(tileType)
	{
		case TileType::Obstacle:

			cout << 'X';
			break;

		case TileType::Free:

			cout << 'F';
			break;

		case TileType::Path:

			cout << 'P';
			break;

		case TileType::Checked:

			cout << 'C';
			break;

		case TileType::InProgress:

			cout << 'I';
			break;
	
		case TileType::Unknown:
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
