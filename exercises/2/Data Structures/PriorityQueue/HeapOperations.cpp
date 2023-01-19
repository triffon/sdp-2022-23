#include <vector>
#include <iostream>
#include <string>

template <typename T> 
void print( const std::string& text, const std::vector<int>& v = {} )
{
	std::cout << text << ": ";
	for ( const int& elem : v ) 
		std::cout << elem << ' ';

	std::cout << '\n';
}

size_t get_left_child_ind( size_t index )
{
	return index * 2 + 1;
}

size_t get_right_child_ind( size_t index )
{
	return index * 2 + 2;
}

int get_parent_ind( size_t index )
{
	return ( index > 0 ) ? ( index - 1 ) / 2 : -1;
}

template <typename T> 
const T& top( const std::vector<T>& v )
{
	return v[ 0 ];
}

template <typename T> 
void push( std::vector<T>& v, const T& el)
{
	v.push_back( el );

	size_t index = v.size() - 1;

	// check if node at index i and its parent violates 
	// the heap property
	while ( index != 0 && v[ index ] > v[ get_parent_ind( index ) ] )
	{
		// swap the two if heap property is violated
		std::swap( v[ index ], v[ get_parent_ind( index ) ] );

		print<int>( "After push", v );
		// call Heapify-up on the parent
		index = get_parent_ind( index );
	}
}

template<typename T>
void pop( std::vector<T>& v )
{
	v[ 0 ] = v.back();
	v.pop_back();
	int index = 0;

	size_t size = v.size();
	// sift until wanted position is reached
	while ( index < (size - 1) / 2 )
	{
		int left = get_left_child_ind( index );
		int right = get_right_child_ind( index );

		int largest  = index;
		// compare v[index] with its left and right child and find largest/smallest value
		if ( left < size && v[ left ] > v[ largest  ] )
			largest  = left;

		if ( right < size && v[ right ] > v[ largest  ] )
			largest  = right;

		// go down one level more 
		if ( largest  != index )
		{
			std::swap( v[ index ], v[ largest  ] );
			index = largest;
		}
	}

}

template<typename T>
void heapify( std::vector<T>& v, int i )
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	int n = v.size();
	// If left child is larger than root
	if ( l < n && v[ l ] > v[ largest ] )
		largest = l;

	// If right child is larger than largest so far
	if ( r < n && v[ r ] > v[ largest ] )
		largest = r;

	// If largest is not root
	if ( largest != i )
	{
		std::swap( v[ i ], v[ largest ] );

		// Recursively heapify the affected sub-tree
		heapify( v, largest );
	}
}


template<typename T>
void build_heap( std::vector<T>& v )
{
	for ( int i = v.size() / 2 - 1; i >= 0; --i )
	{
		heapify( v, i );
	}
}


int main()
{
	std::vector<int> heap = { 100, 19, 36, 17, 12, 25, 5, 9, 15, 6, 11, 13, 8, 1, 4 };
	print<int>( "Before push", heap );
	push( heap, 30 );
	print<int>( "After push", heap );

	int topOfTheHeap = top<int>( heap );
	std::cout << "The top of the heap is: " << topOfTheHeap << std::endl;

	print<int>( "Before pop", heap );
	pop( heap );
	print<int>( "After pop", heap );


	std::vector<int> arr = { 4, 2, 3, 5, 7, 1, 8};
	build_heap<int>( arr );
	print<int>( "The max heap from array is", arr );

	return 0;
}
