#include "AStar.hpp"
#include "Grid.hpp"
#include "Point.hpp"
#include "Print.hpp"

#include <vector>

/*
	Make it clearer how I save path (new struct?)

	Make text description

	Add Drawing?
	Add UI?
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int heuristicManhattan (Point point, int pointCost, Point end)
{
	return 	pointCost +
			distanceManhattan(point, end);
};

int heuristicEuclidian (Point point, int pointCost, Point end)
{
	return 	pointCost +
			distanceEuclidian(point, end);
};

int heuristicBFS (Point point, int pointCost, Point end)
{
	return 0; // all neighbours are equal: priority queue -> queue
}

int heuristicDFS (Point point, int pointCost, Point end)
{
	static int C = std::numeric_limits<int>::max();

	C -= 1;
	return C; 
}
#pragma GCC diagnostic pop

int main()
{
	size_t size = 10; // read map

	Grid<Tile> map{size};

	map.at({4, 0}) = Tile::Obstacle;
	map.at({4, 1}) = Tile::Obstacle;
	map.at({4, 2}) = Tile::Obstacle;
	map.at({4, 3}) = Tile::Obstacle;
	map.at({4, 4}) = Tile::Obstacle;

	// map.at({1, 4}) = Tile::Obstacle;
	// map.at({2, 4}) = Tile::Obstacle;
	// map.at({3, 4}) = Tile::Obstacle;
	// map.at({4, 4}) = Tile::Obstacle;

	print(map);

	Grid<int> tileCosts{size, 1};

	Point start{0, 0};
	Point end{6, 0};

	try
	{
		std::vector<AStar::Heuristic> heuristics{	heuristicBFS,
													heuristicDFS};

		AStar astar{map, tileCosts};

		for (AStar::Heuristic heuristic : heuristics)
		{
			astar.search(start, end, heuristic);

			printPath(astar.moveDirections(), start, end);
		}
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid: " << except.what() << std::endl;
	}

	return 0;
}