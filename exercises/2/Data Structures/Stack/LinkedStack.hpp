#pragma once

namespace dsa
{

class LinkedStack
{
public:
    LinkedStack();
    LinkedStack( const LinkedStack& other );
    LinkedStack& operator=( LinkedStack other );
    ~LinkedStack();

    bool        push( int elem );
    bool        pop();
    int&        top();
    const int&  top()   const;
    bool        empty() const;

    void        swap( LinkedStack& other );

private:
    struct Node
    {
        Node( int data = 0, Node* next = nullptr )
            : fNext( next ), fData( data )
        {}

        Node*   fNext;
        int     fData;
    };

private:
    Node*    fTop;
};

} // end namespace dsa
