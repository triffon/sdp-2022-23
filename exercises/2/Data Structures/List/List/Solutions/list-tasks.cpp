#include <iostream>

struct Node
{
	int		fData;
	Node*	fpNext;
	Node*	fpPrev;
};

// Erases the given node of the doubly linked list 
Node* erase(Node*& pNode);

// Adds an element to the back of the doubly linked list
void push_back(Node*& pHead, Node*& pTail, int data);

// Prints the doubly linked list
void print(const Node* pHead);

// Deletes the doubly linked list
void delete_list(Node* pHead);

// Task 1
void reverse(Node*& pHead, Node*& pTail)
{
    // Will change both pHead and pTail

    Node*   pCurr   = pHead;
    while ( pCurr )
    {
        std::swap( pCurr->fpPrev, pCurr->fpNext );
        pCurr   = pCurr->fpPrev;
    }

    std::swap( pHead, pTail );
}

// Task 2
void remove_repeats(Node* pHead, Node*& pTail)
{
    // May change pTail

    Node*   pCurr   = pHead;
    while ( pCurr->fpNext )
    {
        if ( pCurr->fData == pCurr->fpNext->fData )
        {
            // remove pNext in this case:
            // pCurr <-> pNext <-> pThird

            Node*   pNext   = pCurr->fpNext;
            Node*   pThird  = pNext->fpNext;
            pCurr->fpNext   = pThird;
            if ( pThird )
            {
                pThird->fpPrev  = pCurr;
            }
            else // if ( pNext == pTail )
            {
                // pNext was the tail, fix the original pointer
                pTail   = pCurr;
            }

            delete pNext;

            // The body of this `if` can be replaced by:
            // erase( pCurr->fpNext );
        }
        else
        {
            // only move to the next if we haven't removed
            pCurr   = pCurr->fpNext;
        }
    }
}

// Task 3
void unique(Node* pHead, Node*& pTail)
{
    // May change pTail

    Node*   pCurr   = pHead;
    for ( ; pCurr; pCurr = pCurr->fpNext )
    {
        Node*   pEraser = pCurr->fpNext;
        while ( pEraser )
        {
            if ( pCurr->fData == pEraser->fData )
            {
                if ( pEraser == pTail )
                    pTail   = pEraser->fpPrev;

                pEraser     = erase( pEraser );

                // The body of this `if` can be written as in Task 2
            }
            else
            {
                pEraser = pEraser->fpNext;
            }
        }
    }
}

// Task 4
void append(Node* pHeadLhs, Node* pTailLhs, Node* pHeadRhs, Node* pTailRhs)
{
    if ( pHeadLhs == nullptr )
    {
        pHeadLhs    = pHeadRhs;
        return;
    }

    if ( pTailRhs == nullptr )
    {
        pTailRhs    = pTailLhs;
        return;
    }

    pTailLhs->fpNext    = pHeadRhs;
    pHeadRhs->fpPrev    = pTailLhs;
}

// Task 5
template<class Predicate>
void divide(Node*& pHead, Node*& pTail, Predicate pred)
{
    // May change both pHead and pTail

    if ( pHead == nullptr )
        return;

    // Count length
    size_t  cnt     = 0;
    Node*   pTemp   = pHead;
    while ( pTemp )
    {
        ++cnt;
        pTemp   = pTemp->fpNext;
    }

    // Three pointers used for readibility
    Node* pPrev = pHead->fpPrev;
    Node* pCurr = pHead;
    Node* pNext = pHead->fpNext;

    // Process exactly cnt elements
    for ( size_t i = 0; i < cnt; i++ )
    {
        if ( pred( pCurr->fData ) )
        {
            // Move the head to the next if the head
            // is about to be moved to the back
            if ( pCurr == pHead )
                pHead   = pNext;

            // Connect the two nodes around the current
            if ( pPrev )
                pPrev->fpNext   = pNext;

            if (pNext)
                pNext->fpPrev   = pPrev;

            // Add the current node to the end
            pCurr->fpNext   = nullptr;
            pCurr->fpPrev   = pTail;
            pTail->fpNext   = pCurr;
            pTail           = pCurr;

            // Move the pointers by one except for prev
            pCurr   = pNext;
            if ( pNext )
                pNext = pNext->fpNext;
        }
        else
        {
            // The current element doesn't satisfy the predicate
            // Move all pointers by one
            pPrev   = pCurr;
            pCurr   = pNext;
            if ( pNext )
                pNext   = pNext->fpNext;
        }
    }
}


