// 26.11.2020
// Author: Yasen Aleksiev
// Part of the DSA course in FMI-SU 2020/2021

#include <iostream>
#include <algorithm> // for std::transform
#include <functional> // for std::function

template <typename T>
struct BTNode
{
	T		fData;
	BTNode* fLeftNode;
	BTNode* fRightNode;

	BTNode(const T& data) : fData( data ), fLeftNode( nullptr ), fRightNode( nullptr ) { }
};


template <typename T>
bool isLeaf( BTNode<T>* node )
{
	return node && !node->fLeftNode && !node->fRightNode;
}

template <typename T>
void printBinaryLDK( const BTNode<T>* root )
{
	if ( root )
	{
		printBinaryLDK( root->fLeftNode );
		printBinaryLDK( root->fRightNode );
		std::cout << root->fData << " ";
	}
	// hidden bottom of the recursion is over hire
}

template <typename T>
void printBinaryLKD( const BTNode<T>* root )
{
	if ( root )
	{
		printBinaryLKD( root->fLeftNode );
		std::cout << root->fData << " ";
		printBinaryLKD( root->fRightNode );
	}
}

template <typename T>
void printBinaryKLD( const BTNode<T>* root )
{
	if ( root )
	{
		std::cout << root->fData << " ";
		printBinaryKLD( root->fLeftNode );
		printBinaryKLD( root->fRightNode );
	}
}


void initTree( BTNode<int>*& root ) // we need to pass the pointer by reference, because we need to change it
{//	costruct binary search tree
	root = new BTNode<int>( 5 );

	root->fLeftNode = new BTNode<int>( 4 );
	root->fRightNode = new BTNode<int>( 11 );

	root->fLeftNode->fLeftNode = new BTNode<int>( 3 );
	root->fRightNode->fLeftNode = new BTNode<int>( 10 );
	root->fRightNode->fRightNode = new BTNode<int>( 13 );

	root->fLeftNode->fLeftNode->fLeftNode = new BTNode<int>( 1 );
	root->fRightNode->fLeftNode->fLeftNode = new BTNode<int>( 9 );
}

struct Student
{
	std::string fName;
	unsigned short fFn;

	Student( const std::string& name, unsigned short fn ) : fName( name ), fFn ( fn ) { }
};

bool operator<( const Student& lhs, const Student& rhs )
{
	return lhs.fFn < rhs.fFn;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << '[' << s.fName << ',' << s.fFn << ']' << std::endl;
	return os;
}


void initTree( BTNode<Student>*& root )
{
	root = new BTNode<Student>( Student( "Eeeee", 45005 ) );

	root->fLeftNode = new BTNode<Student>( Student( "Deeee", 45004 ) );
	root->fRightNode = new BTNode<Student>( Student( "Kkkkk", 45011 ) );

	root->fLeftNode->fLeftNode = new BTNode<Student>( Student( "Ccccc", 45003 ) );
	root->fRightNode->fLeftNode = new BTNode<Student>( Student( "Jjjjj", 45010 ) );
	root->fRightNode->fRightNode = new BTNode<Student>( Student( "Mmmmm", 45013 ) );

	root->fLeftNode->fLeftNode->fLeftNode = new BTNode<Student>( Student( "Aaaaa", 45001) );
	root->fRightNode->fLeftNode->fLeftNode = new BTNode<Student>( Student( "Iiiii", 45009 ) );
}

template <typename T>
void deleteTree( BTNode<T>*& root )
{
	if ( root )
	{
		deleteTree( root->fLeftNode );
		deleteTree( root->fRightNode );
		delete root;
		root = nullptr;
	}
}


template <typename T, typename Comparator = std::less<T> >
bool isValidBST( const BTNode<T>* root, Comparator comp = Comparator() )
{
	if ( !root )
	{
		return true;
	}

	/* false if left is > than node */
	if ( root->fLeftNode && !comp( root->fLeftNode->fData, root->fData ) ) // A -> B <=> (A && !B) 
	{
		return false;
	}

	/* false if right is < than node */
	if ( root->fRightNode && !comp( root->fData, root->fRightNode->fData ) ) // A -> B <=> (A && !B) 
	{
		return false;
	}

	/* false if, recursively, the left or right is not a BST */
	if ( !isValidBST( root->fLeftNode ) || !isValidBST( root->fRightNode ) )
	{
		return false;
	}

	/* passing all that, it's a BST */
	return true;
}


void sq( int& x )
{
	x = x * x;
}

void addOne( int& x )
{
	++x;
}

void makeUpperCase( Student& s )
{
	for ( char& c : s.fName ) c = toupper( c );
	// or
	// std::transform(s.fName.begin(), s.fName.end(), s.fName.begin(), ::toupper);
}

void stringReverse( Student& s )
{
	std::reverse( s.fName.begin(), s.fName.end() );
}

template <typename T>
void tree_map( BTNode<T>* root, const std::function<void(T&)>& f )	// The type of the argument of the function f is the same as
																	// the type of the objects in the nodes on the given tree
{
	if ( root )
	{
		tree_map( root->fLeftNode, f );
		tree_map( root->fRightNode, f );
		f( root->fData );
	}
}

