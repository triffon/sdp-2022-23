#include <iostream>
#include <vector>
#include <queue>

void print_queue( std::priority_queue<size_t> q )
{
    while ( !q.empty() )
    {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << "\n";
}


size_t stoneGame( const std::vector<size_t>& stones )
{
    std::priority_queue<size_t> q;
    for ( size_t stone : stones )
        q.push( stone );

    print_queue( q );

    while ( q.size() > 1 )
    {
        size_t maxG = q.top();
        q.pop();
        size_t maxL = q.top();
        q.pop();

        size_t res = maxG - maxL;
        if ( res > 0 )
            q.push( res );

        print_queue( q );
    }

    if ( q.size() == 1 )
        return q.top();

    return 0;
}


int main()
{
    std::vector<size_t> vec = { 5, 2, 10, 6, 1, 14 };
    std::cout << stoneGame( vec );

    return 0;
}
