#include <queue>
#include <iostream>
#include <array>
#include <limits>
#include <queue>
#include <cmath>
#include <functional>

#include "Graph.hpp"

// for obtaining algo info on every step
struct AStar
{
private:

	bool isInBoundaries(const Point& point)
	{
		return 	lessEqualThan(Zeros, point) &&
				lessThan(point, Point{size});
	}

	bool isUnprocessed(const Point& point)
	{
		return 	state.at(point) != AlgoState::Checked &&
				state.at(point) != AlgoState::InProgress;
	}

public:

	const int MaxCost = std::numeric_limits<int>::max();
	const int DefaultCost = 1;

// [Init Conditions]

	const size_t size;

	const Grid<Tile>& map;

	const Point& start;
	const Point& end;

	const std::function<int(Point point, int pointCost, Point end)> heuristic;

// [Temporal Resources] 

	Grid<AlgoState> state;

	Grid<Point> pathsToStart;
	
	Grid<int> tileCosts;
	Grid<int> pathCosts;

	std::priority_queue<WeightedPoint> weightedNextDoors;

	AStar(	const Grid<Tile>& _map,
			const Point& _start,
			const Point& _end,
			std::function<int(Point point, int pointCost, Point end)> _heuristic)
	:
		size{_map.size},

		map{_map},
		
		start{_start},
		end{_end},

		heuristic{_heuristic},

		state{size},

		pathsToStart{size},

		tileCosts{size, DefaultCost},
		pathCosts{size, MaxCost}
	{
		pathCosts.at(start) = 0;

		weightedNextDoors.emplace(start, pathCosts.at(start));
	}

	bool makeStep()
	{
		if (!weightedNextDoors.empty())
		{
			Point current = weightedNextDoors.top().point; // choose point with the least cost
			weightedNextDoors.pop();

			state.at(current) = AlgoState::Checked;

			if (current == end)
			{
				return false;
			}

			for (Point shift : shifts)
			{
				Point neighbour = current + shift;
				int neighbourProbableCost = pathCosts.at(current) +
											heuristic(neighbour, tileCosts.at(neighbour), end);

				if (isInBoundaries(neighbour) &&
					map.at(neighbour) != Tile::Obstacle &&
					isUnprocessed(neighbour) &&
					neighbourProbableCost < pathCosts.at(neighbour))
				{
					pathsToStart.at(neighbour) = current;
					state.at(neighbour) = AlgoState::InProgress;
					pathCosts.at(neighbour) = neighbourProbableCost;

					weightedNextDoors.emplace(neighbour, pathCosts.at(neighbour)); // how emplace works?
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	Grid<Point> search()
	{
		while(makeStep()) {;}
	}
};

Grid<Results> getResults(	const Grid<Point>& paths,
							const Point& start,
							const Point& finish)
{
	Grid<Results> results{paths.size};

	results.at(start) = Results::Path;
	results.at(finish) = Results::Path;

	Point currCell = paths.at(finish);
	
	while(currCell != start)
	{
		results.at(currCell) = Results::Path;

		Point prevCell = paths.at(currCell);

		currCell = prevCell;
	}

	return results;
}

int main()
{
	size_t size = 5; // read map

	Grid<Tile> map{size}; 	// it would be convinient to give list of neccessary layers
							// when craete grid. builder pattern?
	map.at({2, 0}) = Tile::Obstacle;

	Point start{0, 0};
	Point end{4, 0};

	auto heuristicManhattan = [](Point point, int pointCost, Point end)
									{
										return 	pointCost +
												distanceManhattan(point, end);
									};
	
	try
	{
		AStar astar{map, start, end, heuristicManhattan};

		while(astar.makeStep())
		{
			print(astar.state);
		}

		Grid<Results> results = getResults(astar.pathsToStart, start, end);

		print(results);
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid: " << except.what() << std::endl;
	}

	return 0;
}