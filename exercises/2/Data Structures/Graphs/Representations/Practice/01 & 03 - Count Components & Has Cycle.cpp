#include <iostream>
#include <vector>
#include <forward_list>
#include <set>

using GraphAdjLists = std::vector<std::forward_list<size_t>>;

bool hasEdge( const GraphAdjLists& graph, size_t from, size_t to ) // O(|E|)
{
    for ( size_t neighbour : graph[ from ] )
        if ( neighbour == to )
            return true;

    return false;
}


void addEdgeOriented( GraphAdjLists& graph, size_t from, size_t to ) // O(|E|)
{
    if ( !hasEdge( graph, from, to ) )
        graph[ from ].push_front( to );
}


void addEdgeUnoriented( GraphAdjLists& graph, size_t from, size_t to ) // O(|E|)
{
    addEdgeOriented( graph, from, to );
    addEdgeOriented( graph, to, from );
}


void DFSAndRemoveVisited( const GraphAdjLists& graph, size_t from, std::set<size_t>& vertices )
{
    vertices.erase( from );

    for ( size_t neighbour : graph[ from ] )
        if ( vertices.find( neighbour ) != vertices.end() )
            DFSAndRemoveVisited( graph, neighbour, vertices );
}


// Task 1 - Find the number of connected components in an undirected graph
size_t countComponents( const GraphAdjLists& graph )
{
    size_t count = 0;
    std::set<size_t> vertices;

    for ( size_t i = 0; i < graph.size(); i++ )
        vertices.insert( i );

    for ( ; !vertices.empty(); count++ )
        DFSAndRemoveVisited( graph, *vertices.begin(), vertices );

    return count;
}


bool hasCycleOrientedRec( const GraphAdjLists& graph, size_t vertex, std::vector<bool>& isVisited, std::vector<bool>& isCurrent )
{
    if ( isCurrent[ vertex ] )
        return true;
    
    isCurrent[ vertex ] = true;

    for ( size_t neighbour : graph[ vertex ] )
        if ( !isVisited[ neighbour ] )
            if ( hasCycleOrientedRec( graph, neighbour, isVisited, isCurrent ) )
                return true;

    isVisited[ vertex ] = true;
    return false;
}


// Task 3 - Check if an oriented graph has a cycle
bool hasCycleOriented( const GraphAdjLists& graph )
{
    std::vector<bool> isVisited, isCurrent;
    isVisited.resize( graph.size(), false );
    isCurrent.resize( graph.size(), false );
    return hasCycleOrientedRec( graph, 0, isVisited, isCurrent );
}


int main()
{
    GraphAdjLists graphUnoriented, graphOriented;

    graphUnoriented.resize( 19 );
    {
        addEdgeUnoriented( graphUnoriented, 0, 1 );
        addEdgeUnoriented( graphUnoriented, 1, 2 );
        addEdgeUnoriented( graphUnoriented, 1, 3 );
        addEdgeUnoriented( graphUnoriented, 3, 4 );
        addEdgeUnoriented( graphUnoriented, 3, 6 );
        addEdgeUnoriented( graphUnoriented, 7, 3 );
        addEdgeUnoriented( graphUnoriented, 3, 10 );
        addEdgeUnoriented( graphUnoriented, 6, 5 );
        addEdgeUnoriented( graphUnoriented, 6, 7 );
        addEdgeUnoriented( graphUnoriented, 7, 8 );
        addEdgeUnoriented( graphUnoriented, 10, 9 );

        addEdgeUnoriented( graphUnoriented, 11, 12 );
        addEdgeUnoriented( graphUnoriented, 12, 13 );

        addEdgeUnoriented( graphUnoriented, 15, 16 );
        addEdgeUnoriented( graphUnoriented, 15, 17 );
        addEdgeUnoriented( graphUnoriented, 16, 18 );
        addEdgeUnoriented( graphUnoriented, 17, 18 );
    }

    std::cout << "# of connected components: " << countComponents( graphUnoriented ) << "\n";

    graphOriented.resize( 11 );
    {
        addEdgeOriented( graphOriented, 0, 1 );
        addEdgeOriented( graphOriented, 1, 2 );
        addEdgeOriented( graphOriented, 1, 3 );
        addEdgeOriented( graphOriented, 3, 4 );
        addEdgeOriented( graphOriented, 3, 6 );
        addEdgeOriented( graphOriented, 7, 3 ); // Change with ( 3, 7 ) for a graph without a cycle
        addEdgeOriented( graphOriented, 3, 10 );
        addEdgeOriented( graphOriented, 6, 5 );
        addEdgeOriented( graphOriented, 6, 7 );
        addEdgeOriented( graphOriented, 7, 8 );
        addEdgeOriented( graphOriented, 10, 9 );
    }

    std::cout << "Has cycle: " << ( hasCycleOriented( graphOriented ) ? "Yes" : "No" ) << "\n";

    return 0;
}
