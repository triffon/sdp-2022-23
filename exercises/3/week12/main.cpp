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
class OrderedBinaryTree
{
private:
    node<T> *root;

public:
    OrderedBinaryTree()
    {
        this->root = nullptr;
    }

    OrderedBinaryTree(const OrderedBinaryTree &other)
    {
        copy(other->root);
    }

    OrderedBinaryTree &operator=(const OrderedBinaryTree &other)
    {
        if (this != &other)
        {
            destroy(this->root);
            copy(other);
        }
        return *this;
    }

    ~OrderedBinaryTree()
    {
        destroy(this->root);
    }

    void add(T value)
    {
        add(this->root, value);
    }

    bool contains(T value)
    {
        return contains(this->root, value);
    }

    void print() const
    {
        print(this->root);
        std::cout << std::endl;
    }

    void iterate()
    {
        // TODO: check visitor pattern
    }

private:
    void add(node<T> *&root, T value)
    {
        if (root == nullptr)
        {
            root = new node<T>(value, nullptr, nullptr);
        }
        // else if (value == root->data)
        // {
        //     return;
        // }
        else if (value < root->data)
        {
            add(root->left, value);
        }
        else
        {
            add(root->right, value);
        }
    }

    bool contains(node<T> *root, T value) const
    {
        if (nullptr == root)
        {
            return false;
        }

        if (root->data == value)
        {
            return true;
        }
        else if (value < root->data)
        {
            return contains(root->left, value);
        }
        else
        {
            return contains(root->right, value);
        }
    }

    void print(node<T> *root) const
    {
        if (nullptr == root)
        {
            return;
        }
        print(root->left);              // ляво
        std::cout << root->data << " "; // корен
        print(root->right);             // дясно
    }

    void copy(node<T> *root)
    {
        // TODO
    }

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
};

template <typename T>
class Set
{
private:
    OrderedBinaryTree<T> data;

public:
    void add(T value)
    {
        if (!data.contains(value))
        {
            data.add(value);
        }
    }

    bool contains(T value)
    {
        return data.contains(value);
    }

    void print() const
    {
        data.print();
    }
};

int main()
{
    OrderedBinaryTree<int> tree;
    tree.add(50);
    tree.add(30);
    tree.add(80);
    tree.add(50);
    tree.add(70);
    tree.add(10);
    tree.add(5);
    tree.add(20);
    tree.add(31);
    tree.add(32);
    tree.add(35);

    std::cout << "-----------------------------------" << std::endl;
    tree.print();
    std::cout << "-----------------------------------" << std::endl;
    return 0;
}
