#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include "llist.hpp"

template <typename V, template <typename, typename> class Dictionary>
class Graph : Dictionary<V, LinkedList<V>> {
public:
    using VertexList = LinkedList<V>;
    using VertexIterator = typename VertexList::I;
private:
    using D = Dictionary<V, VertexList>;

public:
    VertexList vertices() const { return D::keys(); }

    VertexIterator successors(V const& u) const {
        VertexList const* vl = D::lookup(u);
        if (vl == nullptr)
            return VertexIterator();
        return vl->begin();
    }

    bool isEdge(V const& u, V const& v) const {
        VertexList const* vl = D::lookup(u);
        if (vl == nullptr)
            return false;
        VertexIterator it = vl->find(v);
        return it.valid();
    }

    bool addVertex(V const& u) {
        return D::add(u, VertexList());
    }

    bool removeVertex(V const& u) {
        // TODO: за домашно
        return false;
    }

    bool addEdge(V const& u, V const& v) {
        VertexList* vl = D::lookup(u);
        if (vl == nullptr)
            return false;
        vl->insertLast(v);
        return true;
    }

    bool removeEdge(V const& u, V const& v) {
        VertexList* vl = D::lookup(u);
        if (vl == nullptr)
            return false;
        VertexIterator vi = vl->find(v);
        if (!vi)
            return false;
        V tmp;
        return vl->deleteAt(tmp, vi);
    }

};

#endif