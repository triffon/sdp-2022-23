
#include <iostream>
#include <vector>
#include <algorithm>

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

int main()
{
	int V = 9; // Number of vertices in graph
	int E = 14; // Number of edges in graph
	Graph graph( V, E );
	createGraph( graph );
	return 0;
}