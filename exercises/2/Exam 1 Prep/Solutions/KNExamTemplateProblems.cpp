#include <iostream>

// Basic template forward list Node structure
template<class Type>
struct Node
{
    Type        fData;
    Node<Type>* fpNext;
};


// problem 3
template<class T>
bool dupsub( Node<T>* pHead, unsigned k );

// problem 4
template<class T>
void mirror( Node<T>* pHead );

template<class T>
void insertAfter( Node<T>* pNode, const T& elem );

template<class T>
void clearList( Node<T>*& pHead );      // Note the reference!

template<class T>
void printList( const Node<T>* pHead ); // Note the const!

template <class T>
bool firstKElemsMatch( const Node<T>* pLst1, const Node<T>* pLst2, unsigned k ); // Note the consts!


int main()
{
    Node<char>* pList   = 
        new Node<char> { 'a',
            new Node<char> { 'b',
                new Node<char> { 'b',
                    new Node<char> { 'c', nullptr }
                }
            }
        };

    std::cout << "list: \t\t";
    printList( pList );
    std::cout << '\n';

    std::cout << "mirror: \t";
    mirror( pList );
    printList( pList );
    std::cout << '\n';

    std::cout << "dupbsub k = 2:\t";
    std::cout << std::boolalpha << dupsub( pList, 2 ) << '\n';

    // Do NOT forget to delete your memory!!!
    clearList( pList ); 

    return 0;
}


template<class T>
bool dupsub( Node<T>* pHead, unsigned k )
{
    Node<T>*    pSecond = pHead;

    while ( pHead != nullptr )
    {
        pSecond = pHead->fpNext;

        while ( pSecond != nullptr )
        {
            if ( firstKElemsMatch( pHead, pSecond, k ) )
                return true;
            
            pSecond = pSecond->fpNext;
        }

        pHead   = pHead->fpNext;
    }

    return false;
}


template <class T>
bool firstKElemsMatch( const Node<T>* pLst1, const Node<T>* pLst2, unsigned k )
{
    while (     pLst1 != nullptr
            &&  pLst2 != nullptr 
            &&  pLst1->fData == pLst2->fData
            &&  k > 0 )
    {
        pLst1   = pLst1->fpNext;
        pLst2   = pLst2->fpNext;
        k--;
    }

    return k == 0;
}


template<class T>
void mirror( Node<T>* pHead )
{
    if ( pHead == nullptr )
        return;

    // find the last node
    Node<T>*    pLast   = pHead;
    while ( pLast->fpNext != nullptr )
        pLast   = pLast->fpNext;

    // insert elements just after the original last node
    while ( pHead != pLast->fpNext )
    {
        insertAfter( pLast, pHead->fData );
        pHead   = pHead->fpNext;
    }
}


template<class T>
void insertAfter( Node<T>* pNode, const T& elem )
{
    if ( pNode == nullptr )
        return;

    Node<T>* newNode = new Node<T> { elem, pNode->fpNext };
    pNode->fpNext = newNode;
}


template<class T>
void clearList( Node<T>*& pHead )
{
    Node<T>*    pToDel  = pHead;

    while ( pToDel )
    {
        pHead   = pHead->fpNext;
        delete pToDel;
        pToDel  = pHead;
    }
}


template<class T>
void printList( const Node<T>* pHead )
{
    while ( pHead != nullptr )
    {
        std::cout << pHead->fData << ' ';
        pHead   = pHead->fpNext;
    }
}
