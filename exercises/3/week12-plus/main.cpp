#include <iostream>
#include <vector>
#include "stack/lstack.hpp"
#include "queue/squeue.hpp"
#include "list/llist.hpp"

template <typename T>
struct node
{
    T data;
    std::vector<node<T> *> children;
    // LinkedList<node<T> *> children;
    // node<T> **children;
};

class LocationTree
{
public:
    LocationTree()
    {
        topLocation = new node<std::string>;
        topLocation->data = "";
    }

    LocationTree(const LocationTree &other)
    {
        topLocation = copyTree(other.topLocation);
    }

    LocationTree &operator=(const LocationTree &other)
    {
        if (this != &other)
        {
            deleteTree(topLocation);
            topLocation = copyTree(other.topLocation);
        }
        return *this;
    }

    ~LocationTree()
    {
        deleteTree(topLocation);
    }

    void addRootLocation(std::string newLocation)
    {
        addLocation({}, newLocation);
    }

    // parentLocation: "Община , град 2 , квартал 2.2", newLocation: "улица ала бала 14"
    void addLocation(std::vector<std::string> parentLocation, std::string newLocation)
    {
        // find the parent location under the topLocation tree
        node<std::string> *parentNode = find(topLocation, parentLocation);
        if (nullptr == parentNode)
        {
            throw "Element not found";
        }
        // use insertion sort logic to add the newLocation in the sorted childrens list
        addSorted(parentNode->children, newLocation);
    }

    /*
     * Община
     *      - град 1
     *      - град 2
     *          - квартал 2.1
     *          - квартал 2.2
     *              - улица ала бала 14
     *              - улица портокала 21
     *          - квартал 2.3
     *      - град 3
     *
     * parentLocation: Община / град 2
     * result:
     *  [
     *      Община / град 2 / квартал 2.1
     *      Община / град 2 / квартал 2.2
     *      Община / град 2 / квартал 2.3
     *      Община / град 2 / квартал 2.2 / улица ала бала 14
     *      Община / град 2 / квартал 2.2 / улица портокала 21
     *  ]
     */
    std::vector<std::vector<std::string>> findAllSubLocations(std::vector<std::string> parentLocation)
    {
        std::vector<std::vector<std::string>> result;
        node<std::string> *startingNode = find(topLocation, parentLocation);
        generateAllSubLocations(startingNode, parentLocation, result);
        return result;
    }

    bool contains(std::vector<std::string> parentLocation)
    {
        return nullptr != find(topLocation, parentLocation);
    }

    void print() const
    {
        print(topLocation);
    }

private:
    void generateAllSubLocations(node<std::string> *root, std::vector<std::string> currentPath, std::vector<std::vector<std::string>> &subLocations)
    {
        if (nullptr == root)
        {
            return;
        }

        currentPath.push_back(root->data);
        subLocations.push_back(currentPath);
        for (auto it : children)
        {
            generateAllSubLocations(it, currentPath, subLocations);
        }
    }

    void print(node<std::string> *root) const
    {
        if (root == nullptr)
        {
            return;
        }

        std::cout << root->data << std::endl;

        for (auto it = root->children.begin(); it != root->children.end(); it++)
        {
            print(*it);
        }
    }

    void addSorted(std::vector<node<std::string>> &elements, std::string element)
    {
        size_t start = 0;
        size_t end = elements.size();
        while (start <= end)
        {
            size_t currentIndex = (end - start) / 2;
            if (elements[currentIndex]->data == element)
            {
                throw "Element already exists";
            }
            else if (elements[currentIndex]->data < element)
            {
                start = start;
                end = currentIndex - 1;
            }
            else
            {
                start = currentIndex + 1;
                end = end;
            }
        }
        // [10, 20, 30, 40, 50]
        //  0   1    2   3   4
        // add: 60 [0,4]-->[3,4]-->[4,4]--> [5,4] the place to add the element is on "start" position
        // add: 5  [0,4]-->[0,1]-->[0,-1] the place to add the element is on the "start" position
        // add: 45 [0,4]-->[3,4]-->[4,4]--> [4,3] the place to add the element is on the "start" position

        // adding 45
        // [10, 20, 30, 40, 50] 50
        //  0   1    2   3   4  5
        //                   ^---- start here; and add here
        // adding 5
        // [10, 20, 30, 40, 50] 50
        //  0   1    2   3   4  5
        //  ^ --add here     ^---- start here

        if (start >= elements.size())
        {
            elements.push_back(element);
        }
        elements.push_back(elements[element.size() - 1]);

        for (int i = elements.size() - 2; i >= start && i > 0; i--)
        {
            elements[i] = elements[i - 1];
        }
        elements[start] = element;
    }

