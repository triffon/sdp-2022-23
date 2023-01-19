#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include "llist.hpp"
#include "lqueue.hpp"
#include "lstack.hpp"
#include "set.hpp"

template <typename V, template <typename, typename> class Dictionary>
class Graph : Dictionary<V, LinkedList<V>> {
public:
    using VertexList = LinkedList<V>;
    using VertexIterator = typename VertexList::I;
private:
    using D = Dictionary<V, VertexList>;
    using E = std::pair<V, V>;

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

    VertexList BFS(V const& from, V const& to) const {
        Set<V, Dictionary> visited;
        VertexList path;
        LinkedQueue<V> queue;
        LinkedStack<E> steps;
        queue.enqueue(from);
        visited.insert(from);
        while (!queue.empty() && queue.head() != to) {
            V current = queue.dequeue();
            for(VertexIterator succ = successors(current); succ; ++succ)
                // проверяваме да не зациклим
                if (!visited.contains(*succ)) {
                    // маркираме го като обходен
                    visited.insert(*succ);
                    // добавяме го в опашката
                    queue.enqueue(*succ);
                    // запомняме реброто, по което сме минали
                    steps.push(E{current, *succ});
                }
        }

        if (queue.empty())
            return path;

        // queue.head() == to
        // намерили сме път

        V current = to;
        // добавяме в пътя в обратен ред
        path.insertFirst(current);
        while (!steps.empty()) {
            E edge = steps.pop();
            if (edge.second == current) {
                // намерихме стъпката
                current = edge.first;
                // добавяме в началото, за да получим пътя в правилен ред
                path.insertFirst(current);
            }
        }
        return path;
    }


};

#endif