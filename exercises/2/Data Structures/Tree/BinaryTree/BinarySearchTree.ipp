#pragma once
#include "BinarySearchTree.hpp"

namespace dsa
{


template<class T>
BST<T>::BST()
    : fpRoot( nullptr )
{}


template<class T>
BST<T>::BST( const BST& other )
{
    this->copyBranch( fpRoot, other.fpRoot );
}


template<class T>
BST<T>::BST( BST&& other ) noexcept
{
    this->fpRoot    = other.fpRoot;
    other.fpRoot    = nullptr;  // Leave `other` in a valid state!
}


template<class T>
BST<T>& BST<T>::operator=( BST other )
{
    std::swap( fpRoot, other.fpRoot );
    return *this;
}


template<class T>
BST<T>& BST<T>::operator=( BST&& other ) noexcept
{
    if ( this != &other )
    {
        this->deleteBranch( fpRoot );
        this->fpRoot = other.fpRoot;
        other.fpRoot = nullptr; // Leave `other` in a valid state!
    }

    return *this;
}


template<class T>
BST<T>::~BST()
{
    this->deleteBranch( fpRoot );
}


template<class T>
void BST<T>::insert( const T& elem )
{
    this->insertRec( fpRoot, elem );
}


template<class T>
bool BST<T>::tryInsert( const T& elem )
{
    return this->tryInsertRec( fpRoot, elem );
}


template<class T>
typename BST<T>::opt_const_ref
    BST<T>::find( const T& elem ) const
{
    return this->findRec( fpRoot, elem );
}


template<class T>
bool BST<T>::erase( const T& elem )
{
    return this->eraseRec( fpRoot, elem );
}


template<class T>
void BST<T>::print( std::ostream& out ) const
{
    this->printRec( fpRoot, out );
}


template<class T>
T BST<T>::min() const
{
    if ( fpRoot == nullptr )
        throw std::logic_error( "BST: min() of an empty BST!" );

    // Iterative method
    BST<T>::Node*   pCurr   = fpRoot;
    while ( pCurr->fpLeft )
        pCurr   = pCurr->fpLeft;

    return pCurr->fData;
}


template<class T>
T BST<T>::max() const
{
    // Recursive method
    return this->maxRec( fpRoot )->fData;
}

template<class T>
typename const BST<T>::Node*
BST<T>::maxRec( const Node* node ) const
{
    if ( node == nullptr )
        throw std::logic_error( "BST: max() of an empty BST!" );

    // Tail recursive method (iterative recursion)
    if ( node->fpRight )
        return this->maxRec( node->fpRight );

    return node;
}


template<class T>
void BST<T>::deleteBranch( Node*& node ) noexcept
{
    if ( !node )
        return;
    
    deleteBranch( node->fpLeft );
    deleteBranch( node->fpRight );
    delete node;
    node = nullptr;
}


template<class T>
void BST<T>::copyBranch( Node*& node, const Node* otherNode )
{
    if ( !otherNode )
        return;
    
    node = new Node { otherNode->fData };
    this->copyBranch( node->fpLeft, otherNode->fpLeft );
    this->copyBranch( node->fpRight, otherNode->fpRight );
}


template<class T>
void BST<T>::insertRec( Node*& node, const T& elem )
{
    if ( !this->tryInsertRec( node, elem ) )
        throw std::logic_error( "BST: Cannot store duplicate elements!" );
}


template<class T>
bool BST<T>::tryInsertRec( Node*& node, const T& elem )
{
    if ( node == nullptr )
    {
        // Free space (nullptr) found
        node = new Node { elem };
        return true;
    }

    // Insert in the left subtree
    if ( elem < node->fData )
        return this->tryInsertRec( node->fpLeft, elem );

    // Insert in the right subtree ( elem > node->fData )
    if ( elem > node->fData )
        return this->tryInsertRec( node->fpRight, elem );

    // Discard duplicates (elem == node->fData)
    return false;
}


template<class T>
typename BST<T>::opt_const_ref
BST<T>::findRec( const Node* node, const T& elem ) const
{
    if ( !node )
        return std::nullopt;
    
    if ( elem == node->fData )
        return node->fData;

    if ( elem < node->fData )
        return this->findRec( node->fpLeft, elem );

    // ( elem > node->fData )
    return this->findRec( node->fpRight, elem );
}


template<class T>
bool BST<T>::eraseRec( Node*& node, const T& elem )
{
    if ( !node )
        return false;
    
    if ( node->fData == elem ) // Element found
    {
        if ( !node->fpLeft && !node->fpRight )
        {
            // No children => it's a leaf
            delete node;
            node = nullptr;
        }
        else if ( ( node->fpLeft && !node->fpRight ) || ( !node->fpLeft && node->fpRight ) )
        {
            // Only one child => replace it with the child
            Node* onlyChild = node->fpLeft ? node->fpLeft : node->fpRight;
            Node* toRemove = node;
            node = onlyChild;
            delete toRemove;
        }
        else
        {
            // Two children => replace it with the smallest from the right subtree
            Node*& min = this->minRec( node->fpRight );
            std::swap( node->fData, min->fData );
            this->eraseRec( min, elem ); // Erase recursively incase it's not a leaf
        }

        return true;
    }
    else if ( elem < node->fData )
    {
        // Search the left subtree
        return this->eraseRec( node->fpLeft, elem );
    }

    // Search the right subtree ( elem > node->fData )
    return this->eraseRec( node->fpRight, elem );
}


template<class T>
void BST<T>::printRec( const Node* node, std::ostream& out ) const
{
    if ( !node )
        return;
    
    this->printRec( node->fpLeft );
    out << node->fData << " ";
    this->printRec( node->fpRight );
}


template<class T>
typename BST<T>::Node*&
BST<T>::minRec( Node*& node )
{
    if ( node->fpLeft )
        return this->minRec( node->fpLeft );

    return node;
}

} // end of namespace dsa
