#ifndef __BINTREE_HPP
#define __BINTREE_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode *left, *right;

    BinTreeNode(T const& _data = T(), BinTreeNode* _left = nullptr, BinTreeNode* _right = nullptr) : 
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
class BinTreePosition {
    BinTreeNode<T>* ptr;
    using P = BinTreePosition<T>;
public:
    BinTreePosition(BinTreeNode<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr != nullptr; }

    P left() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return ptr->left;
    }

    P right() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return ptr->right;
    }

    T const& get() const {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return ptr->data;
    }

    T& get() {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return ptr->data;
    }
};

template <typename T>
class BinTree {
    BinTreeNode<T>* rootNode;
    using N = BinTreeNode<T>;
public:
    using P = BinTreePosition<T>;
    BinTree() : rootNode(nullptr) {}

    BinTree(T const& root, BinTree&& left = BinTree(), BinTree&& right = BinTree()) {
        rootNode = new BinTreeNode<T>(root, left.rootNode, right.rootNode);
        left.rootNode = right.rootNode = nullptr;
    }

    /*
    void print(std::ostream& os = std::cout) const {
        rootNode->print(os);
    }
    */

    void print(std::ostream& os = std::cout) const {
        print(os, root());
    }

    void print(std::ostream& os, P pos) const {
        if (!pos.valid())
            os << "()";
        else {
            os << '(' << pos.get() << ' ';
            print(os, pos.left());
            os << ' ';
            print(os, pos.right());
            os << ')';
        }
    }


    P root() const { return P(rootNode); }
};

#endif