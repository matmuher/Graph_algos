#include "AStar.hpp"
#include "Grid.hpp"
#include "Point.hpp"
#include "Print.hpp"
#include "LayersPrinter.hpp"

#include <vector>

/*
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
	static int C = AStar::MaxCost / 2;

	C -= 1;
	return C; 
}
#pragma GCC diagnostic pop

int main()
{
	size_t size = 20; // read map

	Grid<Tile> map{size};

	map.at({4, 0}) = Tile::Obstacle;
	map.at({4, 1}) = Tile::Obstacle;
	map.at({4, 2}) = Tile::Obstacle;
	map.at({4, 3}) = Tile::Obstacle;
	map.at({4, 4}) = Tile::Obstacle;

	map.at({6, 4}) = Tile::Obstacle;
	map.at({7, 4}) = Tile::Obstacle;
	map.at({8, 4}) = Tile::Obstacle;
	map.at({9, 4}) = Tile::Obstacle;

	print(map);

	Grid<int> tileCosts{size, 1};

	Point start{0, 0};
	Point end{7, 0};

	try
	{
		std::vector<AStar::Heuristic> heuristics{	heuristicEuclidian,
													heuristicManhattan,
													heuristicBFS,
													heuristicDFS};

		AStar astar{map, tileCosts};

		for (AStar::Heuristic heuristic : heuristics)
		{
			astar.search(start, end, heuristic);
	
			Grid<MoveDirection> path = getPath(astar.moveDirections(), start, end);

			std::vector<const GridPrinter*> printers;

			TerminalPrinter pathPrinter{path};
			TerminalPrinter mapPrinter{map};
			TerminalPrinter statePrinter{astar.state()};

			printers.push_back(&mapPrinter);
			printers.push_back(&pathPrinter);
			printers.push_back(&statePrinter);

			drawLayers(size, printers);
		}
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid: " << except.what() << std::endl;
	}

	return 0;
}