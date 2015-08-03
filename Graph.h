#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "Vertex.h"

template <typename T>
class Graph
{
public:
	Graph()
	{
	}

	~Graph()
	{
	}

	void addVertex(Vertex<T> * newVertex);

	void addVertex(T value);

	Vertex<T> * getVertex(T value);

	void addEdge(Vertex<T> * originV, Vertex<T> * destinationV, int cost);
	void addEdge(T originValue, T destinationValue, int cost);

	void DFS(T startingVertex);	// print the vertices in depth-first fashion
	void BFS(T startingVertex); // print the vertices in breadth-first fashion
private:
	std::vector<Vertex<T>*> vertices;

	void clearAllVisits()
	{
		std::vector<Vertex<T>*>::iterator vi = vertices.begin();
		while (vi != vertices.end())
		{
			(*vi)->setVisited(false);
			vi++;
		}
	}
};

template <typename T>
void Graph<T>::addVertex(Vertex<T> * newVertex)
{
	// keep the values unique... ugh. 
	// need more efficient structure. tree?
	for (auto v : vertices)
	{
		if (v->getValue() == newVertex->getValue())
			return;
	}

	// add it to the collection of nodes
	vertices.push_back(newVertex);
}

template <typename T>
void Graph<T>::addVertex(T value)
{
	addVertex(new Vertex<T>(value));
}

template <typename T>
Vertex<T> * Graph<T>::getVertex(T value)
{
	for (auto v : vertices)
	{
		if (v->getValue() == value)
			return v;
	}
	//return nullptr; // interestingly, not needed
}

template <typename T>
void Graph<T>::addEdge(Vertex<T> * originV, Vertex<T> * destinationV, int cost)
{
	if (originV == nullptr || destinationV == nullptr)
		return; // no edges point to nowhere

	// The constructor of the edge does the adding of it to the vertices. ambitious
	new Edge<T>(originV, destinationV, cost);
}

template <typename T>
void Graph<T>::addEdge(T originValue, T destinationValue, int cost)
{
	addEdge(getVertex(originValue), getVertex(destinationValue), cost);
}

template <typename T>
void Graph<T>::DFS(T startingVertex)
{
	clearAllVisits();
	std::stack<Vertex<T>*> stack;
	Vertex<T> * current = getVertex(startingVertex);

	while (true)
	{
		// mark current vertex as visited
		current->setVisited(true);

		// print current vertex
		std::cout << current->getValue() << " ";
		
		// add current vertex to the stack
		stack.push(current);

		// add an unvisited neighbor to the stack
		std::vector<Vertex<T>*> neighbors = current->reachableNeighborsUnvisited();
		if (neighbors.size() > 0)
		{
			stack.push(neighbors[0]);
		}
		else
		{	// no adjacent unvisited vertices, so pop the stack and get the next vertex
			stack.pop();
		}

		if (stack.size() > 0)
		{
			current = stack.top();
		}
		else
			break;

	}
}

template <typename T>
void Graph<T>::BFS(T startingVertex)
{
	clearAllVisits();
	std::queue<Vertex<T>*> queue;
	Vertex<T> * current = getVertex(startingVertex);

	while (true)
	{
		// mark current vertex as visited
		current->setVisited(true);

		// print current vertex
		std::cout << current->getValue() << " ";

		// add reachable, unvisited neighbors to the queue
		std::vector<Vertex<T>*> neighbors = current->reachableNeighborsUnvisited();
		std::vector<Vertex<T>*>::iterator vi = neighbors.begin();
		while (vi != neighbors.end())
		{
			queue.push((*vi));
			vi++;
		}

		if (queue.size() > 0)
		{
			// get the oldest child in the queue
			current = queue.front();
			queue.pop();
		}
		else
			break;
	}

}