template <typename T>
void trim( BTNode<T>*& root )
{
	if ( isLeaf( root ) )
	{
		delete root;
		root = nullptr;
	}
	else
	{
		if ( root->fLeftNode )
		{
			trim( root->fLeftNode );
		}
		if ( root->fRightNode )
		{
			trim( root->fRightNode );
		}
	}
}

template <typename T>
void bloom( BTNode<T>*& root )
{
	if ( isLeaf( root ) )
	{
		root->fLeftNode = new BTNode<T>( root->fData );
		root->fRightNode = new BTNode<T>( root->fData );
		return;
	}
	if ( root->fLeftNode )
	{
		bloom( root->fLeftNode );
	}
	if ( root->fRightNode )
	{
		bloom( root->fRightNode );
	}
}

void testBTWithNumbers()
{
	std::cout << "BEGIN TEST FOR THE BINARY TREE WITH INTEGERS\n\n";

	BTNode<int>* root = nullptr;
	std::cout << "Init tree with integers...\n";
	initTree( root );
	std::cout << "Print binary tree [left->root->right]: \n";
	printBinaryLKD( root );
	std::cout << std::endl;

	std::cout << "Validate the tree:\n";
	if ( isValidBST( root ) )
	{
		std::cout << "Valid BST" << std::endl;
	}
	else
	{
		std::cout << "Not valid BST" << std::endl;
	}

	printBinaryLKD( root );
	std::cout << std::endl;

	std::function<void(int&)> sqPt = sq;
	std::function<void(int&)> addOnePt = addOne;
	std::cout << "Map a function that makes every number in the tree squared...\n";
	tree_map( root, sqPt );
	std::cout << "And the result tree is:\n";
	printBinaryLKD( root );
	std::cout << "\n--------------------------------\n\n";


	std::cout << "Trim every leaf of the tree... :(\n";
	trim( root );
	std::cout << "And the result tree is:\n";
	printBinaryLKD( root );
	std::cout << "\n--------------------------------\n\n";

	std::cout << "Bloom every leaf of the tree... ^.^\n";
	bloom( root );
	std::cout << "And the result tree is:\n";
	printBinaryLKD( root );
	std::cout << "\n--------------------------------\n\n";

	deleteTree( root );
	std::cout << "\n\nEND TEST FOR THE BINARY TREE WITH INTEGERS\n\n";
}


void testBTWithStudents()
{
	std::cout << "BEGIN TEST FOR THE BINARY TREE WITH STUDENTS\n\n";

	BTNode<Student>* root = nullptr;
	std::cout << "Init tree with students...\n";
	initTree( root );
	std::cout << "Print binary tree [left->root->right]: \n";

	printBinaryLKD( root );
	std::cout << std::endl;

	std::cout << "Validate the tree by two ways:\n";
	if ( isValidBST( root ) )	//	This will validate the tree with comparision the students by FN, 
	{							//	using 'bool operator<( const Student& lhs, const Student& rhs )'
	
		std::cout << "Valid BST with students by there faculty numbers" << std::endl;
	}
	else
	{
		std::cout << "Not valid BST with students by there faculty numbers" << std::endl;
	}

	if ( isValidBST( root, [] ( const Student& lhs, const Student& rhs ) { return lhs.fName < rhs.fName;  } ) ) 
	{ // Тhis will validate the tree with compared the students by Name, using lambda function to compared two given students
	  // The names are compared with operator< of the std::string
	  // The second template argument will be evalued from the given lambda 
		std::cout << "Valid BST with students by there names" << std::endl;
	}
	else
	{
		std::cout << "Not valid BST with students by there names" << std::endl;
	}

	printBinaryLKD( root );
	std::cout << std::endl;

	std::function<void(Student&)> makeUpperCasePt = makeUpperCase;
	std::function<void(Student&)> reverseStrPt = stringReverse;
	std::cout << "Map a function that makes upper case name of every student in the tree...\n";
	tree_map( root, makeUpperCasePt );
	std::cout << "And the result tree is:\n";
	printBinaryLKD( root );
	std::cout << "\n--------------------------------\n\n";


	std::cout << "Trim every leaf of the tree... :(\n";
	trim( root );
	std::cout << "And the result tree is:\n";
	printBinaryLKD( root );
	std::cout << "\n--------------------------------\n\n";

	std::cout << "Bloom every leaf of the tree... ^.^\n";
	bloom( root );
	std::cout << "And the result tree is:\n";
	printBinaryLKD( root );
	std::cout << "\n--------------------------------\n\n";

	deleteTree( root );

	std::cout << "\n\nEND TEST FOR THE BINARY TREE WITH STUDENTS\n\n";
}

template <typename T>
BTNode<T>* sortedArrayToBST( T arr[], int start, int end )
{
	if ( start > end )
	{
		return nullptr;
	}

	int mid = ( start + end ) / 2;
	BTNode<T>* root = new BTNode<T>( arr[ mid ] );

	root->fLeftNode = sortedArrayToBST( arr, start, mid - 1 );
	
	root->fRightNode = sortedArrayToBST( arr, mid + 1, end );

	return root;
}


int main()
{
	//testBTWithNumbers();
	//testBTWithStudents();


	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int n = sizeof(arr) / sizeof(arr[0]);  

	/* Convert List to BST */
	BTNode<int>* root = sortedArrayToBST<int>( arr, 0, n - 1 );

	printBinaryLDK( root );

	return 0;
}