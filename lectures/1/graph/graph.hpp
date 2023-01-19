#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include "llist.hpp"
#include "set.hpp"

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

    bool DFS(V const& from, V const& to, Set<V, Dictionary>& visited, VertexList& path) const {
        // обхождаме from
        path.insertLast(from);
        // маркираме го като обходен
        visited.insert(from);

        if (from == to)
            // успешно дъно
            return true;

        for(VertexIterator succ = successors(from); succ; ++succ)
            // проверяваме да не зациклим
            if (!visited.contains(*succ) && DFS(*succ, to, visited, path))
                return true;

        // стъпка назад
        V tmp; // = from
        path.deleteLast(tmp);

        return false;
    }

    VertexList DFS(V const& from, V const& to) const {
        Set<V, Dictionary> visited;
        VertexList path;
        DFS(from, to, visited, path);
        return path;
    }

};

#endif