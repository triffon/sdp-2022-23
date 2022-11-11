#include <iostream>

struct Node
{
    int     fData;
    Node*   fpNext  = nullptr;
};

// Note the references included to the Node*
// They are needed when the head might be changed inside the function!

void reverse( Node*& pHead );
void erase_repeats( Node* pHead );
void unique( Node* pHead );
void append( Node*& pHeadLhs, Node*& pHeadRhs );

template<class Predicate>
void divide_by( Node*& pHead, Predicate pred );

// utility functions
void erase_after( Node* pElem );
void clearList( Node*& pHead );
void printList( const Node* pHead );    // Note the const!
bool isEven( int num );


int main()
{
    Node*   pLst    = 
        new Node { 1,
            new Node { 2,
                new Node { 2,
                    new Node { 4,
                        new Node { 2,
                            new Node { 5 }
                        }
                    }
                }
            }
        };

    std::cout << "list: \t\t";
    printList( pLst );
    std::cout << '\n';

    reverse( pLst );

    std::cout << "reverse: \t";
    printList( pLst );
    std::cout << '\n';

    erase_repeats( pLst );

    std::cout << "erase_reps: \t";
    printList( pLst );
    std::cout << '\n';

    unique( pLst );

    std::cout << "unique: \t";
    printList( pLst );
    std::cout << '\n';

    divide_by( pLst, isEven );

    // can also be written with a lambda
    //divide_by( pLst, [] (int num) { return num % 2 == 0; } );

    std::cout << "divide by: \t";
    printList( pLst );
    std::cout << '\n';


    // Do NOT forget to clear your memory!
    clearList( pLst ); 

    std::cout << "delete: \t";
    printList( pLst );
    std::cout << '\n';

    return 0;
}


void reverse( Node*& pHead )
{
    Node*   pPrev   = nullptr;
    Node*   pNext   = pHead->fpNext;

    while ( pNext )
    {
        pHead->fpNext   = pPrev;
        pPrev           = pHead;
        pHead           = pNext;
        pNext           = pNext->fpNext;
    }

    pHead->fpNext   = pPrev;
}


void erase_repeats( Node* pHead )
{
    if ( pHead == nullptr )
        return; // edge case, because if pHead is nullptr then "pHead->fpNext" will fail

    Node*   pCurr   = pHead;
    Node*   pNext   = pHead->fpNext;

    while ( pNext )
    {
        if ( pCurr->fData == pNext->fData )
        {
            erase_after( pCurr );
        }
        else
        {
            pCurr   = pCurr->fpNext;
        }

        pNext   = pCurr->fpNext;
    }
}


void unique( Node* pHead )
{
    Node*   pCurr   = pHead;

    while ( pCurr != nullptr )
    {
        Node*   pEraser = pCurr;

        while ( pEraser->fpNext != nullptr )
        {
            if ( pCurr->fData == pEraser->fpNext->fData )
                erase_after( pEraser );
            else
                pEraser = pEraser->fpNext;
        }

        pCurr   = pCurr->fpNext;
    }
}


void append( Node*& pHeadLhs, Node*& pHeadRhs )
{
    if ( pHeadLhs == nullptr )
    {
        pHeadLhs    = pHeadRhs; // Ex.: [] append [ 1, 2, 3 ], result: [ 1, 2, 3 ]
    }
    else
    {
        Node*   pCurr   = pHeadLhs;
        while ( pCurr->fpNext )
            pCurr   = pCurr->fpNext;

        pCurr->fpNext   = pHeadRhs;
    }

    pHeadRhs    = nullptr;
}


template<class Predicate>
void divide_by( Node*& pHead, Predicate pred )
{
    if ( pHead == nullptr || pHead->fpNext == nullptr )
        return; // do nothing for lists with 0 or 1 elements

    size_t  elemCnt = 1;

    // Count the number of elements
    // and get a pointer to the last node
    Node*   pLast   = pHead;
    while ( pLast->fpNext )
    {
        pLast   = pLast->fpNext;
        ++elemCnt;
    }

    Node*   pPrev   = nullptr;
    Node*   pCurr   = pHead;
    for ( size_t i = 0; i < elemCnt; i++ )  // do exactly elemCnt steps
    {
        if ( pred( pCurr->fData ) ) // used the predicate function
        {
            // if the current element satisfies the predicate
            // move it to the end of the list

            if ( pCurr == pHead )
            {
                // special case - we're moving the head to the back
                pHead           = pHead->fpNext;
                pLast->fpNext   = pCurr;
                pLast           = pLast->fpNext;
                pCurr           = pHead;
            }
            else if ( pCurr != pLast )
            {
                // generic case
                pPrev->fpNext   = pCurr->fpNext;
                pLast->fpNext   = pCurr;
                pLast           = pLast->fpNext;
                pCurr           = pPrev->fpNext;
            }

            pLast->fpNext   = nullptr;
        }
        else
        {
            // if the current element does NOT satisfy the predicate
            // keep it where it is and continue with the next element

            pPrev   = pCurr;
            pCurr   = pCurr->fpNext;
        }
    }
}


void erase_after( Node* pElem )
{
    if ( pElem == nullptr )
        return; // erase after end of list, means do nothing

    if ( pElem->fpNext == nullptr )
        return; // erase after the last element still does nothing

    Node*   pToDel  = pElem->fpNext;
    pElem->fpNext   = pToDel->fpNext;

    delete pToDel;
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


void printList( const Node* pHead )
{
    while ( pHead )
    {
        std::cout << pHead->fData << ' ';
        pHead   = pHead->fpNext;
    }
}


bool isEven( int num )
{
    return num % 2 == 0;
}
