#ifndef __BSTREE_HPP
#define __BSTREE_HPP

#include "bintree.hpp"

template <typename T>
class BinSearchTree : public BinTree<T> {
public:
    using P = BinTreePosition<T>;
    using BinTree<T>::root;

    P search(T const& x) const {
        return P();
    }

    bool insert(T const& x) {
        return false;
    }
};

#endif