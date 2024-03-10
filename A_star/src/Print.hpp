#pragma once

#include "Grid.hpp"
#include "Point.hpp"

#include <iostream>

namespace GA
{

std::ostream& operator<< (std::ostream& cout, AlgoState algoState);


std::ostream& operator<< (std::ostream& cout, Tile tileType);


std::ostream& operator<< (std::ostream& cout, MoveDirection direction);

template<class ValueType>
void print(const Grid<ValueType>& grid);

};

namespace GA
{

char toChar(MoveDirection direction);

char toChar(Tile tileType);

char toChar(AlgoState algoState);

struct MaChar
{
	MaChar() : value{'-'} {}

	char value;

	MaChar(char value_) : value{value_} {}
	MaChar(Tile value_) : value{toChar(value_)} {}
	MaChar(MoveDirection value_) : value{toChar(value_)} {}
	MaChar(AlgoState value_) : value{toChar(value_)} {}
};

};

#include "glm/glm.hpp"

namespace GA
{
	struct Color;

	extern const Color
	Red,
	Green,
	Blue,
	Pink,
	Goluboy,
	Yellow,
	Orange,
	Black,
	White;

	Color toColor(MoveDirection direction);

	Color toColor(Tile tileType);

	Color toColor(AlgoState algoState);

	struct Color
	{
		glm::vec3 value;

		Color(float x, float y, float z) : value{x, y, z} {}
		Color(glm::vec3 value_) : value{value_} {}
		Color() : Color{Pink} {}

		Color(Tile value_) : Color{toColor(value_)} {}
		Color(MoveDirection value_) : Color{toColor(value_)} {}
		Color(AlgoState value_) : Color{toColor(value_)} {}
	};

	std::ostream& operator<< (std::ostream& cout, Color color);

	std::ostream& operator<< (std::ostream& cout, MaChar x);
};
