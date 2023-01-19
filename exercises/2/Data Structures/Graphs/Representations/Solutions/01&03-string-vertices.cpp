// Sample solutions using an adjacent lists representation
// of a Graph with string vertices identifiers

#include <iostream>
#include <vector>
#include <set>
#include <map>

// Note: In this case to represent a vertex without any neighours
//       we have to insert a key with the vertex's identifier
//       without any elements in its adjacency list (vector)

using   GraphAdjLists   = std::map< std::string, std::vector< std::string > >;

bool hasEdge( const GraphAdjLists& graph, const std::string& from, const std::string& to ) // O(|E|*log|V|)
{
   // Note: GraphAdjLists can be implemented as a map<string, set<string>>
   //       then the time complexity will be O(log|E|*log|V|)

   auto    pair    = graph.find( from );   // finds in O(log|V|)

   if ( pair != graph.end() )
   {
       // we have a node with the identifier `from`
       // pair->first is the `from` (key) in the map
       // pair->second is the vector (value) in the map

       // runs in O(|E|) time
       for ( const std::string& neighbour : pair->second )
           if ( neighbour == to )
               return true;
   }

   return false;
}


void addEdgeOriented( GraphAdjLists& graph, const std::string& from, const std::string& to ) // O(|E|*log|V|)
{
   if ( ! hasEdge( graph, from, to ) )
       graph[ from ].push_back( to );
}


void addEdgeUnoriented( GraphAdjLists& graph, const std::string& from, const std::string& to ) // O(|E|*log|V|)
{
   addEdgeOriented( graph, from, to );
   addEdgeOriented( graph, to, from );
}


void DFSAndVisit( const GraphAdjLists& graph, const std::string& from, std::set<std::string>& visited )
{
   if ( visited.find( from ) != visited.end() )
       return;

   visited.insert( from );

   auto    pair    = graph.find( from );
   if ( pair != graph.end() )
   {
       for ( const std::string& neighbour : pair->second )
       {
           if ( visited.find( neighbour ) == visited.end() )
               DFSAndVisit( graph, neighbour, visited );
       }
   }
}


// Task 1 - Find the number of connected components in an undirected graph
size_t countComponents( const GraphAdjLists& graph )
{
   size_t count = 0;
   std::set<std::string> visited;

   for ( const auto& pair : graph )
   {
       // Note: pair->first is the key (each vertex)
       if ( visited.find( pair.first ) == visited.end() )
       {
           count++;
           DFSAndVisit( graph, pair.first, visited );
       }
   }

   return count;
}


bool hasCycleOrientedRec( const GraphAdjLists& graph, const std::string& vertex, std::set<std::string>& isVisited, std::set<std::string>& isInCurrentPath )
{
   if ( isInCurrentPath.find( vertex ) != isInCurrentPath.end() )
       return true;

   isInCurrentPath.insert( vertex );

   auto    pair    = graph.find( vertex );
   if ( pair != graph.end() )
   {
       for ( const std::string& neighbour : pair->second )
           if ( isVisited.find( neighbour ) == isVisited.end() )
               if ( hasCycleOrientedRec( graph, neighbour, isVisited, isInCurrentPath ) )
                   return true;
   }

   isVisited.insert( vertex );

   return false;
}


// Task 3 - Check if an oriented graph has a cycle
bool hasCycleOriented( const GraphAdjLists& graph )
{
   if ( graph.empty() )
       return false;

   std::set<std::string>   isVisited;
   std::set<std::string>   isInCurrentPath;

   const std::string&  startingVertex  = graph.begin()->first;
   // graph.begin() is an iterator to the first element in the map
   // ->first is its value (our vertex identifier)

   return hasCycleOrientedRec( graph, startingVertex, isVisited, isInCurrentPath);
}


int main()
{
   GraphAdjLists   graphUnoriented;
   
   {
       addEdgeUnoriented( graphUnoriented, "a", "b" );
       addEdgeUnoriented( graphUnoriented, "b", "c" );
       addEdgeUnoriented( graphUnoriented, "b", "d" );
       addEdgeUnoriented( graphUnoriented, "d", "e" );
       addEdgeUnoriented( graphUnoriented, "d", "g" );
       addEdgeUnoriented( graphUnoriented, "h", "d");
       addEdgeUnoriented( graphUnoriented, "d", "k" );
       addEdgeUnoriented( graphUnoriented, "g", "f" );
       addEdgeUnoriented( graphUnoriented, "g", "h" );
       addEdgeUnoriented( graphUnoriented, "h", "i" );
       addEdgeUnoriented( graphUnoriented, "k", "j" );

       addEdgeUnoriented( graphUnoriented, "l", "m");
       addEdgeUnoriented( graphUnoriented, "m", "n");

       // adds a key with no neighbours
       graphUnoriented.insert( { "o", {} } );

       addEdgeUnoriented( graphUnoriented, "p", "q");
       addEdgeUnoriented( graphUnoriented, "p", "r");
       addEdgeUnoriented( graphUnoriented, "q", "s");
       addEdgeUnoriented( graphUnoriented, "r", "s");
   }

   std::cout << "# of connected components: " << countComponents( graphUnoriented ) << "\n";


   GraphAdjLists   graphOriented;
   {
       addEdgeOriented( graphOriented, "0", "1" );
       addEdgeOriented( graphOriented, "1", "2" );
       addEdgeOriented( graphOriented, "1", "3" );
       addEdgeOriented( graphOriented, "3", "4" );
       addEdgeOriented( graphOriented, "3", "6" );
       addEdgeOriented( graphOriented, "7", "3" ); // Comment this line for a graph without a cycle
       addEdgeOriented( graphOriented, "3", "10" );
       addEdgeOriented( graphOriented, "6", "5" );
       addEdgeOriented( graphOriented, "6", "7" );
       addEdgeOriented( graphOriented, "7", "8" );
       addEdgeOriented( graphOriented, "10", "9" );
   }

   std::cout << "Has cycle: " << ( hasCycleOriented( graphOriented ) ? "Yes" : "No" ) << "\n";

   return 0;
}
