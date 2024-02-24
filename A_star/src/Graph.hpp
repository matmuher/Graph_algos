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

	Node& operator= (const ValueType& _value);
};

Node::Node() : value{0} {}


Node::Node(const ValueType& _value) : value{_value} {};


Node& Node::operator= (const ValueType& _value)
{
	value = _value;
	return *this;
}

class Grid
{
public:
 
	const size_t size;

	Grid(size_t _size);

	Node* operator[] (int row_id);  

	const Node* operator[] (int row_id) const;

private:

	Node* root;
};

Grid::Grid(size_t _size) : size{_size}, root{nullptr}
{
	root = new Node[size * size];
}

Node* Grid::operator[] (int row_id)
{
	return root + row_id * size;
}


const Node* Grid::operator[] (int row_id) const
{
	return root + row_id * size;
}

void print(const Grid& graph)
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

/*
	Path - sequence of nodes, that lead you
	from node0 to nodeTarget
*/

struct Path
{
public:



private:

	std::vector<Node*> j;
};