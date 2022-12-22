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
};

template <typename T>
class BinTreePosition {
    BinTreeNode<T>* ptr;
    using P = BinTreePosition<T>;
public:
    BinTreePosition(BinTreeNode<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr != nullptr; }

    operator bool() const { return valid(); }

    P left() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return ptr->left;
    }

    P operator-() const { return left(); }

    P right() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return ptr->right;
    }

    P operator+() const { return right(); }

    T const& get() const {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return ptr->data;
    }

    T const& operator*() const { return get(); }

    T& get() {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return ptr->data;
    }

    T& operator*() { return get(); }

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

    unsigned depth() const { return depth(root()); }

    unsigned depth(P pos) const {
        return pos ? 1 + std::max(depth(-pos), depth(+pos)) : 0;
    }


    P root() const { return P(rootNode); }
};

#endif