    node<std::string> *find(node<std::string> *root, std::vector<std::string> pathInTree)
    {
        if (nullptr == root)
        {
            return nullptr;
        }
        if (root->data == pathInTree[0])
        {
            return root;
        }

        pathInTree.erase(pathInTree.begin());

        std::vector<node<std::string> *>::iterator it = (root->children).begin();
        while (it != root->children.end())
        {
            node<std::string> *res = find(*it, pathInTree);
            if (res != nullptr)
            {
                return res;
            }
            it++;
        }
        return nullptr;
    }

    // we already know that the *root is on the right path. We only care about it's children
    node<std::string> *find_version2(node<std::string> *root, std::vector<std::string> pathInTree)
    {
        node<std::string> *pathNode = findBinarySearch(root->children, pathInTree[0]);
        if (pathNode == nullptr)
        {
            return nullptr;
        }
        if (pathInTree.size() == 1)
        {
            return pathNode;
        }
        pathInTree.erase(pathInTree.begin());
        return find_version2(pathNode, pathInTree);
    }

    // Use Iterative Approach based on path in tree
    node<std::string> *find_version3(node<std::string> *root, std::vector<std::string> pathInTree)
    {
        node<std::string> *currentTreeNode = root;
        for (int i = 0; i < pathInTree.size(); i++)
        {
            node<std::string> *pathNode = findBinarySearch(currentTreeNode->children, pathInTree[0]);
            if (pathNode == nullptr)
            {
                return nullptr;
            }
            if (i == pathInTree.size() - 1)
            {
                return pathNode;
            }
            currentTreeNode = pathNode;
        }
        return nullptr;
    }

    node<std::string> *findBinarySearch(std::vector<node<std::string> *> elements, std::string elementToFind)
    {
        size_t start = 0;
        size_t end = elements.size();
        while (start <= end)
        {
            // [0, 4] --> 2; left [0, 2]; right [3, 4]
            // [0, 5] --> 2; left [0, 2]; right [3, 5]
            size_t currentIndex = (end - start) / 2;
            if (elements[currentIndex]->data == elementToFind)
            {
                return elements[currentIndex];
            }
            else if (elements[currentIndex]->data < elementToFind)
            {
                start = start;
                end = currentIndex - 1;
            }
            else
            {
                start = currentIndex + 1;
                end = end;
            }
        }
        return nullptr;
    }

    node<std::string> *copyTree(node<std::string> *root)
    {
        node<std::string> *result = new node<std::string>();
        result->data = root->data;
        for (auto it = root->children.begin(); it != root->children.end(); it++)
        {
            result->children.push_back(copyTree(*it));
        }
        return result;
    }

    void deleteTree(node<std::string> *root)
    {
        if (nullptr == root)
        {
            return;
        }
        for (auto it = root->children.begin(); it != root->children.end(); it++)
        {
            deleteTree(*it);
        }
        delete root;
    }

    node<std::string> *topLocation; // option 1 - add sentinel
    // std::vector<node<std::string> *> topLocations; // option 2 - forest
};

struct DailySales
{
    std::string storeName;
    std::string date;
    int dailyRevenue;
}

struct Store
{
    std::string storeName;
    std::vector<string> storeLocation;
}

void
printDailyRevenue(std::vector<DailySales> dailySales, std::vector<Store> stores, std::vector<string> location)
{
}

/**
 * List: Магазин, ден, продажби
 *
 * Магазин -> локация ("Община / град 2 / квартал 2.2 / улица ала бала 14")
 * локация: улица + номер / квартал / град / община
 *
 * Община
 *      - град 1
 *      - град 2
 *          - квартал 2.1
 *          - квартал 2.2
 *              - улица ала бала 14
 *              - улица портокала 21
 *          - квартал 2.3
 *      - град 3
 *
 * location: "Община / град 2 / квартал 2.2 / улица ала бала 14"
 * Справка за продажбите за даден ден по зададена локация
 */
int main()
{

    return 0;
}
