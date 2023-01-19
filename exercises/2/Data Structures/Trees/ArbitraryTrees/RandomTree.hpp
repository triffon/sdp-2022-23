#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <iostream>

namespace dsa
{
#define ENABLE_BFS
	template <class T>
	class RandomTree
	{
		typedef T data;
	public:
		struct Node
		{
			data value;
			std::vector<Node*> adjacencyList;
			bool isVisited;

			Node( const data& newValue ) : value( newValue ), isVisited( false ) { }
		};

		RandomTree() { }
		RandomTree( const RandomTree& ) = delete;
		RandomTree& operator=( const RandomTree& ) = delete;
		~RandomTree();

		Node* addNode( const data& newElement, Node* adj = nullptr );
		void removeNode( const data& removedElement );
		void printTree() const;
		Node* find( const data& searchedElement ) const;

	private:
		Node* bfs( Node* start, const data& searchedElement ) const;
		Node* dfs( Node* start, const data& searchedElement ) const;
	private:

		std::list< Node* > tree;

	};


	template<class T>
	inline RandomTree<T>::~RandomTree()
	{
		for ( const Node* node : tree )
		{
			delete node;
		}
	}

	template<class T>
	inline typename RandomTree<T>::Node* RandomTree<T>::addNode( const data& newElement, Node* adj )
	{
		Node* newNode = new Node( newElement );
		if ( adj )
		{
			adj->adjacencyList.push_back( newNode );
			newNode->adjacencyList.push_back( adj );
		}
		tree.push_back( newNode );

		return newNode;
	}

	template<class T>
	inline void RandomTree<T>::removeNode( const data& removedElement )
	{
		// "liniar" search to find a node which must be removed
		// not so easy :(
		for ( Node* node : tree )
		{
			if ( node->value == removedElement )
			{
				tree.remove( node->value );
				delete node;
				break;
			}
		}
	}

	template<class T>
	inline void RandomTree<T>::printTree() const
	{
		for ( const Node* node : tree )
		{
			std::cout << node->value << ": adjacency -> ";
			for ( const Node* adj : node->adjacencyList )
			{
				std::cout << adj->value << " ";
			}
			std::cout << std::endl;
		}

	}

	template<class T>
	inline typename RandomTree<T>::Node* RandomTree<T>::find( const data& searchedElement ) const
	{
		Node* result = nullptr;
		if ( !tree.empty() )
		{
#ifdef ENABLE_BFS
			result = this->bfs( tree.front(), searchedElement );
#else
			result = this->dfs( tree.front(), searchedElement );
#endif // ENABLE_BFS

			for ( Node* node : tree )
			{
				node->isVisited = false;
			}
		}
		return result;
	}

	template<class T>
	inline typename RandomTree<T>::Node* RandomTree<T>::bfs( Node* start, const data& searchedElement ) const
	{
		Node* resultNode = nullptr;
		std::queue<Node*> wave;

		wave.push( start );

		while ( !wave.empty() )
		{
			Node* currentNode = wave.front();
			wave.pop();

			if ( currentNode->value == searchedElement )
			{
				resultNode = currentNode;
				break;
			}

			std::cout << currentNode->value << " ";
			currentNode->isVisited = true;
			for ( Node* adj : currentNode->adjacencyList )
			{
				if ( !adj->isVisited )
				{
					wave.push( adj );
				}
			}
		}
		std::cout << std::endl;

		return resultNode;
	}

	template<class T>
	inline typename RandomTree<T>::Node* RandomTree<T>::dfs( Node* start, const data& searchedElement ) const
	{
		Node* resultNode = nullptr;

		std::stack<Node*> order;

		order.push( start );

		while ( !order.empty() )
		{
			Node* currentNode = order.top();
			order.pop();

			if ( currentNode->value == searchedElement )
			{
				resultNode = currentNode;
				break;
			}

			std::cout << currentNode->value << " ";
			currentNode->isVisited = true;
			for ( Node* adj : currentNode->adjacencyList )
			{
				if ( !adj->isVisited )
				{
					order.push( adj );
				}
			}
		}
		std::cout << std::endl;

		return resultNode;
	}



}