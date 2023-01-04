#include <iostream>
#include <vector>
#include <algorithm>

// a structure to represent a 
// weighted edge in graph
struct Edge
{
	int v, u, weight;
	Edge( int _v, int _u, int _weight): v(_v), u(_u), weight(_weight){ }
};
/*
bool operator<( const Edge& lhs, const Edge& rhs )
{
return lhs.weight < rhs.weight;
}
*/


// a structure to represent a connected, 
// undirected and weighted graph
struct Graph
{
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	Graph( int _V, int _E ): V( _V ), E( _E ) {}


	// graph is represented as an array of edges.
	// Since the graph is undirected, the edge
	// from src to dest is also edge from dest
	// to src. Both are counted as 1 edge here.
	std::vector<Edge> edges;
};

// Creates a graph with V vertices and E edges
void createGraph( Graph* graph )
{
	// add edge 0-1
	graph->edges.push_back( Edge( 0, 1, 4 ) );

	// add edge 0-7
	graph->edges.push_back( Edge( 0, 7, 8 ) );

	// add edge 1-7
	graph->edges.push_back( Edge( 1, 7, 11 ) );

	// add edge 1-2
	graph->edges.push_back( Edge( 1, 2, 8 ) );

	// add edge 7-8
	graph->edges.push_back( Edge( 7, 8, 7 ) );

	// add edge 7-6
	graph->edges.push_back( Edge( 7, 6, 1 ) );

	// add edge 2-8
	graph->edges.push_back( Edge( 2, 8, 2 ) );

	// add edge 8-6
	graph->edges.push_back( Edge( 8, 6, 6 ) );

	// add edge 6-5
	graph->edges.push_back( Edge( 6, 5, 2 ) );

	// add edge 2-5
	graph->edges.push_back( Edge( 2, 5, 4 ) );

	// add edge 2-3
	graph->edges.push_back( Edge( 2, 3, 7 ) );

	// add edge 3-5
	graph->edges.push_back( Edge( 3, 5, 14 ) );

	// add edge 3-4
	graph->edges.push_back( Edge( 3, 4, 9 ) );

	// add edge 5-4
	graph->edges.push_back( Edge( 5, 4, 10 ) );
}


int main()
{
	int V = 9; // Number of vertices in graph
	int E = 14; // Number of edges in graph
	Graph* graph = new Graph( V, E );
	createGraph( graph );
	delete graph;
	return 0;
}
