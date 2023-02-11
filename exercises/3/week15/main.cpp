#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <list>
#include <iterator>

/*
    Намиране на средния елемент в свързан списък
    while (fastiter->next && fastiter->next->next) {
        iter += 1;
        fastiter += 2;
    }
    iter --> средният елемент
    fastiter --> последният или предпоследният

*/

template <typename T>
void print_T(std::list<T> &l)
{
    // https://en.cppreference.com/w/cpp/language/dependent_name
    typename std::list<T>::iterator iter = l.begin();
    while (iter != l.end())
    {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << std::endl;
}

void print(std::list<int> &l)
{
    std::list<int>::iterator iter = l.begin();
    while (iter != l.end())
    {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << std::endl;
}

std::list<int> copyElements(std::list<int>::iterator from, std::list<int>::iterator to)
{
    std::list<int> result;
    while (from != to)
    {
        result.push_back(*from);
        from++;
    }
    return result;
}

// O(n^2) --> Insertion Sort, Bubble Sort, Shaker Sort, ...
// O(nlogn) --> Merge Sort, QuickSort
// Merge Sort
// [1   6 10  6    124    25 5]
//                  [1,6,10,6]     --> [1, 6, 10] \
//                  [6, 124,25,5]  --> [5, 6, 25, 124]   ->  [1, 5, 6, 6, 10, 25, 124]
void mergeSort(std::list<int> &l)
{
    // recursion end
    if (l.size() <= 1)
    {
        return;
    }

    // split ...
    std::list<int>::iterator middle = l.begin();
    for (int i = 0; i < l.size() / 2; i++)
    {
        middle++;
    }
    std::list<int> firstPart = copyElements(l.begin(), middle);
    std::list<int> secondPart = copyElements(middle, l.end());

    // .. and sort
    mergeSort(firstPart);
    mergeSort(secondPart);

    // merge
    l.clear();
    std::list<int>::iterator iter1 = firstPart.begin();
    std::list<int>::iterator iter2 = secondPart.begin();
    while (iter1 != firstPart.end() && iter2 != secondPart.end())
    {
        if (*iter1 < *iter2)
        {
            l.push_back(*iter1);
            iter1++;
        }
        else
        {
            l.push_back(*iter2);
            iter2++;
        }
    }
    while (iter1 != firstPart.end())
    {
        l.push_back(*iter1);
        iter1++;
    }
    while (iter2 != secondPart.end())
    {
        l.push_back(*iter2);
        iter2++;
    }
}

// graph<int> g;
// int[x][y]
// list<pair<element, list<neigbours>>
//      pair<4, [5,6,7]> 4 --> 5, 4 --> 6, 4 --> 7
// list<pair<element, element>>
//      pair<4,7> 4 --> 7
// насочен и ненасочен граф
//  насочен 4 -->  7,  възможно е 7 -x-> 4
//  несочен 4 -->  7,  задължително 7 --> 4
// претеглени или непретеглени
//  претеглени - ако всяко ребро има тегло (цена)

typedef std::vector<std::vector<bool>> graph;
//   1 2 3 4 5
// 1 x x x x
// 2 x x
// 3 x   x   x
// 4 x     x
// 5     x   x
// ??? 1 --> 5
// търсене в дълбочина (DFS) - stack
// търсене в широчина (BFS) - queue

bool hasPathDFS(graph g, int start, int end, std::vector<bool> &visited)
{
    if (start == end)
    {
        return true;
    }
    if (visited[start])
    {
        return false;
    }
    visited[start] = true;
    for (int v = 0; v < g.size(); v++)
    {
        if (g[start][v] && start != v)
        {
            if (hasPathDFS(g, v, end, visited))
            {
                return true;
            }
        }
    }
    return false;
}

bool hasPathDFS_iter(graph g, int start, int end, std::vector<bool> &visited)
{
    std::stack<int> previousElements;
    previousElements.push(start);

    while (!previousElements.empty())
    {
        int currentVertex = previousElements.top();
        if (currentVertex == end)
        {
            return true;
        }
        if (visited[currentVertex])
        {
            previousElements.pop();
            continue;
        }
        visited[currentVertex] = true;

        for (int v = 0; v < g.size(); v++)
        {
            if (g[currentVertex][v] && currentVertex != v)
            {
                previousElements.push(v);
            }
        }
    }
    return false;
}

bool findPathDFS(graph g, int start, int end, std::vector<bool> &visited, std::vector<int> &path)
{
    if (start == end)
    {
        // path.push_back(start); will return in reverse order
        path.insert(path.begin(), start);
        return true;
    }
    if (visited[start])
    {
        return false;
    }
    visited[start] = true;
    for (int v = 0; v < g.size(); v++)
    {
        if (g[start][v] && start != v)
        {
            if (findPathDFS(g, v, end, visited, path))
            {
                path.insert(path.begin(), start);
                return true;
            }
        }
    }
    return false;
}

bool hasPath(graph g, int start, int end)
{
    std::vector<bool> visited;
    for (int i = 0; i < g.size(); i++)
    {
        visited.push_back(false);
    }
    // return hasPathDFS(g, start, end, visited);
    return hasPathDFS_iter(g, start, end, visited);
}

std::vector<int> findPath(graph g, int start, int end)
{
    std::vector<int> res;
    std::vector<bool> visited;
    for (int i = 0; i < g.size(); i++)
    {
        visited.push_back(false);
    }
    findPathDFS(g, start, end, visited, res);
    return res;
}

// stack / queue / llist / dlist / btree / tree / [hashtable]
// path in graph
int main()
{
    std::list<int> list1 = {1, 6, 10, 6, 124, 25, 5};
    mergeSort(list1);
    std::cout << "==================================" << std::endl;
    print(list1);
    std::cout << "==================================" << std::endl;

    graph g1;
    std::vector<bool> r1 = {true, true, true, true, false};
    std::vector<bool> r2 = {true, true, false, false, false};
    std::vector<bool> r3 = {true, false, true, false, true};
    std::vector<bool> r4 = {true, false, false, true, false};
    std::vector<bool> r5 = {false, false, true, false, true};
    g1.push_back(r1);
    g1.push_back(r2);
    g1.push_back(r3);
    g1.push_back(r4);
    g1.push_back(r5);
    std::cout << hasPath(g1, 0, 4) << std::endl;
    std::cout << "==================================" << std::endl;
    std::vector<int> path = findPath(g1, 0, 4);
    for (std::vector<int>::iterator iter = path.begin(); iter != path.end(); iter++)
    {
        std::cout << *iter << " -> ";
    }
    std::cout << std::endl;
    std::cout << "==================================" << std::endl;

    return 0;
}
