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
	char src, dest;
	int distance, cost;
	Edge( char _src, char _dest, int _distance, int _cost) : src(_src), dest(_dest), distance(_distance), cost(_cost) { }
};

// a structure to represent a connected, 
// undirected and weighted graph
class Graph
{
public:
	// V -> Number of vertices, E -> Number of edges
	int V, E;

	Graph( int _V, int _E ): V( _V ), E( _E ) {}


	// graph is represented as an array of edges.
	// Since the graph is undirected, the edge
	// from src to dest is also edge from dest
	// to src. Both are counted as 1 edge here.
	std::vector<Edge> edges;
};

// Creates a graph with V vertices and E edges
void createGraph( Graph& graph )
{

	// add edge A-B
	graph.edges.push_back( Edge( 'A', 'B', 40, 50 ) );

	// add edge A-H
	graph.edges.push_back( Edge( 'A', 'H', 80, 50 ) );

	// add edge B-H
	graph.edges.push_back( Edge( 'B', 'H', 110, 60 ) );

	// add edge B-C
	graph.edges.push_back( Edge( 'B', 'C', 80, 20 ) );

	// add edge H-I
	graph.edges.push_back( Edge( 'H', 'I', 70, 60 ) );

	// add edge H-G
	graph.edges.push_back( Edge( 'H', 'G', 10, 100 ) );

	// add edge C-I
	graph.edges.push_back( Edge( 'C', 'I', 20, 40 ) );

	// add edge I-G
	graph.edges.push_back( Edge( 'I', 'G', 60, 70 ) );

	// add edge G-F
	graph.edges.push_back( Edge( 'G', 'F', 20, 70 ) );

	// add edge C-F
	graph.edges.push_back( Edge( 'C', 'F', 40, 70 ) );

	// add edge C-D
	graph.edges.push_back( Edge( 'C', 'D', 70, 30 ) );

	// add edge D-F
	graph.edges.push_back( Edge( 'D', 'F', 140, 100 ) );

	// add edge D-E
	graph.edges.push_back( Edge( 'D', 'E', 90, 60 ) );

	// add edge F-E
	graph.edges.push_back( Edge( 'F', 'E', 100, 20 ) );
}

// The main function to construct MST using Kruskal's
// algorithm
void KruskalMST( Graph& graph )
{
	int V = graph.V;

	// Step 1: Sort all the edges in non-decreasing
	// order of their weight. If we are not allowed to
	// change the given graph, we can create a copy of
	// array of edges
	std::sort( graph.edges.begin(), graph.edges.end(),
		[&] ( const Edge& lhs, const Edge& rhs ) -> bool 
		{
			if ( lhs.cost == rhs.cost )
			{
				return lhs.distance <= rhs.distance;
			}
			return lhs.cost < rhs.cost;
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

	std::vector<Edge> result; // This will store the result MST
							  // Number of edges to be taken is equal to V-1
	while ( e < V - 1 && i < graph.E )
	{
		// Step 2: Pick the smallest edge. And increment
		// the index for next iteration
		Edge next_edge = graph.edges[ i++ ];

		int x = find( subsets, next_edge.src - 'A' );
		int y = find( subsets, next_edge.dest - 'A' );

		// If including this edge does't cause cycle,
		// include it in result and increment the index
		// of result for next edge
		if ( x != y )
		{
			result.push_back( next_edge );
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
		std::cout	<<	result[ i ].src << " -- " 
					<<	result[ i ].dest<< " == (" 
					<<	result[ i ].cost<< ", "
					<<	result[ i ].distance << ")"
					<< std::endl;
		minimumCost += result[ i ].cost;
	}
	std::cout << "Minimum Cost Spanning Tree: " << minimumCost << std::endl;
}

/*
int main()
{

	int V = 9; // Number of vertices in graph
	int E = 14; // Number of edges in graph

	Graph graph( V, E );
	createGraph( graph );

	KruskalMST( graph );

	return 0;
}
*/