#include <iostream>
#include <vector>
#include "stack/lstack.hpp"
#include "queue/squeue.hpp"

// read elements to a queue
template <typename T>
StaticQueue<T> readN(int n)
{
    StaticQueue<T> q;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Input value: ";
        T element;
        std::cin >> element;
        q.enqueue(element); // push
    }
    return q;
}

// print a queue
template <typename T>
void print(StaticQueue<T> q)
{
    while (!q.empty())
    {
        std::cout << q.dequeue() << std::endl; // pop
    }
}

// print a vector
template <typename T>
void print(std::vector<T> v)
{
    for (T x : v)
    {
        std::cout << x << std::endl;
    }
}

// reverse a queue
template <typename T>
StaticQueue<T> reverse(StaticQueue<T> q)
{
    LinkedStack<T> s;
    while (!q.empty())
    {
        s.push(q.dequeue());
    }
    while (!s.empty())
    {
        q.enqueue(s.pop());
    }
    return q;
}

// reverse a queue
template <typename T>
void reverseRecursiveHelper(StaticQueue<T> &q, StaticQueue<T> &result)
{
    if (q.empty())
    {
        return;
    }
    T element = q.dequeue();
    reverseRecursiveHelper(q, result);
    result.enqueue(element);
}

// reverse a queue
template <typename T>
StaticQueue<T> reverseRecursive(StaticQueue<T> q)
{
    StaticQueue<T> result;
    reverseRecursiveHelper(q, result);
    return result;
}

// vector of -1 5 10 4 123 -9 0 -1
// windowSize = 3
// result:
//  10              -- [-1 5 10]
//  10              -- [5 10 4]
//  123             -- [10 4 123]
//  123             -- [4 123 -9]
//  123             -- [123 -9 0]
//  0               -- [-9 0 -1]

int findMax(StaticQueue<int> q)
{
    int maxValue = q.dequeue();
    while (!q.empty())
    {
        if (maxValue < q.head())
        { // peek; stl queue --> q.front()
            maxValue = q.head();
        }
        q.dequeue(); // q.pop()
    }
    return maxValue;
}

std::vector<int> findSlidingWindowMaxValues(std::vector<int> const &numbers, int windowSize)
{
    StaticQueue<int> window;
    for (int i = 0; i < windowSize; i++)
    {
        window.enqueue(numbers[i]);
    }
    std::vector<int> maxValues;
    maxValues.push_back(findMax(window));
    for (int i = windowSize; i < numbers.size(); i++)
    {
        window.dequeue();
        window.enqueue(numbers[i]);
        maxValues.push_back(findMax(window));
    }
    return maxValues;
}

std::vector<int> findSlidingWindowMaxValuesV2(std::vector<int> const &numbers, int windowSize)
{
    StaticQueue<int> window;
    int windowMaxValue = numbers[0];
    for (int i = 0; i < windowSize; i++)
    {
        window.enqueue(numbers[i]);
        if (windowMaxValue < numbers[i])
        {
            windowMaxValue = numbers[i];
        }
    }
    std::vector<int> maxValues;
    maxValues.push_back(windowMaxValue);
    for (int i = windowSize; i < numbers.size(); i++)
    {
        if (windowMaxValue < numbers[i])
        {
            windowMaxValue = numbers[i];
        }
        window.enqueue(numbers[i]);
        if (windowMaxValue == window.dequeue())
        {
            windowMaxValue = findMax(window);
        }
        maxValues.push_back(windowMaxValue);
    }
    return maxValues;
}

int main()
{
    StaticQueue<int> q = readN<int>(4);
    print(q);
    std::cout << "now print reversed" << std::endl;
    print(reverse(q));
    std::cout << "now print recursively reversed" << std::endl;
    print(reverseRecursive(q));

    std::vector<int> values = {-1, 5, 10, 4, 123, -9, 0, -1};
    std::vector<int> maxValuesV1 = findSlidingWindowMaxValues(values, 3);
    std::vector<int> maxValuesV2 = findSlidingWindowMaxValuesV2(values, 3);

    std::cout << "-------------------------------------------" << std::endl;
    print(maxValuesV1);
    std::cout << "-------------------------------------------" << std::endl;
    print(maxValuesV2);
    std::cout << "-------------------------------------------" << std::endl;

    return 0;
}