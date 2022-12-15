#ifndef __TREE_HPP
#define __TREE_HPP

#include <iostream>
#include "llist.hpp"

template <typename T>
class Tree {
private:
    T data;
    LinkedList<Tree> trees;
public:
    // конструктор за листо
    Tree(T const& _data = T()) : data(_data) {}

    // добавяне на поддърво
    void addSubtree(Tree const& t) {
        trees.insertLast(t);
    }

    Tree& operator<<(Tree const& t) {
        addSubtree(t);
        return *this;
    }

    T root() const { return data; }

    LinkedList<Tree> const& subtrees() const { return trees; }

    void print(std::ostream& os = std::cout) const {
        os << '(' << root();
        for(Tree const& subtree : subtrees()) {
            os << ' ';
            subtree.print(os);
        }
        os << ')';
    }
};

#endif