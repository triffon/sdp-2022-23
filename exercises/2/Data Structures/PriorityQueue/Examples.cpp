#include "PriorityQueue.hpp"
#include <iostream>

template<typename T> 
void print_queue( T& q )
{
    while ( !q.empty() )
    {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main()
{
    dsa::PriorityQueue<int> q;

    for ( int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2} )
        q.push( n );

    print_queue( q );

    dsa::PriorityQueue<int, std::vector<int>, std::greater<int> > q2;

    for ( int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2} )
        q2.push( n );

    print_queue( q2 );

    return 0;
}