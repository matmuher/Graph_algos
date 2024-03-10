#include "Shader.hpp"
#include "AStar.hpp"
#include "Grid.hpp"
#include "Point.hpp"
#include "Print.hpp"
#include "BufferPrinter.hpp"
#include "Heuristic.hpp"
#include "Drawing.hpp"

int main(int argc, const char* argv[])
{
// [Input Parameteres]

	const size_t GridSize = 20;
	const float QuadWidth = 2. / (GridSize);

	using namespace GA;

	Grid<Tile> map{GridSize};

	map.at({4, 0}) = Tile::Obstacle;
	map.at({4, 1}) = Tile::Obstacle;
	map.at({4, 2}) = Tile::Obstacle;
	map.at({4, 3}) = Tile::Obstacle;
	map.at({4, 4}) = Tile::Obstacle;

	map.at({6, 4}) = Tile::Obstacle;
	map.at({7, 4}) = Tile::Obstacle;
	map.at({8, 4}) = Tile::Obstacle;
	map.at({9, 4}) = Tile::Obstacle;

	Grid<int> tileCosts{GridSize, 1};

	GA::Point start{0, 0};
	GA::Point end{7, 0};

// [Init AStar]

	AStar astar{map, tileCosts};
	AStar::Heuristic heuristic = processCmd(argc, argv);
	astar.initSearch(start, end, heuristic);

// [Init Drawing]

	GLFW::ScopeGuard scopeGuard;
	GLFW::initOpenGL(3, 3);

	GLFW::Window window{800, 800, "Pathfinder"};	
	Grid<GA::Color> buffer{GridSize, White};
	GridDrawer drawer{GridSize};

	drawer.shader.use();
	drawer.shader.setFloat("QuadWidth", QuadWidth);
	drawer.shader.setInt("GridSize", GridSize);

// [Render Loop]

	while(!window.shouldClose())
	{

// [Process Events]

		int button = window.processInput();

		switch(button)
		{
			case GLFW_KEY_LEFT:

				astar.stepBack();
				break;

			case GLFW_KEY_RIGHT:

				astar.makeStep();
				break;

			default: ;
		}

// [Convert data to drawing format]

		buffer.fill(White);
		std::vector<Filler<GA::Color>> fillers;
		fillers.emplace_back(astar.resultPath(), MoveDirection::No);
		fillers.emplace_back(map, Tile::No);
		fillers.emplace_back(astar.state(), AlgoState::No);
		fillBuffer(buffer, fillers);

// [Draw]

		drawer.updateColors(&buffer[0][0]);
		drawer.drawGrid();

		window.swapBuffers();
		GLFW::pollEvents();
	}
}
