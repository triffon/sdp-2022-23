#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

struct Node
{
	std::string				fWord;
	std::vector< Node* >	fChildren;

	Node( const std::string& word = "" ) : fWord( word ) {}
};

void printRightView( const Node* root )
{
	// TODO: implement with InOrder traversal (but from right to left)
	//		 saving the current max depth and appending to a string (sentence)
}

void insertChildOnTheRightPlace( const std::string& currentChild, std::vector<Node*>& currentLine, std::vector< Node* >& lastLine, size_t& parentIndex );
Node* init( const std::string& fileName );
void deleteTree( Node* root );


int main()
{
	std::string filename;
	std::cin >> filename;

	Node* root = init( filename );
	
	printRightView( root );

	deleteTree( root );

	return 0;
}


void insertChildOnTheRightPlace( const std::string& currentChild, std::vector<Node*>& currentLine, std::vector< Node* >& lastLine, size_t& parentIndex )
{
	if ( currentChild != "*" )
	{
		Node* newNode = new Node( currentChild );
		assert( parentIndex < lastLine.size() );
		lastLine[ parentIndex ]->fChildren.push_back( newNode );
		currentLine.push_back( newNode );
	}
	else
	{
		parentIndex++;
	}
}


Node* init( const std::string& fileName )
{
	std::ifstream file( fileName );
	if ( !file.is_open() )
		return nullptr;

	std::string rootString;
	std::getline( file, rootString );

	Node* root = new Node( rootString );

	std::vector<Node*> lastLine;
	lastLine.push_back( root );

	while ( !file.eof() )
	{
		std::string line;
		std::getline( file, line );

		std::vector<Node*> currentLine;
		std::string currentChild;
		size_t parentIndex = 0;
		size_t pos = 0;
		while ( ( pos = line.find( ' ' ) ) != std::string::npos )
		{
			currentChild = line.substr( 0, pos );
			insertChildOnTheRightPlace( currentChild, currentLine, lastLine, parentIndex );
			line.erase( 0, pos + 1 );
		}

		insertChildOnTheRightPlace( line, currentLine, lastLine, parentIndex ); // for the last word of this level

		lastLine = currentLine;
	}

	file.close();
	return root;
}


void deleteTree( Node* root )
{
	if ( root )
	{
		for ( Node* child : root->fChildren )
		{
			deleteTree( child );
		}
		delete root;
	}
}
