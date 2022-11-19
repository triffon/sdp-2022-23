#include <iostream>

// Basic forward list Node structure
struct Node
{
    int     fData;
    Node*   fpNext;
};

// problem solutions
void fillgaps( Node* pHead );
//void removeIdx( Node* pHead );              // TODO:
//bool dupsub( Node<T>* pHead, unsigned k );  // TODO:
void mirror1( Node* pHead );
void mirror2( Node* pHead );
//void mirror( Node<T>* pHead );              // TODO:
//void removedups( Node* pHead );             // TODO:

// basic forward list functions
void insertAfter( Node* pHead, int num );
void pushFront( Node*& pHead, int num );    // Note the reference!
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

    // Do NOT forget to delete your memory!!!
    clearList( pList ); 

    std::cout << "deleted: \t";
    printList( pList );
    std::cout << '\n';

    return 0;
}


/*
 * Problems solutions
 */

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


/*
 * Basic forward list functions
 */

void insertAfter( Node* pHead, int num )
{
    if ( pHead == nullptr )
        return;

    Node*   newNode = new Node { num, pHead->fpNext };
    pHead->fpNext   = newNode;
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


void clearList( Node*& pHead )
{
    Node*   pToDel  = pHead;

    while ( pToDel )
    {
        pHead   = pHead->fpNext;
        delete pToDel;
        pToDel  = pHead;
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
