#ifndef __BINTREE_HPP
#define __BINTREE_HPP

#include <iostream>

template <typename T>
struct TreeNode {
    T data;
    TreeNode *left, *right;

    TreeNode(T const& _data = T(), TreeNode* _left = nullptr, TreeNode* _right = nullptr) : 
        data(_data), left(_left), right(_right) {}

    void print(std::ostream& os = std::cout) const {
        os << '(' << data << ' ';
        if (left == nullptr)
            os << "()";
        else
            left->print(os);
        os << ' ';
        if (right == nullptr)
            os << "()";
        else
            right->print(os);
        os << ')';
    }
};

template <typename T>
class BinTree {
    TreeNode<T>* rootNode;
public:
    BinTree() : rootNode(nullptr) {}

    BinTree(T const& root, BinTree&& left = BinTree(), BinTree&& right = BinTree()) {
        rootNode = new TreeNode<T>(root, left.rootNode, right.rootNode);
        left.rootNode = right.rootNode = nullptr;
    }

    void print(std::ostream& os = std::cout) const {
        rootNode->print(os);
    }
};

#endif