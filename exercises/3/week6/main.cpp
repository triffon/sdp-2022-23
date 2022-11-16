#include <iostream>
#include <vector>
#include "stack/lstack.hpp"
#include "queue/squeue.hpp"
#include <iostream>
#include <vector>

// // coding kata
// std::vector<std::pair<int, int>> combine(std::vector<int> v1, std::vector<int> v2) {
//     std::vector<std::pair<int, int>> result;
//     if (v1.size() == v2.size()) {
//         for (int i = 0; i < v1.size(); i++) {
//             std::pair<int, int> x(v1[i], v2[i]);
//             result.push_back(x);
//         }
//     }
//     return result;  // (1 10) (2 20) (3 30)
// }

std::vector<std::pair<int, int>> combine(std::vector<int> v1, std::vector<int> v2)
{
    if (v1.size() != v2.size())
    {
        std::vector<std::pair<int, int>> result;
        return result;
    }

    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < v1.size(); i++)
    {
        std::pair<int, int> x(v1[i], v2[i]);
        result.push_back(x);
    }
    return result; // (1 10) (2 20) (3 30)
}

std::vector<std::string> breakToPathElements(std::string path)
{
    std::vector<std::string> res;
    // find the first /
    int firstSlashIndex = path.find('/');
    if (firstSlashIndex < 0)
    {
        return res;
    }
    // find the next /
    int nextSlashIndex = path.find('/', firstSlashIndex + 1);
    while (nextSlashIndex >= 0)
    {
        // fetch the text between and add it to a vector
        res.push_back(path.substr(firstSlashIndex + 1, nextSlashIndex - firstSlashIndex - 1));
        firstSlashIndex = nextSlashIndex;
        nextSlashIndex = path.find('/', firstSlashIndex + 1);
    }
    // repeat using the 2nd / as a first one
    return res;
}

LinkedStack<std::string> reverse(LinkedStack<std::string> s)
{
    LinkedStack<std::string> res;
    while (!s.empty())
    {
        res.push(s.pop());
    }
    return res;
}

std::string appendAsPath(LinkedStack<std::string> s)
{
    if (s.empty())
    {
        return "/";
    }

    std::string res;
    while (!s.empty())
    {
        res.append("/");
        res.append(s.pop());
    }
    return res;
}

std::string simplyPath(std::string path)
{
    // extract vector with all words between // in the path
    std::vector<std::string> pathElements = breakToPathElements(path);
    LinkedStack<std::string> currentPath;
    // foreach word in the vector
    for (std::string element : pathElements)
    {
        // check if it's .. --> then pop from the stack
        if (element == "..")
        {
            if (!currentPath.empty())
            {
                currentPath.pop();
            }
        }
        else if (element == "." || element == "")
        {
            // check if it's . --> do nothing
            // check if it's empty --> do nothing
            // do nothing
        }
        else
        {
            // check if it's a word --> push to the stack
            currentPath.push(element);
        }
    }
    // reverse the stack
    currentPath = reverse(currentPath);
    // append all elements from the stack with / between them
    return appendAsPath(currentPath);
}

int main()
{
    std::cout << simplyPath("/home/../test/..//xxxx/././x/./ala/../bala") << std::endl;
    std::cout << simplyPath("/home/../../../") << std::endl;
    return 0;
}
