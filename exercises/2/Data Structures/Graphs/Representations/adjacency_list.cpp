#include<iostream>
#include<list>
#include<vector>
#include<set>
using namespace std; 

using Edge = pair < int, int >;
using Vertex = list< Edge >;
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
	int V; // No. of vertices 

	// In a weighted graph, we need to store vertex 
	// and weight pair for every edge 
	vector< Vertex > adj; 

public: 
	Graph( int V ): V( V )
	{
		for ( int i = 0; i < V; ++i ) adj.push_back( Vertex() );
	}
	// function to add an edge to graph 
	void addEdge(int u, int v, int w); 

}; 

void Graph::addEdge(int u, int v, int w) 
{ 
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
} 


// Driver program to test methods of graph class 
int main() 
{ 
	// create the graph given in above fugure 
	int V = 9; 
	Graph g(V); 

	// making above shown graph 
	g.addEdge(0, 1, 4); 
	g.addEdge(0, 7, 8); 
	g.addEdge(1, 2, 8); 
	g.addEdge(1, 7, 11); 
	g.addEdge(2, 3, 7); 
	g.addEdge(2, 8, 2); 
	g.addEdge(2, 5, 4); 
	g.addEdge(3, 4, 9); 
	g.addEdge(3, 5, 14); 
	g.addEdge(4, 5, 10); 
	g.addEdge(5, 6, 2); 
	g.addEdge(6, 7, 1); 
	g.addEdge(6, 8, 6); 
	g.addEdge(7, 8, 7); 

	return 0; 
} 