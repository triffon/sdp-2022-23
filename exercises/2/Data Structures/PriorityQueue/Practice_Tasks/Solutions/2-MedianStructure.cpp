#include <iostream>
#include <vector>
#include <queue>

class MedianStructure
{
public:
    void push( int elem )
    {
        if ( maxHeap.empty() || elem <= maxHeap.top() )
            maxHeap.push( elem );
        else
            minHeap.push( elem );

        // Keep maxHeap's size either equal to minHeap's size
        // or greater than minHeap's size by exactly one
        if ( minHeap.size() > maxHeap.size() )
        {
            int minHeapTop = minHeap.top();
            minHeap.pop();
            maxHeap.push( minHeapTop );
        }
        else if ( maxHeap.size() > minHeap.size() + 1 )
        {
            int maxHeapTop = maxHeap.top();
            maxHeap.pop();
            minHeap.push( maxHeapTop );
        }
    }


    float median() const
    {
        if ( minHeap.size() == maxHeap.size() )
            return ( minHeap.top() + maxHeap.top() ) * 0.5f;

        return maxHeap.top();
    }

private:
    std::priority_queue<int, std::vector<int>, std::less<int>>      maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>>   minHeap;
};

int main()
{
    std::vector<int> vec = { 5, 2, 3, 6, 1, 0, 4 };

    MedianStructure st;
    for ( int elem : vec )
    {
        st.push( elem );
        std::cout << st.median() << "\n";
    }

    return 0;
}
