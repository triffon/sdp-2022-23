#include <iostream>
#include "CircularList.hpp"

class CircularTable
{
public:
	CircularTable( size_t size = 0 )
	{
		setKnights( size );
	}

	void setKnights( size_t count )
	{
		this->knights = {};
		for ( size_t i = 1; i <= count; ++i )
			knights.push_back( i );
	}

	size_t doGame();

private:
	dsa::CircularList<size_t> knights;
};

size_t CircularTable::doGame()
{
	dsa::CircularList<size_t>::iterator currentKnight = knights.begin();

	while ( knights.getSize() != 1 )
	{
		currentKnight = knights.removeAfter( currentKnight );
	}

	return knights.front();
}

int main()
{
	CircularTable table;
	table.setKnights( 12 );

	std::cout << "Winner is: " << table.doGame() << std::endl;

	return 0;
}
