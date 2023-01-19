/*******************************************************************************
* This file is part of the "Data structures and algorithms" course. FMI 2018/19 
*******************************************************************************/

/**
* @file   bellman-ford_spp.cpp
* @author Ivan Filipov
* @date   01.2019
* @brief  Finding the shortest path from a starting vertex to all others, using Bellman-Ford's algorithm.
*
* @see https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
* @note Written in plain C.
*
* Difference from Dijkstra - edges can also have negative weights.
* Also finds out if the graph contains negative cycle.
*/

#include <stdio.h>   // printf(), putchar()
#include <stdbool.h> // bool
#include <climits>
/// graph matrix size
#define SIZE 6 
#define MAX INT_MAX
#define min(x, y) ((x) < (y)) ? (x) : (y)

int graphMap[SIZE][SIZE] = {
	// vertex "to" :
	// A    B    C    D    E    F     // vertex "from" :
	{ MAX, MAX,   6,   2, MAX, MAX }, // A
	{ MAX, MAX, MAX,  -7, MAX, MAX }, // B
	{ MAX,   1, MAX, MAX, MAX, MAX }, // C
	{ MAX, MAX,  11, MAX, MAX, MAX }, // D
	{  15, MAX,  10, MAX, MAX,  -3 }, // E
	{ MAX,   5, MAX, MAX, MAX, MAX }  // F
};

void print_paths(int v_begin, int dist_vector[]) {

	printf("\nfrom %c to:\n", 'A' + v_begin);

	for (int i = 0; i < SIZE; i++) {
		if (v_begin == i) continue;

		printf("\t%c ", 'A' + i);

		if (dist_vector[i] == MAX)
			printf("no such path!\n");
		else
			printf(" weight %d\n", dist_vector[i]);
	}
}

bool find_negative_cycle(int dist_vector[]) {

	for (int i = 0; i < SIZE; i++)
		for (int j = i; j < SIZE; j++) {
			if (graphMap[j][i] == MAX || dist_vector[j] == MAX) continue;
			if (dist_vector[i] > dist_vector[j] + graphMap[j][i])
				return true;
		}

	return false;
}

/**
* @brief Runs Bellman-Ford's algorithm in the given graph.
*/
void ford_shortest_paths( int v_begin )
{
	int dist_vector[ SIZE ];
	for ( int i = 0; i < SIZE; i++ )
		dist_vector[ i ] = graphMap[ v_begin ][ i ];

	// for each vertex between i and j 
	for ( size_t k = 0; k < SIZE ; k++ )
	{
		for ( size_t i = 0; i < SIZE; i++ )
		{
			for ( size_t j = 0; j < SIZE; j++ )
			{
				if ( i == j ) continue;

				if ( graphMap[ j ][ i ] == MAX || dist_vector[ j ] == MAX ) continue;
				
				if ( dist_vector[ i ] > dist_vector[ j ] + graphMap[ j ][ i ] )
					dist_vector[ i ] = dist_vector[ j ] + graphMap[ j ][ i ];
			}
		}
	}

	if ( find_negative_cycle( dist_vector ) )
		printf( "\nthe given graph contains a negative loop!\n" );
	else
		print_paths( v_begin, dist_vector );
}

int main() {

	// run the algorithm from 'B' 
	int v_begin = 1;
	ford_shortest_paths(v_begin);
	
	// run the algorithm from 'E'
	v_begin = 4; // 'E'
	ford_shortest_paths(v_begin);
	
	// change the graph a bit, and run the algorithm again 
	printf("\nmodifying the graph to create a negative loop...\n");
	// for better understanding see the graph's visual representation
	graphMap['D' - 'A']['C' - 'A'] = -11; 
	ford_shortest_paths(v_begin);
	
	return 0;
}
