// A C++ program for Prim's Minimum 
// Spanning Tree (MST) algorithm. The program is 
// for adjacency matrix representation of the graph 

// Source: https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

#include <iostream> 
#include <limits>

// Number of vertices in the graph 
constexpr int	VERTICES_CNT	= 5;
constexpr int	INF				= std::numeric_limits<int>::max();


// A utility function to find the vertex with 
// minimum key value, from the set of vertices 
// not yet included in MST 
int minKeyIndex( int key[], bool mstSet[] )
{
	// Initialize min value 
	int	min_cost  = INF;
	int	min_index = -1;

	for ( int v = 0; v < VERTICES_CNT; v++ )
	{
		if ( mstSet[ v ] == false && key[ v ] < min_cost )
		{
			min_cost  = key[ v ];
			min_index = v;
		}
	}

	return min_index;
}


// A utility function to print the 
// constructed MST stored in parent[] 
void printMST( int parent[], int graph[ VERTICES_CNT ][ VERTICES_CNT ] )
{
	std::cout << "Edge \tWeight\n";
	for ( int i = 1; i < VERTICES_CNT; i++ )
		std::cout << parent[ i ] << " - " << i << " \t" << graph[ i ][ parent[ i ] ] << " \n";
}


// Function to construct and print MST for 
// a graph represented using adjacency 
// matrix representation
// Time complexity O(|V|^2)
void primMST( int graph[ VERTICES_CNT ][ VERTICES_CNT ] )
{
	// Array to store constructed MST 
	int parent[ VERTICES_CNT ];
	for ( int i = 0; i < VERTICES_CNT; i++ )
		parent[ i ] = -1;

	// Key values used to pick minimum weight edge in cut 
	int key[ VERTICES_CNT ];
	for ( int i = 0; i < VERTICES_CNT; i++ )
		key[ i ] = INF;

	// To represent set of vertices included in MST 
	bool mstSet[ VERTICES_CNT ] = { false, };

	// Always include first 1st vertex in MST. 
	// Make key 0 so that this vertex is picked as first vertex. 
	key[ 0 ] = 0;
	parent[ 0 ] = -1; // First node is always root of MST 

	// The MST will have V vertices 
	for ( int count = 0; count < VERTICES_CNT - 1; count++ )
	{
		// Pick the minimum key vertex from the 
		// set of vertices not yet included in MST 
		int u = minKeyIndex( key, mstSet );

		// Add the picked vertex to the MST Set 
		mstSet[ u ] = true;

		// Update key value and parent index of 
		// the adjacent vertices of the picked vertex. 
		// Consider only those vertices which are not 
		// yet included in MST 
		for ( int v = 0; v < VERTICES_CNT; v++ )

			// graph[u][v] is non zero only for adjacent vertices of m 
			// mstSet[v] is false for vertices not yet included in MST 
			// Update the key only if graph[u][v] is smaller than key[v] 
			if ( mstSet[ v ] == false && graph[ u ][ v ] < key[ v ] )
			{
				parent[ v ] = u;
				key[ v ] = graph[ u ][ v ];
			}
	}

	// print the constructed MST 
	printMST( parent, graph );
}


int main() 
{ 
	int graph[ VERTICES_CNT ][ VERTICES_CNT ] =
	{ 
		{ INF,  2 , INF,  6 , INF },
		{  2 , INF,  3 ,  8 ,  5  },
		{ INF,  3 , INF, INF,  7  },
		{  6 ,  8 , INF, INF,  9  },
		{ INF,  5 ,  7 ,  9 , INF },
	};

	// Print the solution 
	primMST( graph ); 

	return 0; 
}
