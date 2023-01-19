#include <iostream>
#include <vector>
#include <queue>

int main()
{
    std::vector<int>            vec = { 5, 2, 3, 6, 1, 0, 4 };
    std::priority_queue<int>    queue;

    for ( int elem : vec )
        queue.push( elem );

    int k = 4; // kth largest
    for ( size_t i = 0; i < k - 1; i++ )
        queue.pop();
    
    std::cout << queue.top();

    return 0;
}
