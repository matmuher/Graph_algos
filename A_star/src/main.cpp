#include "AStar.hpp"
#include "Grid.hpp"
#include "Point.hpp"
#include "Print.hpp"
#include "LayersPrinter.hpp"

#include <vector>

/*
	Add text description?

	Add Drawing?
	Add UI?
	Add reversing of actions?
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

// #include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GLFW
{
	struct ScopeGuard
	{
		ScopeGuard()
		{
			glfwInit();
		}

		~ScopeGuard()
		{
			glfwTerminate();	
		}
	};

	static void initOpenGL(int versionMajor, int versionMinor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	struct Window
	{
		GLFWwindow* window = nullptr;

		Window(int width, int height, const char* title)
		{
			window = glfwCreateWindow(width, height, title, NULL, NULL);
		
			if (!window)
			{
				throw "Cant create glfw window";
			}
		}

		void makeContextCurrent()
		{
			glfwMakeContextCurrent(window);
		}

		bool shouldClose()
		{
			return glfwWindowShouldClose(window);
		}

		void swapBuffers()
		{
			glfwSwapBuffers(window);
		}
	};

	void pollEvents()
	{
		glfwPollEvents();
	}
}

int main()
{
	GLFW::ScopeGuard scopeGuard;

	GLFW::initOpenGL(3, 3);

	const int Width = 800;
	const int Height = 800;
	const char* Title = "Pathfinder";

	GLFW::Window window{Width, Height, Title};

	window.makeContextCurrent();

	while(!window.shouldClose())
	{
		window.swapBuffers();
		GLFW::pollEvents();
	}
}

int main1()
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