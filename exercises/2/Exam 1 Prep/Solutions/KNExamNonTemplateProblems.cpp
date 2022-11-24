#include <iostream>

// Basic forward list Node structure containing integers
struct Node
{
    int     fData;
    Node*   fpNext;
};

// problem 1
void fillgaps( Node* pHead );

// problem 2
void removeIdx( Node*& pHead );              // Note the reference!

// problem 4 variant 1
void mirror1( Node* pHead );

// problem 4 variant 2
void mirror2( Node* pHead );

// problem 5
void removedups( Node* pHead );

/* basic forward list functions */
void insertAfter( Node* pNode, int num );
void eraseAfter( Node* pNode );
void pushFront( Node*& pHead, int num );    // Note the reference!
void popFront( Node*& pHead );              // Note the reference!
void clearList( Node*& pHead );             // Note the reference!

// utility functions
void printList( const Node* pHead );        // Note the const!
void printListRec( const Node* pHead );


int main()
{
    Node*   pList   = 
        new Node { 1,
            new Node { 2,
                new Node { 5,
                    new Node { 7, nullptr }
                }
            }
        };

    std::cout << "list: \t\t";
    printListRec( pList );
    std::cout << '\n';

    std::cout << "fillgaps: \t";
    fillgaps( pList );
    printList( pList );
    std::cout << '\n';

    std::cout << "mirror: \t";
    mirror2( pList );
    printList( pList );
    std::cout << '\n';

    std::cout << "removeIdx: \t";
    removeIdx( pList );
    printList( pList );
    std::cout << '\n';

    Node*   pList2   = 
        new Node { 1,
            new Node { 2,
                new Node { 2,
                    new Node { 5, 
                        new Node { 7,
                            new Node { 7, nullptr }
                        }
                    }
                }
            }
        };

    std::cout << "list 2: \t";
    printListRec( pList2 );
    std::cout << '\n';

    std::cout << "removedups: \t";
    removedups( pList2 );
    printList( pList2 );
    std::cout << '\n';

    // Do NOT forget to delete your memory!!!
    clearList( pList );
    clearList( pList2 );

    std::cout << "deleted: \t";
    printList( pList );
    printList( pList2 );
    std::cout << '\n';

    return 0;
}


/*
 * Problems solutions
 */

// problem 1
void fillgaps( Node* pHead )
{
    if ( pHead == nullptr )
        return;

    while ( pHead->fpNext != nullptr )
    {
        if ( pHead->fpNext->fData - pHead->fData > 1 )
        {
            insertAfter( pHead, pHead->fData + 1 );
        }

        pHead = pHead->fpNext;
    }
}


// problem 2
void removeIdx( Node*& pHead )
{
    if ( pHead == nullptr )
        return;

    int length  = 0;
    Node*   pCurr   = pHead;
    while ( pCurr != nullptr )
    {
        ++length;
        pCurr   = pCurr->fpNext;
    }

    
    Node*   pEraser = pHead;

    for ( int i = length - 2; i >= 0; --i )
    {
        if ( pEraser->fpNext->fData == i )
            eraseAfter( pEraser );
        else
            pEraser = pEraser->fpNext;
    }

    if ( pHead->fData == length - 1 )
        popFront( pHead );
}

// variant 1
void mirror1( Node* pHead )
{
    if ( pHead == nullptr )
        return;

    // find the last node
    Node*   pLast   = pHead;
    while ( pLast->fpNext != nullptr )
        pLast   = pLast->fpNext;
    
    // insert elements just after the original last node
    while ( pHead != pLast->fpNext )
    {
        insertAfter( pLast, pHead->fData );
        pHead   = pHead->fpNext;
    }
}


// variant 2
void mirror2( Node* pHead )
{
    if ( pHead == nullptr )
        return;
    
    // keep a pointer to the last node
    Node*   pLast       = pHead;

    // create a new list
    Node*   pNewList    = nullptr;

    // keep inserting all the elements from the
    // original list to the front of the new list
    while ( pHead != nullptr )
    {
        pushFront( pNewList, pHead->fData );
        pHead   = pHead->fpNext;

        // pHead will move until it's nullptr
        // pLast will stop at the last node
        if ( pHead != nullptr )
            pLast   = pHead;
    }

    // lastly link together the two lists (append)
    pLast->fpNext   = pNewList;
}


void removedups( Node* pHead )
{
    if ( pHead == nullptr )
        return;

    Node*   pCurr   = pHead;
    Node*   pNext   = pHead->fpNext;

    while ( pNext )
    {
        if ( pCurr->fData == pNext->fData )
        {
            eraseAfter( pCurr );
        }
        else
        {
            pCurr   = pCurr->fpNext;
        }

        pNext   = pCurr->fpNext;
    }
}


/*
 * Basic forward list functions
 */

void insertAfter( Node* pNode, int num )
{
    if ( pNode == nullptr )
        return;

    Node*   newNode = new Node { num, pNode->fpNext };
    pNode->fpNext   = newNode;
}


void eraseAfter( Node* pNode )
{
    if ( pNode == nullptr || pNode->fpNext == nullptr )
        return;

    Node*   pToDel          = pNode->fpNext;
            pNode->fpNext   = pNode->fpNext->fpNext;
    delete  pToDel;
}


void pushFront( Node*& pHead, int num )
{
    // pHead is a reference so we can change the original head

    if ( pHead == nullptr )
    {
        // empty list case
        pHead   = new Node { num, nullptr };
    }
    else
    {
        // non-empty list
        Node*   newNode = new Node { num, pHead };
        pHead   = newNode;
    }
}


void popFront( Node*& pHead )
{
    // pHead is a reference so we can change the original head

    if ( pHead == nullptr )
        return;

    Node*   pToDel  = pHead;
            pHead   = pHead->fpNext;
    delete  pToDel;
}


void clearList( Node*& pHead )
{
    // pHead is a reference so we can set it to nullptr
    // after the list has been cleared

    while ( pHead )
    {
        Node*   pToDel  = pHead;
                pHead   = pHead->fpNext;
        delete  pToDel;
    }
}


/*
 * Utility functions
 */

void printList( const Node* pHead )
{
    while ( pHead != nullptr )
    {
        std::cout << pHead->fData << ' ';
        pHead   = pHead->fpNext;
    }
}


void printListRec( const Node* pHead )
{
    if ( pHead == nullptr )
        return;

    std::cout << pHead->fData << ' ';
    printListRec( pHead->fpNext );
}
