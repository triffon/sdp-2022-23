#ifndef __BSTREE_HPP
#define __BSTREE_HPP

#include "bintree.hpp"


template <typename T>
class BinSearchTree : public BinTree<T> {
public:
    using P = BinTreePosition<T>;
    using MP = BinTreeMutatingPosition<T>;
    using BinTree<T>::root;
    using BinTree<T>::mutatingRoot;

    template <typename P>
    static P searchFrom(P pos, T const& x) {
        while(pos && *pos != x)
            if (x < *pos)
                --pos;
            else
                ++pos;
        // !pos || *pos == x
        return pos;
    }

    P search(T const& x) const {
        return searchFrom(root(), x);
    }

    MP search(T const& x) {
        return searchFrom(mutatingRoot(), x);
    }

    bool insert(T const& x) {
        MP pos = search(x);
        if (pos)
            return false;
        pos.createLeaf(x);
        return true;
    }
};

#endif