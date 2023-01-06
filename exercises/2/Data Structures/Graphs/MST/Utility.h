#include <vector>

namespace dsa
{


	// A structure to represent a subset for union-find
	struct subset
	{
		int parent;
		int rank;
	};



	int		find( std::vector<subset>& subsets, int i );

	void	Union( std::vector<subset>& subsets, int x, int y );
}