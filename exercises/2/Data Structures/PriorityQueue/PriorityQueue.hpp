#include <vector>


namespace dsa
{
	template< typename T, typename Container = std::vector<T>, typename Comparator = std::less<T> >
	class PriorityQueue
	{
	public:
		PriorityQueue() = default;

		PriorityQueue( const Comparator& cmp );

		PriorityQueue( const PriorityQueue& ) = default;

		PriorityQueue& operator=( const PriorityQueue& ) = default;

		~PriorityQueue() = default;

	public:
		const T& top() const;
		void push( const T& el );
		void pop();

		bool empty() const;
		size_t size() const;


	private:
		Container	fData;
		Comparator	fCmp;

	private:

		size_t	get_left_child_ind( size_t index ) const;
		size_t	get_right_child_ind( size_t index ) const;
		int		get_parent_ind( size_t index ) const;
		void	sift_down( size_t index );
		void	sift_up( size_t index );
	};


	template<typename T, typename Container, typename Comparator>
	inline
		PriorityQueue<T, Container, Comparator>::PriorityQueue( const Comparator& cmp ): fCmp( cmp )
	{
	}


	template<typename T, typename Container, typename Comparator>
	inline
		size_t PriorityQueue<T, Container, Comparator>::get_left_child_ind( size_t index ) const
	{
		return index * 2 + 1;
	}

	template<typename T, typename Container, typename Comparator>
	inline
		size_t PriorityQueue<T, Container, Comparator>::get_right_child_ind( size_t index ) const
	{
		return index * 2 + 2;
	}

	template<typename T, typename Container, typename Comparator>
	inline
		int PriorityQueue<T, Container, Comparator>::get_parent_ind( size_t index ) const
	{
		return ( index ) ? ( index - 1 ) / 2 : -1;
	}

	template<typename T, typename Container, typename Comparator>
	inline void PriorityQueue<T, Container, Comparator>::sift_down( size_t index )
	{
		// get left and right child of node at index index
		int left = get_left_child_ind( index );
		int right = get_right_child_ind( index );

		int indexToChange = index;

		// compare fData[index] with its left and right chill and find largest/smallest value
		if ( left < size() && !fCmp( fData[ left ], fData[ index ] ) )
			indexToChange = left;

		if ( right < size() && !fCmp( fData[ right ], fData[ indexToChange ] ) )
			indexToChange = right;

		// swap with child having greater/smaller value and call heapify-down on the child
		if ( indexToChange != index )
		{
			std::swap( fData[ index ], fData[ indexToChange ] );
			sift_down( indexToChange );
		}
	}

	template<typename T, typename Container, typename Comparator>
	inline void PriorityQueue<T, Container, Comparator>::sift_up( size_t index )
	{
		// check if node at fData[index] and its parent violates 
		// the heap property
		if ( index && fCmp( fData[ this->get_parent_ind( index ) ], fData[ index ] ) )
		{
			// swap the two if heap property is violated
			std::swap( fData[ index ], fData[ this->get_parent_ind( index ) ] );

			// call sift_up on the parent
			sift_up( this->get_parent_ind( index ) );
		}
	}

	template<typename T, typename Container, typename Comparator>
	const T& PriorityQueue<T, Container, Comparator>::top() const {

		return fData.front();
	}

	template<typename T, typename Container, typename Comparator>
	void PriorityQueue<T, Container, Comparator>::push(const T& el) {

		fData.push_back(el);
		sift_up(fData.size() - 1);
	}

	template<typename T, typename Container, typename Comparator>
	void PriorityQueue<T, Container, Comparator>::pop() {

		std::swap(fData.front(), fData.back());
		fData.pop_back();
		sift_down(0);
	}

	template<typename T, typename Container, typename Comparator>
	inline bool PriorityQueue<T, Container, Comparator>::empty() const {

		return fData.empty();
	}

	template<typename T, typename Container, typename Comparator>
	inline size_t PriorityQueue<T, Container, Comparator>::size() const {

		return fData.size();
	}
}
