#pragma once

template <typename T>
class Vertex;

template <typename T>
class Edge
{
public:
	Edge(Vertex<T> * origin, Vertex<T> * dest, int costp)
	{
		this->source = origin;
		this->destination = dest;
		this->cost = costp;

		// add the edge to the vertices automatically
		if (origin != nullptr)
			origin->outgoing.push_back(this);
		if (dest != nullptr)
			destination->incoming.push_back(this);
	}

	~Edge()
	{
	}

	int getCost() { return cost; }

	Vertex<T> * getSourceVertex()
	{
		Vertex<T> * r = source;
		return r;
	}

	Vertex<T> * getDestinationVertex()
	{
		Vertex<T> * r = destination;
		return r;
	}

private:
	int cost;
	Vertex<T> * source;
	Vertex<T> * destination;
};
