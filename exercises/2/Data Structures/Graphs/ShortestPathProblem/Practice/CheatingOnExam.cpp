// Program to find Dijkstra's shortest path using STL set 
#include<iostream>
#include<list>
#include<vector>
#include<set>
using namespace std; 
# define INF INT_MAX 

using Edge = pair < int, int >;
using Vertex = list< Edge >;
class Graph 
{ 
	int V;
	vector< Vertex > adj; 

public: 
	Graph( int V ): V( V )
	{
		for ( int i = 0; i < V; ++i ) adj.push_back( Vertex() );
	}
	void addEdge(int u, int v, int w); 

	void shortestPath(int s); 
}; 

void Graph::addEdge(int u, int v, int w) 
{ 
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
} 

void Graph::shortestPath( int src )
{
	set< int > setds;

	vector<int> dist( V, INF );

	setds.insert( src );
	dist[ src ] = 0;

	while ( !setds.empty() )
	{
		int u = *( setds.begin() );
		setds.erase( setds.begin() );

		for ( const Edge& e : adj[ u ] )
		{
			int v = e.first;
			int weight = e.second;

			if ( dist[ v ] > dist[ u ] + weight )
			{
				if ( dist[ v ] != INF )
					setds.erase( v );

				dist[ v ] = dist[ u ] + weight;
				setds.insert( v );
			}
		}
	}

	std::cout << "Vertex Distance from Source\n";
	for ( int i = 0; i < V; ++i )
		std::cout << i << "\t\t" <<  dist[i] << std::endl;
}

int main() 
{
	int V = 9; 
	Graph g(V); 

	g.addEdge(0, 1, 1); 
	g.addEdge(0, 7, 1); 
	g.addEdge(1, 2, 1); 
	g.addEdge(1, 7, 0); 
	g.addEdge(2, 3, 1); 
	g.addEdge(2, 8, 0); 
	g.addEdge(2, 5, 0); 
	g.addEdge(3, 4, 1); 
	g.addEdge(3, 5, 0); 
	g.addEdge(4, 5, 0); 
	g.addEdge(5, 6, 1); 
	g.addEdge(6, 7, 0); 
	g.addEdge(6, 8, 1); 
	g.addEdge(7, 8, 1); 

	g.shortestPath(0); 

	return 0; 
} 
