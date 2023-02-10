//В града Имеяд могат да бъдат наблюдавани интересни явления. Целият град е съставен от множество обекти, които могат да бъдат посетени 
//(мислете си за кино, мол, бръснар). За съжаление, при всяко преминаване от един обект до друг се заплаща сурова цена – първата буква от името на човек!
//За всеки един обект знаем до кои други обекти можем да стигнем и с коя специфична буква става това; съответно този преход може да направи само човек,
//чието текущо (може би вече съкратено) име започва с тази буква. Например ако знаем, че от банка се стига до мол с буква ‘а’,
//то ana ще може да премине, но liana няма да може.

//Програмата ви ще получи информация за обектите в града и име на човек (поредица от малки латински букви).
//След това тя трябва да отговори кои са всички най-отдалечени обекти до които може да достигне човекът.

//Информацията за обектите ще се съхранява във файл, който ще се подаде на програмата. Първият ред в него съдържа името на обекта,
//който се намира на входа на града (всички хора тръгват от него). Всички останали редове описват преходите между обектите. Те са в следния формат:

//<начало> <край> <буква>
//Под най-отдалечени обекти разбираме тези, които могат да се достигнат с най-големия възможен брой преходи, тръгвайки от началния обект.
//Те ще варират в зависимост от името на човека, който е дошъл в града. Веднъж достигнал тези обекти,
//той/тя или ще е изчерпал всички букви в името си, или няма да може да отиде в никой друг обект с оставащите букви.

//Уточнения: 	* На входа на програмата ще се подадат път до файл описващ обекти и име на човек;
//		* Буквите в преходите и имената са само малки латински;
//		* Не са възможни зацикляния измежду обектите (в графа няма цикли);
//		* Ако от обект A можем да стигнем до обект B с буква 'c', то не е задължително вярно, че от B можем да стигнем до A със 'c';
//		* След всеки преход от едно място до друго, името, което сте получили като вход се намалява с буквата, която сте заплатили.
//			Ако от A отиваме в B с ‘a’,то името ani би станало – ni.


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
