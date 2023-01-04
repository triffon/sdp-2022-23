#include <stdio.h> // printf(), putchar()

/// graph matrix size
#define SIZE 6 
/// "no path" constant, should be maximum INT_MAX / 2
#define MAX 1000
/// helper marco for finding minimum of two numbers
#define min(x, y) ((x) < (y)) ? (x) : (y)

/// the graph is represented as weighing matrix
int graph[SIZE][SIZE] = {
	// vertex "to" :
	// A    B    C    D    E    F     // vertex "from" :
	{ MAX, MAX,   6,   2, MAX, MAX }, // A
	{ MAX, MAX, MAX,  -7, MAX, MAX }, // B
	{ MAX,   1, MAX, MAX, MAX, MAX }, // C
	{ MAX, MAX,  11, MAX, MAX, MAX }, // D
	{  15, MAX,  10, MAX, MAX,  -3 }, // E
	{ MAX,   5, MAX, MAX, MAX, MAX }  // F
};

/// the graph is represented as weighing matrix
int graph1[SIZE][SIZE] = {
	// vertex "to" :
	// A    B    C    D     E      F     // vertex "from" :
	{ MAX,	7 ,  6  ,  2  ,   9 ,  1  }, // A
	{ 7	 , MAX,  6  ,  1  ,  11 ,  3  }, // B
	{ 6  ,	6 , MAX ,  7  ,   2 ,  9  }, // C
	{ 2  , 1  ,  7  , MAX ,   5 , 10  }, // D
	{ 9  , 11 ,  2  ,  5  , MAX ,  1  }, // E
	{ 1  ,  3 ,  9  , 10  ,   1 , MAX }  // F
};