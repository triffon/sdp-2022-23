#ifndef __SET_HPP
#define __SET_HPP

#include "llist.hpp"

template <typename T, template <typename, typename> class Dictionary>
class Set : Dictionary<T, bool> {
using D = Dictionary<T, bool>;
public:
    bool empty() const { return D::keys().empty(); }
    bool insert(T const& x) { return D::add(x, true); }
    bool remove(T const& x) { return D::remove(x); }
    bool contains(T const& x) const { return D::lookup(x) != nullptr; }
    LinkedList<T> elements() const { return D::keys(); }
};

#endif