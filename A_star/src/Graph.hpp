#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

using ValueType = int;

struct Node
{
	ValueType value;

	Node(const ValueType& _value);

	Node();
};

Node::Node() : value{0} {}

class GridGraph
{
public:
 
	const size_t size;

	GridGraph(size_t _size);

	Node* operator[] (size_t row_id);  

	const Node* operator[] (size_t row_id) const;

private:

	Node* root;
};

GridGraph::GridGraph(size_t _size) : size{_size}, root{nullptr}
{
	try
	{
		root = new Node[size * size];
	}
	catch (std::bad_alloc& except)
	{
		std::cerr << "Cant allocate grid of size: " << size << std::endl;
	}
}

Node* GridGraph::operator[] (size_t row_id)
{
	return root + row_id * size;
}


const Node* GridGraph::operator[] (size_t row_id) const
{
	return root + row_id * size;
}

void print(const GridGraph& graph);

void print(const GridGraph& graph)
{
	for (size_t y = 0; y < graph.size; y++)
	{
		for (size_t x = 0; x < graph.size; x++)
		{
			std::cout << graph[y][x].value << ' ';
		}

		std::cout << '\n';
	}
}