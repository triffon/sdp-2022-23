// C++ program for Kruskal's algorithm
// to find Minimum Spanning Tree of a
// given connected, undirected and weighted
// graph

// Source: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

#include <iostream>
#include <vector>
#include <algorithm>
#include "Utility.h"

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


// The main function to construct MST using Kruskal's
// algorithm
void KruskalMST( Graph* graph )
{
	int V = graph->V;

	// Step 1: Sort all the edges in non-decreasing
	// order of their weight. If we are not allowed to
	// change the given graph, we can create a copy of
	// array of edges
	std::sort( graph->edges.begin(), graph->edges.end(),
		[&] ( const Edge& lhs, const Edge& rhs ) -> bool 
		{
			return lhs.weight < rhs.weight;
		}
	);

	// Allocate memory for creating V subsets
	std::vector<dsa::subset> subsets( V );

	// Create V subsets with single elements
	for ( int v = 0; v < V; ++v )
	{
		subsets[ v ].parent = v;
		subsets[ v ].rank = 0;
	}


	int e = 0; // An index variable, used for result[]
	int i = 0; // An index variable, used for sorted edges

	std::vector<Edge> resultTree; // This will store the result MST
	// Number of edges to be taken is equal to V-1
	while ( e < V - 1 && i < graph->E )
	{
		// Step 2: Pick the smallest edge. And increment
		// the index for next iteration
		Edge next_edge = graph->edges[ i++ ];

		int x = dsa::find( subsets, next_edge.v );
		int y = dsa::find( subsets, next_edge.u );

		// If including this edge does't cause cycle,
		// include it in result and increment the index
		// of result for next edge
		if ( x != y )
		{
			resultTree.push_back( next_edge );
			++e;
			Union( subsets, x, y );
		}
		// Else discard the next_edge
	}

	// print the contents of result[] to display the
	// built MST
	std::cout << "Following are the edges in the constructed MST\n";
	int minimumCost = 0;
	for ( i = 0; i < e; ++i )
	{
		std::cout	<<	resultTree[ i ].v	<< " -- " 
				<<	resultTree[ i ].u	<< " == " 
				<<	resultTree[ i ].weight << std::endl;
		minimumCost += resultTree[ i ].weight;
	}
	std::cout << "Minimum Cost Spanning Tree: " << minimumCost << std::endl;
}
/*
int main()
{
	int V = 9; // Number of vertices in graph
	int E = 14; // Number of edges in graph
	Graph* graph = new Graph( V, E );
	createGraph( graph );

	KruskalMST( graph );

	delete graph;
	return 0;
}
*/