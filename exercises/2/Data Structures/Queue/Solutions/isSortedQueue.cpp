#include "TemplateQueue.hpp"

enum class SeqType
{
	ASCENDING,
	DESCENDING,
	NEITHER
};

template <typename T>
bool isSorted( dsa::TemplateQueue<T>& Q )
{
	bool success = true;

	T temp = Q.front();
	size_t countEl = Q.size();

	Q.pop();
	SeqType seqType = SeqType::NEITHER;

	for ( size_t i = 0; i < countEl - 1; ++i )
	{
		if ( seqType == SeqType::NEITHER )
		{
			if ( temp < Q.front() )
				seqType = SeqType::ASCENDING;
			else if ( temp > Q.front() )
				seqType = SeqType::DESCENDING;
		}

		if (   ( seqType == SeqType::NEITHER )
			|| ( seqType == SeqType::ASCENDING && temp <= Q.front() )
			|| ( seqType == SeqType::DESCENDING && temp >= Q.front() ))
		{
			Q.push( temp );
			temp = Q.front();
			Q.pop();
		}
		else
		{
			Q.push( temp );
			for ( size_t j = i; j < countEl - 1; ++j )
			{
				Q.push( Q.front() );
				Q.pop();
			}
			success = false;
			break;
		}
	}

	if ( success )
	{
		Q.push( temp );
	}

	return success;
}


int main()
{

	dsa::TemplateQueue<int> Q;
	for ( int i = 0; i < 20; ++i )
	{
		Q.push( i / 2 );
	}
	// Q.push( -10 ); // uncomment for unsorted queue

	Q.print();

	std::cout << ( isSorted( Q ) ? "Yey" : "Ney" ) << std::endl; ;
	Q.print();

	return 0;
}
