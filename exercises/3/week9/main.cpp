#include <iostream>
#include <vector>
#include "stack/lstack.hpp"
#include "queue/squeue.hpp"
#include "list/llist.hpp"

LinkedList<int> read(int n)
{
    LinkedList<int> result;
    std::cout << "type in " << n << " numbers: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        result.insertLast(x); /// !!!
    }
    return result;
}

void print(const LinkedList<int> &list)
{
    for (LinkedList<int>::I iter = list.begin(); iter != list.end(); iter++)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void appendAllRemaining(LinkedList<int> &result, LinkedList<int>::I i, const LinkedList<int>::I &end)
{
    while (i != end)
    {
        result.insertLast(*i);
        i++;
    }
}

// Merge 2 sorted lists
LinkedList<int> merge(LinkedList<int> &l1, LinkedList<int> &l2)
{
    LinkedList<int> result;
    LinkedList<int>::I i1 = l1.begin();
    LinkedList<int>::I i2 = l2.begin();
    while (i1 != l1.end() && i2 != l2.end())
    {
        if (*i1 <= *i2)
        {
            result.insertLast(*i1);
            i1++;
        }
        else
        {
            result.insertLast(*i2);
            i2++;
        }
    }
    appendAllRemaining(result, i1, l1.end());
    appendAllRemaining(result, i2, l2.end());
    return result;
}

// Merge K sorted lists
LinkedList<int> mergev1(LinkedList<LinkedList<int>> &list)
{
    LinkedList<int> result;
    for (LinkedList<LinkedList<int>>::I iter = list.begin(); iter != list.end(); iter++)
    {
        result = merge(result, *iter);
    }
    return result;
}

// Merge K sorted lists
LinkedList<int> mergev2(LinkedList<LinkedList<int>> &list)
{
    LinkedList<int> result;
    LinkedList<std::pair<LinkedList<int>::I, LinkedList<int>::I>> iterators;
    for (LinkedList<LinkedList<int>>::I iter = list.begin(); iter != list.end(); iter++)
    {
        iterators.insertLast(std::pair<LinkedList<int>::I, LinkedList<int>::I>((*iter).begin(), (*iter).end()));
    }

    LinkedList<std::pair<LinkedList<int>::I, LinkedList<int>::I>>::I iter = iterators.begin();
    for (int i = 0; i < 3; i++)
    {
        LinkedList<std::pair<LinkedList<int>::I, LinkedList<int>::I>>::I minIterator = iterators.begin();
        while (iter != iterators.end())
        {
            std::cout << "*(*minIterator).first: " << (*(*minIterator).first) << " comparing to " << (*(*iter).first) << std::endl;
            if ((*(*iter).first) < (*(*minIterator).first))
            {
                minIterator = iter;
            }
            iter++;
        }
        result.insertLast(*(*minIterator).first);
        (*minIterator).first++;
    }

    return result;
}

int main()
{
    LinkedList<LinkedList<int>> list;
    {
        LinkedList<int> sublist;
        sublist.insertLast(1);
        sublist.insertLast(2);
        sublist.insertLast(30);
        sublist.insertLast(40);
        list.insertLast(sublist);
    }
    {
        LinkedList<int> sublist;
        sublist.insertLast(-1);
        sublist.insertLast(0);
        sublist.insertLast(1);
        sublist.insertLast(15);
        list.insertLast(sublist);
    }
    {
        LinkedList<int> sublist;
        sublist.insertLast(10);
        sublist.insertLast(20);
        sublist.insertLast(101);
        sublist.insertLast(102);
        list.insertLast(sublist);
    }
    print(mergev2(list));
    return 0;
}
