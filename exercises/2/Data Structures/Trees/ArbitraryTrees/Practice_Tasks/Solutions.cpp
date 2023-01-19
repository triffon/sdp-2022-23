#include <iostream>
#include <vector>
#include <queue>

struct Node
{
    int                 fData;
    std::vector<Node*>  fChildren;
    Node( int data = 0 ) : fData(data) {}
};

Node* createTree()
{
    int count = 0;
    Node* root = new Node( count++ );
    root->fChildren.push_back(new Node( count++ ));
    root->fChildren.push_back(new Node( count++ ));
    root->fChildren.push_back(new Node( count++ ));

    root->fChildren[ 0 ]->fChildren.push_back( new Node( count++ ) );

    root->fChildren[ 1 ]->fChildren.push_back( new Node( count++ ) );
    root->fChildren[ 1 ]->fChildren.push_back( new Node( count++ ) );

    root->fChildren[ 2 ]->fChildren.push_back( new Node( count++ ) );

    root->fChildren[ 2 ]->fChildren[0]->fChildren.push_back( new Node( count++ ) );
    root->fChildren[ 2 ]->fChildren[0]->fChildren.push_back( new Node( count++ ) );
    root->fChildren[ 2 ]->fChildren[0]->fChildren.push_back( new Node( count++ ) );
    root->fChildren[ 2 ]->fChildren[0]->fChildren.push_back( new Node( count++ ) );
    root->fChildren[ 2 ]->fChildren[0]->fChildren.push_back( new Node( count++ ) );

    return root;
}

Node* createNiceTree()
{
    Node* root = new Node;
    root->fData = 10;
    root->fChildren.push_back( new Node ( 4 ) );
    root->fChildren.push_back( new Node ( 3 ) );
    root->fChildren.push_back( new Node ( 3 ) );

    root->fChildren[ 0 ]->fChildren.push_back( new Node ( 3 ) );
    root->fChildren[ 0 ]->fChildren.push_back( new Node ( 1 ) );

    root->fChildren[ 1 ]->fChildren.push_back( new Node ( 2 ) );
    root->fChildren[ 1 ]->fChildren.push_back( new Node ( 1 ) );

    root->fChildren[ 0 ]->fChildren[ 0 ]->fChildren.push_back( new Node ( 1 ) );
    root->fChildren[ 0 ]->fChildren[ 0 ]->fChildren.push_back( new Node ( 1 ) );
    root->fChildren[ 0 ]->fChildren[ 0 ]->fChildren.push_back( new Node ( 1 ) );

    return root;
}

void deleteTree( const Node* root )
{
    for ( const Node* child : root->fChildren )
        deleteTree( child );

    delete root;
}

size_t treeHeight( const Node* root )
{
    size_t maxChildHeight = 0;

    for ( const Node* child : root->fChildren )
    {
        size_t currChildHeight = treeHeight( child );
        if ( currChildHeight > maxChildHeight )
            maxChildHeight = currChildHeight;
    }

    return 1 + maxChildHeight;
}

size_t treeBranchingFactor( const Node* root )
{
    size_t maxChildBranchingFactor = root->fChildren.size();

    for ( const Node* child : root->fChildren )
    {
        size_t currChildBranchingFactor = treeBranchingFactor( child );
        if ( currChildBranchingFactor > maxChildBranchingFactor )
            maxChildBranchingFactor = currChildBranchingFactor;
    }

    return maxChildBranchingFactor;
}

void printLevel( const Node* root, size_t level )
{
    if ( level == 0 )
    {
        std::cout << root->fData << " ";
        return;
    }

    for ( const Node* child : root->fChildren )
        printLevel( child, level - 1 );
}

void printTree( const Node* root )
{
    for ( size_t i = 0; i < treeHeight( root ); i++ )
    {
        printLevel( root, i );
        std::cout << "\n";
    }
}

size_t leavesOfTree( const Node* root )
{
    if ( root->fChildren.empty() )
        return 1;

    size_t leaves = 0;
    for ( const Node* child : root->fChildren )
        leaves += leavesOfTree( child );

    return leaves;
}

bool allNodesEqualSumOfChildren( const Node* root )
{
    if ( root->fChildren.empty() )
        return true;

    int sumChildrenData = 0;

    for ( const Node* child : root->fChildren )
        sumChildrenData += child->fData;

    if ( root->fData != sumChildrenData )
        return false;

    for ( const Node* child : root->fChildren )
        if ( !allNodesEqualSumOfChildren( child ) )
            return false;

    return true;
}

bool hasPathToLeafWithSum( const Node* root, int n )
{
    size_t searchSum = n - root->fData;

    if ( searchSum == 0 )
        return true;

    if ( searchSum < 0 )
        return false;

    for ( const Node* child : root->fChildren )
        if ( hasPathToLeafWithSum( child, searchSum ) )
            return true;

    return false;
}

int main()
{
    Node* root = createNiceTree();

    std::cout << treeHeight( root ) << "\n";
    std::cout << treeBranchingFactor( root ) << "\n";
    printTree( root );
    std::cout << leavesOfTree( root ) << "\n";
    std::cout << allNodesEqualSumOfChildren( root ) << "\n";
    std::cout << hasPathToLeafWithSum( root, 15 );

    deleteTree( root );

    return 0;
}