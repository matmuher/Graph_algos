#pragma once

#include "Grid.hpp"
#include "Command.hpp"

#include <functional>
#include <queue>
#include <limits>

namespace GA
{

// for obtaining algo info on every step
struct AStar
{
public:

	using Heuristic = std::function<int(Point point, int pointCost, Point end)>;

	AStar(	const Grid<Tile>& map,
			const Grid<int>& tileCosts);

	AStar(	const Grid<Tile>& map,
			const Grid<int>& tileCosts,
			Point start,
			Point end,
			Heuristic heuristic);

// [Search]

	void initSearch(Point start, Point end, Heuristic heuristic);

	bool makeStep();
	bool stepBack();

	Grid<Point> search(Point start, Point end, Heuristic heuristic);

// [Getters]

	const Grid<AlgoState>& state() const;
	const Grid<Point>& pathsToStart() const;
	const Grid<int>& pathCosts() const;
	const Grid<MoveDirection>& moveDirections() const;
	const Grid<MoveDirection>& resultPath() const;

// [Consts]

	static constexpr int MaxCost = std::numeric_limits<int>::max();
	static constexpr int DefaultCost = 1;
	static const Point PathPoison;

private:

// [Init Conditions]

	const size_t size_;
	const Grid<Tile>& map_;
	const Grid<int>& tileCosts_;

// [Temporal Resources] 

	Grid<AlgoState> state_;
	Grid<Point> pathsToStart_;
	Grid<int> pathCosts_;
	Grid<MoveDirection> moveDirections_;
	Grid<MoveDirection> resultPath_;

	std::vector<Command> history;

// [Search params]

	Point start_;
	Point end_;

	Heuristic heuristic_;

	bool isInit_ = false;

// [Implementation]

	std::priority_queue<WeightedPoint> weightedNextDoors_;

// [Help functions]

	bool isInBoundaries(const Point& point) const;

	bool isUnprocessed(const Point& point) const;

	void dump() const;

	void setPath();
};

}
