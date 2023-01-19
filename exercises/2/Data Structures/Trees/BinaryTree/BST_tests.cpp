#include <iostream>
#include <ctime>
#include "BinarySearchTree.hpp"

void fillBSTRandomly( dsa::BST<int>& bst, size_t elements = 20, int range = 100 )
{
    for ( size_t i = 0; i < elements; i++ )
        if ( !bst.tryInsert( -range / 2 + rand() % (range + 1) ) )
            --i;
}


int main()
{
    srand( (unsigned) time( nullptr ) );

    dsa::BST<int> bst;

    //bst.insert( 3 );
    //bst.insert( 2 );
    //bst.insert( 4 );
    //bst.insert( 1 );
    //bst.insert( 5 );

    // Test fill (insert)
    fillBSTRandomly( bst );

    // Test print
    bst.print(); std::cout << "\n";

    // Min/max
    std::cout << "Min: " << bst.min() << ", Max: " << bst.max() << "\n";

    // Test find
    const int TARGET = 0;
    auto res = bst.find( TARGET );
    if ( res )
        std::cout << TARGET << " was found in the BST\n";
    else
        std::cout << TARGET << " was not found!\n";

    // Test operator= (and copy ctor)
    dsa::BST<int> bst2;
    bst2 = bst;

    // Test erase
    const int TO_REMOVE = 30;
    bst2.tryInsert( TO_REMOVE );

    bst.print(); std::cout << "\n";
    bst2.print(); std::cout << "\n";

    bst2.erase( TO_REMOVE );
    bst2.print(); std::cout << "\n";

    // Test move constructor
    dsa::BST<int> bst3  = std::move( bst2 );
    bst2.print(); std::cout << "\n";
    bst3.print(); std::cout << "\n";

    return 0;
}
