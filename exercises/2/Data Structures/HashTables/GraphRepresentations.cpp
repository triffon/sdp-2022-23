#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <iostream>

/// vertices are characters
typedef char vertex;

/// weights are numbers
typedef int weight;

/// each edge is a tuple s_vertex : d_vertex : weight
using edge = std::tuple<vertex, vertex, weight>; 

struct Edge
{
	vertex src;
	vertex dest;
	weight w;
};

///-------------------------------------------------------------------------------------------------
///-------------------------------ADJACENT LIST-----------------------------------------------------
/// 

/// for each vertex we will have a list of it's edges to children
/// 
// find edge - O(|children_list|)
// add edge - O(1)
// remove edge - O(|children_list|)
using children_list = std::vector<edge>;

// find edge - O(|children_list|)
// add edge - O(1)
// remove edge - O(|children_list|) if we need to find it, O(1) if we have iterator to that edge
using children_list = std::list<edge>;

// find edge - O(log(|children_list|))
// add edge - O(log(|children_list|))
// remove edge - O(log(|children_list|))
using children_list = std::set<edge>;

// find edge - O(1)
// add edge - O(1)
// remove edge - O(1)
using children_list = std::unordered_set<edge>;

/// the graph is represented as a lists of adjacent for each vertex

// find vertex - O(log(|V|))
// add vertex - O(log(|V|))
// remove vertex - O(log(|V|))
using graph = std::map<vertex, children_list>;

// find vertex - O(1)
// add vertex - O(1)
// remove vertex - O(1)
using graph = std::unordered_map<vertex, children_list>;
///-------------------------------------------------------------------------------------------------

/**
* @brief Creates a graph with some edges.
* @retval the created graph
*/
graph InitGraphWithAdjacentList()
{
	edge	a2b( 'a', 'b', 9 ),
			a2c( 'a', 'c', 3 ),
			a2d( 'a', 'd', 5 ),
			b2e( 'b', 'e', 1 ),
			c2b( 'c', 'b', 2 ),
			c2d( 'c', 'd', 1 ),
			d2e( 'd', 'e', 7 ),
			e2a( 'e', 'a', 1 ),
			e2c( 'e', 'c', 6 );

	graph g;
	g[ 'a' ] = { a2b, a2c, a2d };
	g[ 'b' ] = { b2e };
	g[ 'c' ] = { c2b, c2d };
	g[ 'd' ] = { d2e };
	g[ 'e' ] = { e2a, e2c };
	return g;
}

/**
* @brief simply output a graphs contain
* @param[in] G: graph to be outputted
*/
void PrintGraph( const graph& G )
{

	for ( const std::pair<const vertex, children_list>& v_child : G )
	{
		std::cout << "from " << v_child.first  << " to : { ";
		for ( const edge& e : v_child.second )
		{
			std::cout << "( " << std::get<1>( e ) << ", " <<  std::get<2>( e )  << " )" ;
		}
		/*
		for ( const Edge& e : v_child.second )
		{
			std::cout << "( " <<  e.dest << ", " <<  e.w  << " )" ;
		}
		*/
		std::cout << "}" << std::endl;
	}

	std::cout << std::endl << std::endl;
}


///-------------------------------------------------------------------------------------------------
///-------------------------------ADJACENCY MATRIX--------------------------------------------------
/// 

using graphMatrix = std::vector<std::vector<weight>>;
using graphMatrix = std::unordered_map<vertex, std::unordered_map<vertex, weight>>;

graphMatrix InitGraphWithAdjacentMatrix()
{
	graphMatrix g;
	g[ 'a' ][ 'b' ] = 9;
	g[ 'a' ][ 'c' ] = 3;
	g[ 'a' ][ 'd' ] = 5;

	g[ 'b' ][ 'e' ] = 1;

	g[ 'c' ][ 'b' ] = 2;
	g[ 'c' ][ 'd' ] = 1;

	g[ 'd' ][ 'e' ] = 7;

	g[ 'e' ][ 'a' ] = 1;
	g[ 'e' ][ 'c' ] = 7;

	return g;
}


///-------------------------------------------------------------------------------------------------
///-------------------------------LIST OF EDGES-----------------------------------------------------
/// 
// find edge - O(|E|)
// add edge - O(1)
// remove edge - O(|E|)
// add vertex - just isolated vertex is not possible
// remove vertex - O(|E|*k)
using edgeList = std::vector<edge>;

// find edge - O(|E|)
// add edge - O(1)
// remove edge - O(|E|) if we need to find it, O(1) if we have iterator to that edge
// add vertex - just isolated vertex is not possible
// remove vertex - O(|E|*k)
using edgeList = std::list<edge>;


// find edge - O(log(|E|))
// add edge - O(log(|E|))
// remove edge - O(log(|E|))
// add vertex - just isolated vertex is not possible
// remove vertex - O(|E|)
using edgeList = std::set<edge>;

// find edge - O(1)
// add edge - O(1)
// remove edge - O(1)
// add vertex - just isolated vertex is not possible
// remove vertex - O(|E|)
using edgeList = std::unordered_set<edge>;





int main()
{
	graph G = InitGraphWithAdjacentList();
	std::cout << "\nthe given graph contains:"<< std::endl;
	PrintGraph( G );


	graphMatrix g = InitGraphWithAdjacentMatrix();

	return 0;
}