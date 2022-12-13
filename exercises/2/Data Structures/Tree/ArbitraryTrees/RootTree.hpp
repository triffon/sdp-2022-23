#pragma once

#include <list>

namespace dsa
{

/// 
/// A simple struct representing an arbitrary tree consisting of Nodes
/// where each Node holds a pointer to its parent Node and as well as
/// a list of Nodes - its children. The RootTree only has one data
/// member - a pointer to its root
///  
///  - Note: Since Trees rely on working directly with pointers this is
///     not a class, but a struct that doesn't hide any implementation.
/// 
///  - Note: A RootTree will free-up its memory correctly as long as
///     the structure of the tree is kept consistent to the definition.
///
template <class ValueType, class Container = std::list<ValueType>>
struct RootTree
{
    struct Node;
    using ChildrenList  = std::list< Node* >;
    
    struct Node
    {
        ChildrenList    fChildrenList;
        ValueType       fValue;
        Node*           fParentPtr;
        bool            fIsVisited;

        Node( Node* parent, const ValueType& value );

        // Allocates a new child and adds it to the child list
        Node& addChild( const ValueType& value );
    };

    /// Big four
    
    RootTree();
    RootTree( const RootTree& other );
    RootTree& operator=( RootTree other );
    ~RootTree();


    /// Methods

    // Adds a child to the given node
    //  returns a pointer to the newly allocated node
    Node* addNode( Node* node, const ValueType& value );

    // Adds a new node as a root for the tree
    //  returns a pointer to the newly allocated node
    Node* addRootNode( const ValueType& value );

    // Deletes the given node as well as all its children recursively
    // Note: If the root is given - the whole tree will be deleted.
    RootTree& deleteBranch( Node* node );

    // Deletes the given node and connects all its children to its parent
    // Warning: If the root is given - the whole tree will be deleted!
    RootTree& deleteNode( Node* node );

    // Clones the given node as well as its children
    // Warning: returns a pointer to a newly allocated Node*
    // whose memory should be handled afterwards
    Node* cloneBranch( const Node* node );

    // Searches and returns a Node containg the given value using DFS
    //  returns nullptr if no such no exists.
    Node* findDeep( const ValueType& value );
    Node* findDeep( const ValueType& value, const Node* from );

    // Searches and returns a Node containg the given value using DFS
    //  returns nullptr if no such no exists.
    const Node* findDeep( const ValueType& value ) const;
    const Node* findDeep( const ValueType& value, const Node* from ) const;

    // Searches and returns a Node containg the given value using BFS
    //   returns nullptr if no such no exists.
    Node* findShallow( const ValueType& value );
    Node* findShallow( const ValueType& value, const Node* from );

    // Searches and returns a Node containg the given value using BFS
    //   returns nullptr if no such no exists.
    const Node* findShallow( const ValueType& value ) const;
    const Node* findShallow( const ValueType& value, const Node* from ) const;

    // Returns the height of the tree (or subtree if given a node)
    size_t height() const;
    size_t height( const Node* from ) const;

    // Returns the max branching of all nodes of this tree (or subtree if given a node)
    size_t branchingFactor() const;
    size_t branchingFactor( const Node* from ) const;

    // Prints all elements at the given level, where the root level is 0 (or subtree if given a node)
    void printLevel( size_t level ) const;
    void printLevel( size_t level, const Node* from ) const;

    // The single data member
    Node* fRootPtr;
};

} // end namespace dsa

#include "RootTree.ipp"
