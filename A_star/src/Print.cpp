#include "Print.hpp"
#include "Point.hpp"

#include <iomanip>

namespace GA
{


std::istream& operator>> (std::istream& cin, Point& point)
{
	cin >> point.x >> point.y;
}

std::ostream& operator<<(std::ostream& cout, MaChar maChar)
{
	return cout << maChar.value;
}

#define ASS(enumVal, ...) 		\
			case enumVal:			\
				return __VA_ARGS__;			\
				break;				\

#define COUT(type)											\
std::ostream& operator<< (std::ostream& cout, type val)		\
{															\
	return cout << toChar(val);								\
}

char toChar(Tile tileType)
{
	using enum Tile;

	switch(tileType)
	{
		ASS(Obstacle, 'X')
		ASS(No, '-')
	}

	return 'F';
}
COUT(Tile);

char toChar(AlgoState algoState)
{
	using enum AlgoState;

	switch(algoState)
	{
		ASS(Checked, '@')
		ASS(InProgress, '*')
		ASS(No, '-')
	}

	return 'F';
}
COUT(AlgoState);

char toChar(MoveDirection direction)
{
	using enum MoveDirection;

	switch(direction)
	{
		ASS(Up, 	'^')
		ASS(Down, 	'v')
		ASS(Left, 	'<')
		ASS(Right, 	'>')
		ASS(No, 	'-')
	}

	return 'F';
}
COUT(MoveDirection);


Color toColor(MoveDirection direction)
{
	using enum MoveDirection;

	switch(direction)
	{
		ASS(Up, 	Blue)
		ASS(Down, 	Blue)
		ASS(Left, 	Blue)
		ASS(Right,  Blue)
		ASS(Start, 	Green)
		ASS(End,  	Green)
		ASS(No, 	Pink)
	}

	return Pink;
}

Color toColor(Tile tileType)
{
	using enum Tile;

	switch(tileType)
	{
		ASS(Obstacle, Black)
		ASS(No, Pink)
	}

	return Pink;
}


Color toColor(AlgoState algoState)
{
	using enum AlgoState;

	switch(algoState)
	{
		ASS(Checked, Red)
		ASS(InProgress, Yellow)
		ASS(No, Pink)
	}

	return Pink;
}

#undef COUT
#undef ASS


std::ostream& operator<< (std::ostream& cout, Color color)
{
	return cout << 	color.value.x << ' ' <<
					color.value.y << ' ' <<
					color.value.z << ' ';	
}

template<class ValueType>
void print(const Grid<ValueType>& grid)
{
	// system("clear");

	for (int y = int(grid.size) - 1; y >= 0; y--)
	{
		for (int x = 0; x < int(grid.size); x++)
		{
			std::cout << grid[y][x] << ' ';
		}

		std::cout << '\n';
	}

	std::cin.get();
}

// For compiller to know which version to generate
template void print<int>(const Grid<int>& graph);
template void print<Point>(const Grid<Point>& graph);
template void print<AlgoState>(const Grid<AlgoState>& graph);
template void print<Tile>(const Grid<Tile>& graph);
template void print<MoveDirection>(const Grid<MoveDirection>& graph);
template void print<char>(const Grid<char>& graph);
template void print<MaChar>(const Grid<MaChar>& graph);

const Color
	Red{1., 0., 0.},
	Green{0., 1., 0.},
	Blue{0., 0., 1.},
	Pink{1., 0., 1.},
	Goluboy{0., 1., 1.},
	Yellow{1., 1., 0.},
	Orange{1., 0.5, 0.},
	Black{0., 0., 0.},
	White{1., 1., 1.};
};