int main()
{
    // Let's create a list
    Node*   pLstHead    = nullptr;
    Node*   pLstTail    = nullptr;
    push_back( pLstHead, pLstTail, 10 );
    push_back( pLstHead, pLstTail, 10 );
    push_back( pLstHead, pLstTail, 10 );
    push_back( pLstHead, pLstTail, 30 );
    push_back( pLstHead, pLstTail, 30 );
    push_back( pLstHead, pLstTail, 20 );
    push_back( pLstHead, pLstTail, 40 );
    push_back( pLstHead, pLstTail, 20 );
    push_back( pLstHead, pLstTail, 20 );
    push_back( pLstHead, pLstTail, 30 );
    push_back( pLstHead, pLstTail, 10 );

    print( pLstHead );
    std::cout << '\n';

    reverse( pLstHead, pLstTail );

    print( pLstHead );
    std::cout << '\n';

    remove_repeats( pLstHead, pLstTail );

    print( pLstHead );
    std::cout << '\n';

    unique( pLstHead, pLstTail );

    print( pLstHead );
    std::cout << '\n';

    // Delete the list
    delete_list( pLstHead );
    pLstHead    = nullptr;
    pLstTail    = nullptr;

    // And add new elements into the empty list
    push_back( pLstHead, pLstTail, 5 );
    push_back( pLstHead, pLstTail, 2 );
    push_back( pLstHead, pLstTail, 7 );
    push_back( pLstHead, pLstTail, 9 );

    // Creates a second list
    Node*   pLstHead2   = nullptr;
    Node*   pLstTail2   = nullptr;
    push_back( pLstHead2, pLstTail2, 1 );
    push_back( pLstHead2, pLstTail2, 0 );
    push_back( pLstHead2, pLstTail2, 3 );
    push_back( pLstHead2, pLstTail2, 8 );
    push_back( pLstHead2, pLstTail2, 4 );

    print( pLstHead );
    std::cout << '\n';

    print( pLstHead2 );
    std::cout << '\n';

    // Appends the first and the second list
    append( pLstHead, pLstTail, pLstHead2, pLstTail2 );
    // Note: The head and tail of the result list are pLstHead and pLstTail2 !

    print( pLstHead );
    std::cout << '\n';

    divide( pLstHead, pLstTail2, [] ( int num ) { return num % 2 == 0; } );

    print( pLstHead );
    std::cout << '\n';

    delete_list( pLstHead );

	return 0;
}


Node* erase(Node*& pNode)
{
    if ( pNode == nullptr )
        return nullptr;

    if (pNode->fpPrev == nullptr)
    {
        // erasing the head
        Node* pToDel = pNode;
        pNode = pNode->fpNext;
        delete pToDel;

        if (pNode)
            pNode->fpPrev = nullptr;

        return pNode;
    }
    
    if (pNode->fpNext == nullptr)
    {
        // erasing the tail
        Node* pToDel = pNode;
        pNode = pNode->fpPrev;
        delete pToDel;

        if (pNode)
            pNode->fpNext = nullptr;

        return nullptr;
    }

    // general case
    Node* pPrev = pNode->fpPrev;
    Node* pNext = pNode->fpNext;

    pPrev->fpNext = pNext;
    pNext->fpPrev = pPrev;

    delete pNode;
    pNode = pNext;

    return pNode;
}


void push_back(Node*& pHead, Node*& pTail, int data)
{
    Node*   pNewNode    = new Node { data, nullptr, pTail };

    if ( pTail )
    {
        pTail->fpNext   = pNewNode;
        pTail           = pNewNode;
    }
    else
    {
        // there were no elements in the list
        pHead   = pNewNode;
        pTail   = pNewNode;
    }
}


void print(const Node* pHead)
{
    while ( pHead )
    {
        std::cout << pHead->fData << ' ';
        pHead   = pHead->fpNext;
    }
}


void delete_list(Node* pHead)
{
    while ( pHead )
    {
        Node*   pToDel  = pHead;
        pHead   = pHead->fpNext;
        delete pToDel;
    }
}
