#include <iostream>
#include <vector>
#include "stack/lstack.hpp"
#include "queue/squeue.hpp"
#include "list/llist.hpp"

template <typename T>
struct node
{
    T data;
    node<T> *left;
    node<T> *right;

    node(T data, node<T> *left, node<T> *right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

template <typename T>
struct mnode
{
    T data;
    std::vector<mnode<T> *> children;
};

template <typename T>
node<T> *create(T data, node<T> *left = nullptr, node<T> *right = nullptr)
{
    return new node<T>{data, left, right};
}

template <typename T>
void findNumberOfElementsForAllLevels(node<T> *root, std::vector<int> &numberOfElementsPerLevel, int currentLevel)
{
    if (nullptr == root)
    {
        return;
    }
    if (numberOfElementsPerLevel.size() <= currentLevel)
    {
        numberOfElementsPerLevel.push_back(0);
    }
    numberOfElementsPerLevel[currentLevel]++;
    findNumberOfElementsForAllLevels(root->left, numberOfElementsPerLevel, currentLevel + 1);
    findNumberOfElementsForAllLevels(root->right, numberOfElementsPerLevel, currentLevel + 1);
}

template <typename T>
void printNumberOfElementsPerLevel(node<T> *root)
{
    std::vector<int> numberOfElementsPerLevel;
    findNumberOfElementsForAllLevels(root, numberOfElementsPerLevel, 0);
    for (int i = 0; i < numberOfElementsPerLevel.size(); i++)
    {
        std::cout << "Level " << i << ": " << numberOfElementsPerLevel[i] << std::endl;
    }
}

template <typename T>
int findHeight(node<T> *root)
{
    if (nullptr == root)
    {
        return 0;
    }
    return 1 + std::max(findHeight(root->left), findHeight(root->right));
}

template <typename T>
int findNumberOfElementsOnLevel(node<T> *root, int level, int currentLevel = 0)
{
    if (nullptr == root)
    {
        return 0;
    }
    if (level == currentLevel)
    {
        return 1;
    }
    return findNumberOfElementsOnLevel(root->left, level, currentLevel + 1) + findNumberOfElementsOnLevel(root->right, level, currentLevel + 1);
}

template <typename T>
void printNumberOfElementsPerLevel_v2(node<T> *root)
{
    int h = findHeight(root);
    for (int i = 0; i < h; i++)
    {
        std::cout << "Level " << i << ": " << findNumberOfElementsOnLevel(root, i) << std::endl;
    }
}

template <typename T>
void print(mnode<T> *root)
{
    if (nullptr == root)
    {
        return;
    }
    std::cout << root->data << std::endl;
    for (auto child : root->children)
    {
        print(child);
    }
}

template <typename T>
void print(node<T> *root)
{
    if (nullptr == root)
    {
        return;
    }
    print(root->left);
    std::cout << root->data << std::endl;
    print(root->right);
}

template <typename T>
int sumOddLevels(mnode<T> *root, int currentLevel = 1)
{
    if (nullptr == root)
    {
        return 0;
    }
    int sum = 0;
    for (auto child : root->children)
    {
        sum += sumOddLevels(child, currentLevel + 1);
    }
    if (currentLevel % 2 == 1)
    {
        sum += root->data;
    }
    return sum;
}

template <typename T>
node<T> *rotateTree_magicAfter(node<T> *root, node<T> *parent = nullptr)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->right == nullptr)
    {
        root->right = root->left;
        root->left = parent;
        return root;
    }
    node<T> *newRoot = rotateTree_magicAfter(root->right, root);
    root->right = root->left;
    root->left = parent;
    return newRoot;
}

template <typename T>
node<T> *rotateTree(node<T> *root, node<T> *parent = nullptr)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    node<T> *right = root->right;
    root->right = root->left;
    root->left = parent;
    if (right == nullptr)
    {
        return root;
    }
    return rotateTree(right, root);
}

int main()
{
    node<int> *root = create<int>(5,
                                  create<int>(4, create(1), nullptr),
                                  create<int>(10,
                                              create<int>(5),
                                              create<int>(7, create(8), nullptr)));
    printNumberOfElementsPerLevel(root);
    std::cout << "============================================" << std::endl;
    node<int> *treeToRotate = create<int>(1,
                                          create<int>(2, create(4), create(5)),
                                          create<int>(3,
                                                      create<int>(6, create(8), create(9)),
                                                      create<int>(7, create(10), create(11))));
    print(rotateTree_magicAfter(treeToRotate));
    // 1 4 2 5 3 8 6 9 7 10 11
    std::cout << "============================================" << std::endl;
    printNumberOfElementsPerLevel_v2(root);

    mnode<int> *tree2 = new mnode<int>;
    tree2->data = 10;
    {
        mnode<int> *tree21 = new mnode<int>;
        tree21->data = 1;
        {
            mnode<int> *tree211 = new mnode<int>;
            tree211->data = 15;
            tree21->children.push_back(tree211);
        }
        tree2->children.push_back(tree21);
    }
    {
        mnode<int> *tree22 = new mnode<int>;
        tree22->data = 3;
        {
            mnode<int> *tree221 = new mnode<int>;
            tree221->data = 20;
            tree22->children.push_back(tree221);
        }
        {
            mnode<int> *tree222 = new mnode<int>;
            tree222->data = 40;
            {
                mnode<int> *tree2221 = new mnode<int>;
                tree2221->data = 50;
                tree222->children.push_back(tree2221);
            }
            {
                mnode<int> *tree2222 = new mnode<int>;
                tree2222->data = 60;
                tree222->children.push_back(tree2222);
            }
            tree22->children.push_back(tree222);
        }
        {
            mnode<int> *tree223 = new mnode<int>;
            tree223->data = 30;
            tree22->children.push_back(tree223);
        }
        tree2->children.push_back(tree22);
    }
    {
        mnode<int> *tree23 = new mnode<int>;
        tree23->data = 41;
        tree2->children.push_back(tree23);
    }
    {
        mnode<int> *tree24 = new mnode<int>;
        tree24->data = 50;
        tree2->children.push_back(tree24);
    }
    std::cout << "sum of odds: " << sumOddLevels(tree2) << std::endl;

    return 0;
}
