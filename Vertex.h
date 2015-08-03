#pragma once

#include <vector>
#include <unordered_map>
#include "Edge.h"

template <typename T>
class Vertex
{
public:
	Vertex(T v)
	{
		this->value = v;
		this->visited = false;
	}

	~Vertex()
	{

	}

	T getValue() { return value; }
	bool getVisited() { return visited; }
	void setVisited(bool v)
	{
		visited = v;
	}
	std::vector<Vertex<T>*> & reachableNeighbors()
	{
		return getNeighbors(false);
	}
	std::vector<Vertex<T>*> & reachableNeighborsUnvisited()
	{
		return getNeighbors(true);
	}

private:
	T value;
	bool visited;
	std::vector<Edge<T>*> incoming;
	std::vector<Edge<T>*> outgoing;

	/*
	* Get the neighbors that this vertex can reach (via outgoing edges)
	*/
	std::vector<Vertex<T>*> & getNeighbors(bool onlyUnvisitedNeighbors);
};




template <typename T>
std::vector<Vertex<T>*> & Vertex<T>::getNeighbors(bool onlyUnvisitedNeighbors)
{
	std::vector<Vertex<T>*> * nlist = new std::vector<Vertex<T>*>();

	// get all of the outgoing edges' other vertex
	std::vector<Edge<T>*>::iterator vi = outgoing.begin();
	while (vi != outgoing.end())
	{
		Edge<T> * a = (*vi);
		if (onlyUnvisitedNeighbors)
		{
			// only add the neighbors with visited values of false
			if (a->getDestinationVertex()->getVisited() == false)
				nlist->push_back(a->getDestinationVertex());
		}
		else
		{	// add all neighbors
			nlist->push_back(a->getDestinationVertex());
		}
		vi++;
	}

	return * nlist;
}