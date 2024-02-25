#include "AStar.hpp"

AStar::AStar(	const Grid<Tile>& map,
				const Grid<int>& tileCosts,
				Point start,
				Point end,
				Heuristic heuristic)
:
	size_{map.size},

	map_{map},
	tileCosts_{tileCosts},
	
	state_{size_},
	pathsToStart_{size_},
	pathCosts_{size_}
{
	initSearch(start, end, heuristic);
}

bool AStar::makeStep()
{
	if (!isInit_)
	{
		throw "Algorithm is not initialized";
	}

	if (weightedNextDoors_.empty())
	{
		isInit_ = false;
		return false;
	}

	Point current = weightedNextDoors_.top().point; // choose point with the least cost
	weightedNextDoors_.pop();

	state_.at(current) = AlgoState::Checked;

	if (current == end_)
	{
		isInit_ = false;
		return false;
	}

	for (Point shift : shifts)
	{
		Point neighbour = current + shift;
		int neighbourProbableCost = pathCosts_.at(current) +
									heuristic_(neighbour, tileCosts_.at(neighbour), end_);

		if (isInBoundaries(neighbour) &&
			map_.at(neighbour) != Tile::Obstacle &&
			isUnprocessed(neighbour) &&
			neighbourProbableCost < pathCosts_.at(neighbour))
		{
			pathsToStart_.at(neighbour) = current;
			state_.at(neighbour) = AlgoState::InProgress;
			pathCosts_.at(neighbour) = neighbourProbableCost;

			weightedNextDoors_.emplace(neighbour, pathCosts_.at(neighbour)); // how emplace works?
		}
	}

	return true;
}

const Grid<AlgoState>& AStar::state() const
{
	return state_;
}

const Grid<Point>& AStar::pathsToStart() const
{
	return pathsToStart_;
}

const Grid<int>& AStar::pathCosts() const
{
	return pathCosts_;
}

bool AStar::isInBoundaries(const Point& point) const
{
	return 	lessEqualThan(Zeros, point) &&
			lessThan(point, Point{int(size_)});
}

bool AStar::isUnprocessed(const Point& point) const
{
	return 	state_.at(point) != AlgoState::Checked &&
			state_.at(point) != AlgoState::InProgress;
}

Grid<Point> AStar::search(Point start, Point end, Heuristic heuristic)
{
	initSearch(start, end, heuristic);
	while(makeStep()) {;}

	return pathsToStart_;
}

template<class T>
void clearQueue(std::priority_queue<T>& queue)
{
	std::priority_queue<T> empty;
	std::swap(empty, queue); 
}

void AStar::initSearch(Point start, Point end, Heuristic heuristic)
{
	start_ = start;
	end_ = end;
	heuristic_ = heuristic;

	state_.fill(AlgoState::Free);
	pathsToStart_.fill(PathPoison);
	pathCosts_.fill(MaxCost);

	pathCosts_.at(start_) = 0;

	clearQueue(weightedNextDoors_);
	weightedNextDoors_.emplace(start_, 0);

	isInit_ = true;
}

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
