#include "Print.hpp"
#include "Point.hpp"

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

// For compiller to know which version to generate
template void print<int>(const Grid<int>& graph);
template void print<Point>(const Grid<Point>& graph);
template void print<AlgoState>(const Grid<AlgoState>& graph);
template void print<Tile>(const Grid<Tile>& graph);
template void print<Results>(const Grid<Results>& graph);
