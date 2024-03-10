#pragma once

#include "Point.hpp"

#include <cstring>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace GA
{

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
	static int C = 0;
	C += 1;
	return C; // all neighbours are equal: priority queue -> queue
}

int heuristicDFS (Point point, int pointCost, Point end)
{
	static int C = AStar::MaxCost / 2;

	C -= 1;
	return C; 
}
#pragma GCC diagnostic pop


bool are_equal(const char* lhs, const char* rhs)
{
	return strcmp(lhs, rhs) == 0;
}

AStar::Heuristic processCmd(int argc, const char* argv[])
{
	if (argc < 2)
	{
		std::cout 	<< "Please, specify flags to choose heuristic:\n"
					<< "\t-dfs\n"
					<< "\t-bfs\n" 
					<< "\t-euc\n"
					<< "\t-man\n";

		throw "Unspecified flag";
	}

	if(are_equal(argv[1], "-dfs"))
	{
		return heuristicDFS;
	}
	else if (are_equal(argv[1], "-bfs"))
	{
		return heuristicBFS;
	}
	else if (are_equal(argv[1], "-euc"))
	{
		return heuristicEuclidian;
	}
	else if (are_equal(argv[1], "-man"))
	{
		return heuristicManhattan;
	}
	else
	{
		std::cout << argv[1] << ": unrecognised flag\n";
		return heuristicBFS;
	}
}
};
