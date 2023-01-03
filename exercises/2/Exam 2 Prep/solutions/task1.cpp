#include <iostream>
#include <fstream>
#include <string>
#include <queue>

const int STAR      = std::numeric_limits<int>::min();
const int MINUS_INF = std::numeric_limits<int>::min();
const int INF       = std::numeric_limits<int>::max();

struct Node
{
    int     fData;
    Node*   fpLeft;  
    Node*   fpRight;  

    Node( int data = STAR )
        : fData( data )
        , fpLeft( nullptr )
        , fpRight( nullptr )
    {}
};

inline bool isValidNode( const Node* node ) { return node && node->fData != STAR; }

Node* createTree( const std::string& fileName );
bool isBST( const Node* root );
int kthSmallest( const Node* root, size_t kth );
void deleteTree( Node*& tree );

bool readNode( std::ifstream& in, Node* root, std::queue<Node*>& wave, Node*& outNode );
bool isBSTRec( const Node* root, int min, int max );
bool kthSmallestRec( const Node* root, size_t& kth, int& outSmallest );

void testPrintTreeInorder( const Node* root );


int main()
{
    std::string fileName;
    std::cout << "Filename: ";
    std::cin >> fileName;

    Node* tree = createTree( fileName );
    
    if ( !tree )
    {
        std::cout << "The binary tree couldn't be constructed..\n";
        return 1;
    }

    // testPrintTreeInorder( tree );

    if ( !isBST( tree ) )
    {
        std::cout << "Not a BST!\n";
        return 0;
    }

    std::cout << "BST\n";

    size_t kth;
    std::cout << "K: ";
    std::cin >> kth;

    std::cout << kthSmallest( tree, kth );

    deleteTree( tree );

    return 0;
}


void deleteTree( Node*& tree )
{
    if ( !tree )
        return;

    deleteTree( tree->fpLeft );
    deleteTree( tree->fpRight );
    delete tree;
    tree = nullptr;
}


Node* createTree( const std::string& fileName )
{
    std::ifstream in( fileName );
    if ( !in )
    {
        std::cerr << "Error: Couldn't open " << fileName << " for reading.\n";
        return nullptr;
    }

    int count;
    int rows;
    in >> count >> rows;

    if ( count <= 0 )
        return nullptr;

    int elem;
    in >> elem;
    Node* root = new ( std::nothrow ) Node( elem );
    if ( !root )
        return nullptr;

    std::queue<Node*> wave;
    wave.push( root );

    Node* curr;
    while ( !wave.empty() )
    {
        curr = wave.front();
        wave.pop();

        if ( !readNode( in, root, wave, curr->fpLeft ) )
            return nullptr;

        if ( !readNode( in, root, wave, curr->fpRight ) )
            return nullptr;
    }

    in.close();

    return root;
}


bool readNode( std::ifstream& in, Node* root, std::queue<Node*>& wave, Node*& outNode )
{
    std::string str;
    if ( !( in >> str ) )
        return true;

    int elem = STAR;

    if ( str != "*" )
        elem = std::stoi( str );

    outNode = new ( std::nothrow ) Node( elem );
    if ( !outNode )
    {
        deleteTree( root );
        return false;
    }

    wave.push( outNode );
    return true;
}


bool isBST( const Node* root )
{
    return isBSTRec( root, MINUS_INF, INF );
}


bool isBSTRec( const Node* root, int min, int max )
{
    if ( !isValidNode( root ) )
        return true;

    if ( root->fData < min || root->fData > max )
        return false;

    return      isBSTRec( root->fpLeft  , min           , root->fData   )
            &&  isBSTRec( root->fpRight , root->fData   , max           );
}


bool kthSmallestRec( const Node* root, size_t& kth, int& outSmallest )
{
    if ( !isValidNode( root ) )
        return false;

    if ( kthSmallestRec( root->fpLeft, kth, outSmallest ) )
        return true;

    if ( kth == 0 )
    {
        outSmallest = root->fData;
        return true;
    }

    --kth;

    if ( kthSmallestRec( root->fpRight, kth, outSmallest ) )
        return true;

    return false;
}


int kthSmallest( const Node* root, size_t kth )
{
    int res = 0;
    kthSmallestRec( root, kth, res );
    return res;
}


void testPrintTreeInorder( const Node* root )
{
    if ( !isValidNode( root ) )
        return;

    testPrintTreeInorder( root->fpLeft );
    std::cout << root->fData << " ";
    testPrintTreeInorder( root->fpRight );
}
