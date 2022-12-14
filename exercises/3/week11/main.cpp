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
    if (nullptr == root)
    {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
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

    print(root->left);                    // ляво
    std::cout << root->data << std::endl; // корен
    print(root->right);                   // дясно
}

template <typename T, T startValue>
T sum(node<T> *root)
{
    if (nullptr == root)
    {
        return startValue;
    }

    return root->data + sum<T, startValue>(root->left) + sum<T, startValue>(root->right);
}

template <typename T>
T sum(node<T> *root, T startValue)
{
    if (nullptr == root)
    {
        return startValue;
    }

    return root->data + sum(root->left, startValue) + sum(root->right, startValue);
}

template <typename T>
size_t height(node<T> *root)
{
    if (nullptr == root)
    {
        return 0;
    }

    return 1 + std::max(height(root->left), height(root->right));
}

int strlen(char *s)
{
    if (s)
        return 1 + strlen(s + 1);
    else
        return 0;
}

int getValue(const node<int> *root)
{
    return nullptr == root ? 0 : root->data;
}

node<int> *getLeft(const node<int> *root)
{
    return nullptr == root ? nullptr : root->left;
}

node<int> *getRight(const node<int> *root)
{
    return nullptr == root ? nullptr : root->right;
}

node<int> *sum(node<int> *root1, node<int> *root2)
{
    if (nullptr == root1 && nullptr == root2)
    {
        return nullptr;
    }
    node<int> *root = create<int>(getValue(root1) + getValue(root2));
    root->left = sum(getLeft(root1), getLeft(root2));
    root->right = sum(getRight(root1), getRight(root2));
    return root;
}

int applyOperation(int left, char operation, int right)
{
    switch (operation)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    default:
        throw "Unsupported operation";
    }
}

template <typename T>
node<T> *coalesce(node<T> *p1, node<T> *p2)
{
    if (p1 != nullptr)
    {
        return p1;
    }
    return p2;
}

node<int> *applyOperations(node<int> *rootLeft, node<char> *rootOperations, node<int> *rootRight,
                           bool leftTreeEnded = false, bool operationsTreeEnded = false, bool rightTreeEnded = false)
{
    if (nullptr == rootLeft || nullptr == rootOperations || nullptr == rootRight)
    {
        return nullptr;
    }

    if (leftTreeEnded && operationsTreeEnded && rightTreeEnded)
    {
        return nullptr;
    }

    int result = applyOperation(rootLeft->data, rootOperations->data, rootRight->data);
    return create<int>(result,
                       applyOperations(coalesce(rootLeft->left, rootLeft),
                                       coalesce(rootOperations->left, rootOperations),
                                       coalesce(rootRight->left, rootRight),
                                       leftTreeEnded || nullptr == rootLeft->left,
                                       operationsTreeEnded || nullptr == rootOperations->left,
                                       rightTreeEnded || nullptr == rootRight->left),
                       applyOperations(coalesce(rootLeft->right, rootLeft),
                                       coalesce(rootOperations->right, rootOperations),
                                       coalesce(rootRight->right, rootRight),
                                       leftTreeEnded || nullptr == rootLeft->right,
                                       operationsTreeEnded || nullptr == rootOperations->right,
                                       rightTreeEnded || nullptr == rootRight->right));
}

int main()
{
    // Builder Pattern
    node<int> *root3 = IntTreeBuilder::create(10).left(5).left(50).left(75).leftLeaf(6).rightLeaf(7).end().right(95).leftLeaf(6).rightLeaf(7).end().right(60).leftLeaf(6).rightLeaf(7).end().end().right(13).rightLeaf(1).end().end().build();
    print(root3);
    std::cout << std::endl;

    node<int> *root4 =
        IntTreeBuilder::create(10)
            .leftLeaf(5)
            .rightLeaf(6)
            .build();
    print(root4);
    std::cout << std::endl;
    std::cout << "sum: " << sum<int, 0>(root4) << std::endl;
    std::cout << "sum: " << sum(root4, 0) << std::endl;
    std::cout << "height: " << height(root4) << std::endl;
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
    std::cout << "sum: " << sum(root1, 0) << std::endl;
    std::cout << "height: " << height(root1) << std::endl;
    std::cout << std::endl;

    node<int> *root2 = create<int>(10);
    root2->left = create<int>(5);
    root2->left->left = create<int>(6);
    root2->left->right = create<int>(7);

    root2->right = create<int>(13);
    root2->right->right = create<int>(1);
    print(root2);
    std::cout << std::endl;

    node<int> *root11 =
        create<int>(5,
                    create<int>(10,
                                create<int>(13),
                                nullptr),
                    create<int>(15,
                                create<int>(7),
                                create<int>(80)));
    node<int> *root12 =
        create<int>(100,
                    create<int>(200,
                                create<int>(400,
                                            create<int>(800),
                                            nullptr),
                                create<int>(500)),
                    create<int>(300,
                                create<int>(600),
                                create<int>(700)));

    node<char> *rootOperations =
        create<char>('+',
                     create<char>('*',
                                  nullptr,
                                  create<char>('-')),
                     create<char>('+',
                                  create<char>('/'),
                                  nullptr));

    node<int> *root13 = sum(root11, root12);
    std::cout << "-----------------------------------" << std::endl;
    print(root13);
    std::cout << "-----------------------------------" << std::endl;

    node<int> *rootResult = applyOperations(root11, rootOperations, root12);
    std::cout << "-----------------------------------" << std::endl;
    print(rootResult);
    std::cout << "-----------------------------------" << std::endl;
    return 0;
}
