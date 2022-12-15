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
node<T> *create(T data, node<T> *left = nullptr, node<T> *right = nullptr)
{
    return new node<T>{data, left, right};
}

template <typename T>
void destroy(node<T> *root)
{
}

class IntTreeBuilder
{
private:
    LinkedStack<node<int> *> currentNode;

    IntTreeBuilder(int rootData)
    {
        currentNode.push(new node<int>(rootData, nullptr, nullptr));
    }

public:
    IntTreeBuilder &left(int data)
    {
        node<int> *newNode = new node<int>(data, nullptr, nullptr);
        currentNode.peek()->left = newNode;
        currentNode.push(newNode);
        return *this;
    }

    IntTreeBuilder &right(int data)
    {
        node<int> *newNode = new node<int>(data, nullptr, nullptr);
        currentNode.peek()->right = newNode;
        currentNode.push(newNode);
        return *this;
    }

    IntTreeBuilder &end()
    {
        currentNode.pop();
        return *this;
    }

    IntTreeBuilder &leftLeaf(int data)
    {
        currentNode.peek()->left = new node<int>(data, nullptr, nullptr);
        return *this;
    }

    IntTreeBuilder &rightLeaf(int data)
    {
        currentNode.peek()->right = new node<int>(data, nullptr, nullptr);
        return *this;
    }

    node<int> *build()
    {
        node<int> *root = currentNode.peek();
        while (!currentNode.empty())
        {
            root = currentNode.pop();
        }
        return root;
    }

    static IntTreeBuilder create(int rootData)
    {
        IntTreeBuilder builder(rootData);
        return builder;
    }
};

template <typename T>
void print(node<T> *root)
{
    if (nullptr == root)
    {
        return;
    }
    std::cout << root->data << std::endl;
    print(root->left);
    print(root->right);
}

int main()
{
    // Builder Pattern
    node<int> *root3 =
        IntTreeBuilder::create(10)
            .left(5)
            .left(50)
            .left(75)
            .leftLeaf(6)
            .rightLeaf(7)
            .end()
            .right(95)
            .leftLeaf(6)
            .rightLeaf(7)
            .end()
            .right(60)
            .leftLeaf(6)
            .rightLeaf(7)
            .end()
            .end()
            .right(13)
            .rightLeaf(1)
            .end()
            .end()
            .build();
    print(root3);
    std::cout << std::endl;

    node<int> *root4 =
        IntTreeBuilder::create(10)
            .leftLeaf(5)
            .rightLeaf(6)
            .build();
    print(root4);
    std::cout << std::endl;

    node<int> *root1 =
        create<int>(10,
                    create<int>(5,
                                create<int>(6),
                                create<int>(7)),
                    create<int>(13,
                                nullptr,
                                create<int>(1)));
    print(root1);
    std::cout << std::endl;

    node<int> *root2 = create<int>(10);
    root2->left = create<int>(5);
    root2->left->left = create<int>(6);
    root2->left->right = create<int>(7);

    root2->right = create<int>(13);
    root2->right->right = create<int>(1);
    print(root2);
    std::cout << std::endl;
    return 0;
}
