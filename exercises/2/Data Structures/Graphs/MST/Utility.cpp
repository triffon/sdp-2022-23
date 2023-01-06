#include "Utility.h"

namespace dsa
{
	// A utility function to find set of an element i
	// (uses path compression technique)
	int find( std::vector<subset>& subsets, int i )
	{
		// find root and make root as parent of i
		// (path compression)

		if ( subsets[ i ].parent != i )
		{
			subsets[ i ].parent = find( subsets, subsets[ i ].parent );
		}

		/* naive way to find root of the given node
		while ( subsets[ i ].parent != -1 )
		{
		i = subsets[ i ].parent;
		}
		*/
		return subsets[ i ].parent;
	}

	// A function that does union of two sets of x and y
	// (uses union by rank)
	void Union( std::vector<subset>& subsets, int x, int y )
	{

		int xroot = find( subsets, x );
		int yroot = find( subsets, y );
		// naive way to union two sets
		// subsets[ xroot ].parent = yroot;

		// Attach smaller rank tree under root of high
		// rank tree (Union by Rank)
		if ( subsets[ xroot ].rank < subsets[ yroot ].rank )
			subsets[ xroot ].parent = yroot;
		else if ( subsets[ xroot ].rank > subsets[ yroot ].rank )
			subsets[ yroot ].parent = xroot;

		// If ranks are equal, then make one as root and
		// increment its rank by one
		else
		{
			subsets[ yroot ].parent = xroot;
			subsets[ xroot ].rank++; //!!!!
		}
	}
}