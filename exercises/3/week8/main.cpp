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

void print(LinkedList<int> &list)
{
    LinkedList<int>::I iter = list.begin(); // !!!!
    while (iter != list.end())              // !!!!
    {
        std::cout << *iter << " "; // !!!!
        iter++;                    // !!!!
    }
    std::cout << std::endl;

    for (LinkedList<int>::I iter = list.begin(); iter != list.end(); iter++)
    {
        std::cout << *iter << " "; // !!!!
    }
    std::cout << std::endl;
}

template <typename T>
LinkedList<LinkedList<T>> breakToGroups(LinkedList<T> list, int maxGroupSize)
{
    LinkedList<LinkedList<T>> groups;
    int counter = 0;
    for (LinkedList<int>::I iter = list.begin(); iter != list.end(); iter++)
    {
        if (0 == counter % maxGroupSize)
        {
            LinkedList<T> newGroup;
            groups.insertLast(newGroup);
        }
        groups.last().get().insertLast(*iter);
        counter++;
    }
    return groups;
}

int listToNumber(LinkedList<int> list)
{
    int number = 0;
    for (LinkedList<int>::I iter = list.begin(); iter != list.end(); iter++)
    {
        number *= 10;
        number += *iter;
    }
    return number;
}

LinkedList<int> numberToList(int n)
{
    LinkedList<int> list;
    while (n != 0)
    {
        list.insertFirst(n % 10);
        n /= 10;
    }
    if (list.empty())
    {
        list.insertFirst(0);
    }
    return list;
}

LinkedList<int> sumNumbers(LinkedList<int> n1, LinkedList<int> n2)
{
    return numberToList(listToNumber(n1) + listToNumber(n2));
}

LinkedList<int> sumNumbersV2(LinkedList<int> n1, LinkedList<int> n2)
{
    n1.reverse();
    n2.reverse();

    LinkedList<int> n;
    LinkedList<int>::I i1 = n1.begin();
    LinkedList<int>::I i2 = n2.begin();
    int inHand = 0; // едно на ум
    while (i1 != n1.end() && i2 != n2.end())
    {
        n.insertFirst((*i1 + *i2 + inHand) % 10);
        inHand = (*i1 + *i2 + inHand) / 10;

        i1++;
        i2++;
    }
    while (i1 != n1.end())
    {
        n.insertFirst((*i1 + inHand) % 10);
        inHand = (*i1 + inHand) / 10;
        i1++;
    }
    while (i2 != n2.end())
    {
        n.insertFirst((*i2 + inHand) % 10);
        inHand = (*i2 + inHand) / 10;
        i2++;
    }
    if (inHand > 0)
    {
        n.insertFirst(inHand);
    }
    return n;
}

template <typename T>
bool equals(const LinkedList<T> &l1, const LinkedList<T> &l2)
{
    LinkedList<int>::I i1 = l1.begin();
    LinkedList<int>::I i2 = l2.begin();
    while (i1 != l1.end() && i2 != l2.end())
    {
        if (*i1 != *i2)
        {
            return false;
        }
    }
    return (i1 == l1.end() && i2 == l2.end());
}

template <typename T>
bool isPalindrome(LinkedList<T> word)
{
    LinkedList<T> reversedWord = word;
    reversedWord.reverse();
    return equals(reversedWord, word);
}

int main()
{
    LinkedList<int> list = read(5);
    print(list);
    return 0;
}
