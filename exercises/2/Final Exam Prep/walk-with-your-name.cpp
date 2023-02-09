#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using Graph = std::unordered_map< std::string, std::unordered_map<char, std::string>>;

void ReadCity( const std::string& filename, Graph& city, std::string& start_point )
{
	// prepare a file to read
	std::ifstream file_info( filename );
	if ( file_info.good() )
	{
		file_info >> start_point;

		std::string start_edge;
		std::string end_edge;
		char edge_value;
		while ( file_info.good() )
		{
			file_info >> start_edge;
			file_info >> end_edge;
			file_info >> edge_value;
			
			const auto& point_it = city.find( start_edge );
			if ( point_it == city.end() )
			{
				city.insert( { start_edge, {} } );
			}
			
			city[ start_edge ].insert( { edge_value, end_edge } );
		}
	}
}

void FindAllPaths( std::string name, std::string start_point,
	const Graph& city )
{

	const auto& point_it = city.find( start_point );
	if ( point_it != city.end() && !name.empty() )
	{
		bool found_path = false;
		for ( auto& edge : point_it->second )
		{
			if ( name[ 0 ] == edge.first )
			{
				found_path = true;
				FindAllPaths( name.substr( 1 ), edge.second, city );
			}
		}
		if ( !found_path )
		{
			std::cout << start_point << std::endl;
		}
	}
	else
	{
		std::cout << start_point << std::endl;
	}
}


int main()
{
	Graph city;
	std::string start_point;

	ReadCity( "test.txt", city, start_point );

	std::cout << start_point << std::endl;
	std::string name;
	std::cout << "Give me your name and I will take you whatever you want!!!" << std::endl;
	std::cin >> name;

	FindAllPaths( name, start_point, city );

	return 0;
}