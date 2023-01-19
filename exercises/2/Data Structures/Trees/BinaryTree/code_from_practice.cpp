#include <iostream>

struct BSTNode
{
	int			fData;
	BSTNode*	fpLeft	= nullptr;
	BSTNode*	fpRight	= nullptr;
};

void eraseTree( BSTNode*& root )
{
	if ( ! root )
		return;

	eraseTree( root->fpLeft );
	eraseTree( root->fpRight );
	delete root;
	root = nullptr;
}

bool insert( BSTNode*& root, int elem )
{
	if ( root == nullptr )
	{
		root = new BSTNode { elem };
		return true;
	}

	if ( root->fData < elem )
		return insert( root->fpRight, elem );

	if ( root->fData > elem )
		return insert( root->fpLeft, elem );

	return false;
}

bool erase( BSTNode*& root, int elem )
{
	if ( !root )
		return false;

	if ( root->fData == elem )
	{
		if ( root->fpLeft == nullptr && root->fpRight == nullptr )
		{
			delete root;
			root = nullptr;
			return true;
		}

		if ( root->fpRight != nullptr && root->fpLeft == nullptr )
		{
			BSTNode*	pTemp	= root;
			root	= root->fpRight;
			delete pTemp;
			pTemp	= nullptr;
			return true;
		}

		if ( root->fpLeft != nullptr && root->fpRight == nullptr )
		{
			BSTNode*	pTemp	= root;
			root	= root->fpLeft;
			delete pTemp;
			pTemp	= nullptr;
			return true;
		}

		BSTNode*	pCurr	= root->fpLeft;
		while ( pCurr->fpRight != nullptr )
		{
			pCurr = pCurr->fpRight;
		}

		std::swap( pCurr->fData, root->fData );
		return erase( pCurr, elem );	// TODO: Fix
	}

	if ( root->fData < elem )
		return erase( root->fpRight, elem );
	
	return erase( root->fpLeft, elem );
}

void print( const BSTNode* root )
{
	if ( !root )
		return;

	if ( root->fpLeft )
		print( root->fpLeft );

	std::cout << root->fData << ' ';

	if ( root->fpRight )
		print( root->fpRight );
}


int main()
{
	BSTNode*		pTree	= nullptr;

	insert( pTree, 3 );
	insert( pTree, 5 );
	insert( pTree, 1 );
	insert( pTree, -1 );
	insert( pTree, 2 );
	insert( pTree, 4 );
	insert( pTree, 10 );
	insert( pTree, 6 );
	insert( pTree, 7 );
	insert( pTree, 11 );
	insert( pTree, 8 );

	print( pTree );

	std::cout << "\n";

	erase( pTree, 3 );

	print( pTree );

	eraseTree( pTree );

	return 0;
}
