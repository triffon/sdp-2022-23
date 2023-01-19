#include "RootTree.hpp"
#include <vector>
#include <queue>

namespace dsa
{


template<class ValueType, class Container>
inline RootTree<ValueType, Container>::Node::Node( Node* parent, const ValueType& value )
    : fParentPtr( parent )
    , fValue( value )
{}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node&
RootTree<ValueType, Container>::Node::addChild( const ValueType& value )
{
    fChildrenList.push_back( new Node( this, value ) );
    return *this;
}


template<class ValueType, class Container>
inline RootTree<ValueType, Container>::RootTree()
    : fRootPtr( nullptr )
{}


template<class ValueType, class Container>
inline RootTree<ValueType, Container>::RootTree( const RootTree& other )
{
    this->fRootPtr = other.cloneBranch( other.fRootPtr );
}


template<class ValueType, class Container>
inline RootTree<ValueType, Container>&
RootTree<ValueType, Container>::operator=( RootTree other )
{
    std::swap( this->fRootPtr, other.fRootPtr );
    return *this;
}


template<class ValueType, class Container>
inline RootTree<ValueType, Container>::~RootTree()
{
    this->deleteBranch( fRootPtr );
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::addNode( Node* node, const ValueType& value )
{
    node->addChild( value );
    return node->fChildrenList.back();
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::addRootNode( const ValueType& value )
{
    Node* newRoot = new Node( nullptr, value );

    if ( this->fRootPtr )
    {
        newRoot->fChildrenList.push_back( this->fRootPtr );
        this->fRootPtr->fParentPtr = newRoot;
    }

    this->fRootPtr = newRoot;
    return this->fRootPtr;
}


template<class ValueType, class Container>
inline RootTree<ValueType, Container>&
RootTree<ValueType, Container>::deleteBranch( Node* node )
{
    // Note: This method has a problem.
    //       Whoever finds it will receive a bonus point. :)

    while ( !node->fChildrenList.empty() )
        this->deleteBranch( node->fChildrenList.front() );

    node->fChildrenList.clear();
    this->deleteNode( node );

    delete node;
    node = nullptr;

    return *this;
}

template<class ValueType, class Container>
inline RootTree<ValueType, Container>&
RootTree<ValueType, Container>::deleteNode( Node* node )
{
    if ( Node* parent = node->fParentPtr )
    {
        ChildrenList& parentChildren    = parent->fChildrenList;
        ChildrenList& children          = node->fChildrenList;

        typename ChildrenList::const_iterator itNode = 
            std::find( parentChildren.begin(), parentChildren.end(), node );

        // Inserts all the current children to the parent's children list at the node's location
        parentChildren.insert( itNode, children.begin(), children.end() );

        parentChildren.erase( itNode );
    }
    else
    {
        this->deleteBranch( node );
    }

    return *this;
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::cloneBranch( const Node* node )
{
    Node* result = new Node( nullptr, node->fValue );

    for ( const Node* child : node->fChildrenList )
    {
        result->fChildrenList.push_back( cloneBranch( child ) );
        result->fChildrenList.back()->fParentPtr = result;
    }

    return result;
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node* RootTree<ValueType, Container>::findDeep( const ValueType& value )
{
    return this->findDeep( value, this->fRootPtr );
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findDeep( const ValueType& targetValue, const Node* from /*= fRootPtr*/ )
{
    return
        const_cast< Node* >(
            std::as_const( *this ).findDeep( targetValue, from )
        );
}


template<class ValueType, class Container>
inline typename const RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findDeep( const ValueType& value ) const
{
    return this->findDeep( value, this->fRootPtr );
}


template<class ValueType, class Container>
inline typename const RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findDeep( const ValueType& targetValue, const Node* from /*= fRootPtr*/ ) const
{
    if ( from->fValue == targetValue )
        return from;

    for ( const Node* child : from->fChildrenList )
        if ( const Node* result = findDeep( targetValue, child ) )
            return result;

    return nullptr;
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findShallow( const ValueType& value )
{
    return this->findShallow( value, this->fRootPtr );
}


template<class ValueType, class Container>
inline typename RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findShallow( const ValueType& targetValue, const Node* from /*= fRootPtr*/ )
{
    return
        const_cast< Node* >(
            std::as_const( *this ).findDeep( targetValue, from )
        );
}


template<class ValueType, class Container>
inline typename const RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findShallow( const ValueType& value ) const
{
    return this->findShallow( value, this->fRootPtr );
}

template<class ValueType, class Container>
inline typename const RootTree<ValueType, Container>::Node*
RootTree<ValueType, Container>::findShallow( const ValueType& targetValue, const Node* from /*= fRootPtr*/ ) const
{
    std::vector< const Node* > visited;
    std::queue< const Node* > wave;

    // Lambda function that returns true if the node exists in the visited vector
    //   Note: std::find(...) has linear time complexity for std::vector
    //   We'll look at a different data stucture that has a constant find later on in the course
    auto isVisited = [ &visited ] ( const Node* node )
    {
        return std::find( visited.begin(), visited.end(), node ) != visited.end();
    };

    wave.push( from );
    while ( !wave.empty() )
    {
        const Node* currentNode = wave.front();

        if ( currentNode->fValue == targetValue )
            return currentNode;

        visited.push_back( currentNode );

        for ( const Node* child : currentNode->fChildList )
            if ( !isVisited( child ) )
                wave.push( child );

        wave.pop();
    }

    return nullptr;
}


template<class ValueType, class Container>
inline size_t RootTree<ValueType, Container>::height() const
{
    return this->height( this->fRootPtr );
}


template<class ValueType, class Container>
inline size_t RootTree<ValueType, Container>::height( const Node* from /*= fRootPtr*/ ) const
{
    size_t maxChildHeight = 0;
    for ( const Node* child : from->fChildrenList )
    {
        size_t childHeight = this->height( child );
        if ( childHeight > maxChildHeight )
            maxChildHeight = childHeight;
    }
    
    return 1 + maxChildHeight;
}


template<class ValueType, class Container>
inline size_t RootTree<ValueType, Container>::branchingFactor() const
{
    return this->branchingFactor( this->fRootPtr );
}


template<class ValueType, class Container>
inline size_t RootTree<ValueType, Container>::branchingFactor( const Node* from /*= fRootPtr*/ ) const
{
    size_t branchingOfCurrent = from->fChildrenList.size();
    
    for ( const Node* child : from->fChildrenList )
    {
        size_t branchingOfChild = branchingFactor( child );
        if ( branchingOfChild > branchingOfCurrent )
            branchingOfCurrent = branchingOfChild;
    }
    
    return branchingOfCurrent;
}


template<class ValueType, class Container>
inline void RootTree<ValueType, Container>::printLevel( size_t level ) const
{
    return this->printLevel( level, this->fRootPtr );
}


template<class ValueType, class Container>
inline void RootTree<ValueType, Container>::printLevel( size_t level, const Node* from /*= fRootPtr*/ ) const
{
    if ( level == 0 )
    {
        std::cout << from->fValue << " ";
        return;
    }
    
    for ( const Node* child : from->fChildrenList )
        printLevel( level - 1, child );
}


} // end namespace dsa
