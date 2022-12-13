#include <iostream>
#include "RootTree.hpp"

void printTreeLevels( const dsa::RootTree<int>& tree )
{
    size_t treeHeight = tree.height();
    for ( size_t i = 0; i < treeHeight; i++ )
    {
        std::cout << "Level " << i << ": ";
        tree.printLevel( i );
        std::cout << "\n";
    }
}

int main()
{
    dsa::RootTree< int > tree;


    tree.addRootNode( 0 );
    tree.addNode( tree.fRootPtr, 1 );
    tree.fRootPtr->addChild( 2 );

    int count = 3;
    for ( dsa::RootTree< int >::Node* child : tree.fRootPtr->fChildrenList )
    {
        child->addChild( count ).addChild( count + 1 ).addChild( count + 2 );
        count += 3;
    }

    // Adds a child 9 to the node 4
    dsa::RootTree<int>::Node* randNode = *(++tree.fRootPtr->fChildrenList.front()->fChildrenList.begin());
    randNode->addChild( count );

    std::cout << "The tree has a height of: " << tree.height() << "\n";
    std::cout << "The tree has a branching factor of: " << tree.branchingFactor() << "\n";

    std::cout << "---------------------\n";
    printTreeLevels( tree );

    /// Delete the node 4
    tree.deleteNode( randNode );

    std::cout << "---------------------\n";
    printTreeLevels( tree );

    // Node 9
    randNode = *(++tree.fRootPtr->fChildrenList.front()->fChildrenList.begin());
    randNode->addChild( 100 ).addChild( 101 );
    // Adds two children to the node 9

    std::cout << "---------------------\n";
    printTreeLevels( tree );

    // Clone the Node 9 branch and add it as children to Node 9
    dsa::RootTree<int>::Node* cloned = tree.cloneBranch( randNode );
    cloned->fParentPtr = randNode;
    randNode->fChildrenList.push_back( cloned );

    std::cout << "---------------------\n";
    printTreeLevels( tree );

    tree.deleteBranch( cloned );

    std::cout << "---------------------\n";
    printTreeLevels( tree );

    std::cout << "---------------------\n";
    const int TARGET = 100;
    dsa::RootTree<int>::Node* res = tree.findDeep( TARGET );
    std::cout << TARGET << " has " << ( res ? "" : "not " ) << "been found using DFS.\n";

    res = tree.findShallow( TARGET );
    std::cout << TARGET << " has " << ( res ? "" : "not " ) << "been found using BFS.\n";
    
    return 0;
}
