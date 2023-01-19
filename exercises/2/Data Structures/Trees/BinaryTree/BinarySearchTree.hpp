#pragma once
#include <iostream>
#include <optional>

namespace dsa
{

template<class T>
class BST
{
private:
    struct Node
    {
        T       fData;
        Node*   fpLeft  = nullptr;
        Node*   fpRight = nullptr;
    };

public:
    using opt_const_ref = std::optional< std::reference_wrapper<const T> >;

    // Object lifetime
public:
            BST();
            BST( const BST& other );
            BST( BST&& other ) noexcept;
            ~BST();

    BST&    operator=( BST other );
    BST&    operator=( BST&& other ) noexcept;

    // Interface
public:

    void                insert( const T& elem );
    bool                tryInsert( const T& elem );
    opt_const_ref       find( const T& elem ) const;
    bool                erase( const T& elem );
    void                print( std::ostream& out = std::cout ) const;

    T                   min() const;
    T                   max() const;

    // Helper methods
private:
    void                deleteBranch( Node*& node ) noexcept;
    void                copyBranch( Node*& node, const Node* otherNode );

    void                insertRec( Node*& node, const T& elem );
    bool                tryInsertRec( Node*& node, const T& elem );
    opt_const_ref       findRec( const Node* node, const T& elem ) const;
    bool                eraseRec( Node*& node, const T& elem );
    void                printRec( const Node* node, std::ostream& out = std::cout ) const;

    Node*&              minRec( Node*& node );
    const Node*         maxRec( const Node* node ) const;

    // Data fields
private:
    Node*   fpRoot;
};

}

#include "BinarySearchTree.ipp"
