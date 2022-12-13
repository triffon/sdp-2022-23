#include "RandomTree.hpp"



int main()
{
	dsa::RandomTree<int> myTree;
	dsa::RandomTree<int>::Node* nodePtr = myTree.addNode( 5 );
	myTree.addNode( 11, nodePtr );
	myTree.addNode( 10, nodePtr );
	nodePtr = myTree.addNode( 7, nodePtr );
	myTree.addNode( 5, nodePtr );
	nodePtr = myTree.addNode( 8, nodePtr );
	myTree.addNode( 9, nodePtr );
	myTree.addNode( 4, nodePtr );

	myTree.printTree();

	myTree.find( 5 );

	return 0;
}