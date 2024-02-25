#include "AStar.hpp"
#include "Grid.hpp"
#include "Point.hpp"

int heuristicManhattan (Point point, int pointCost, Point end)
{
	return 	pointCost +
			distanceManhattan(point, end);
};

int main()
{
	size_t size = 5; // read map

	Grid<Tile> map{size}; 	// it would be convinient to give list of neccessary layers
							// when craete grid. builder pattern?
	map.at({2, 0}) = Tile::Obstacle;

	Grid<int> tileCosts{size, 1};
	print(tileCosts);

	Point start{0, 0};
	Point end{4, 0};

	try
	{
		AStar astar{map, tileCosts, start, end, heuristicManhattan};

		while(astar.makeStep())
		{
			print(astar.state());
		}

		Grid<Results> results = getResults(astar.pathsToStart(), start, end);

		print(results);
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid: " << except.what() << std::endl;
	}

	return 0;
}