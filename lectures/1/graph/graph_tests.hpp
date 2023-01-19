#ifndef __GRAPH_TESTS_HPP
#define __GRAPH_TESTS_HPP

#include "doctest.h"
#include "graph.hpp"
#include "linked_hash.hpp"

template <typename K, typename V>
using SimpleLinkedHashTable = LinkedHashTable<K, V, trivialHashFunction, 100>;

using TestGraph = Graph<int, SimpleLinkedHashTable>;

void CHECK_PATH(TestGraph const& graph, TestGraph::VertexList path, int from, int to) {
    TestGraph::VertexIterator vi = path.begin();
    REQUIRE(vi.valid());
    CHECK_EQ(*vi, from);
    while (vi.next()) {
        std::clog << *vi << ' ';
        CHECK(graph.isEdge(*vi, *vi.next()));
        ++vi;
    }
    std::clog << *vi << std::endl;
    CHECK_EQ(*vi, to);
}

TEST_CASE("Добавяне на върхове и ребра в граф") {
    TestGraph g;
    for(int v = 1; v <= 6; v++)
        REQUIRE(g.addVertex(v));
    
    int v = 1;
    for(int u : g.vertices())
        CHECK_EQ(u, v++);

    CHECK_EQ(v, 7);

    REQUIRE(g.addEdge(1, 2));
    REQUIRE(g.addEdge(2, 3));
    REQUIRE(g.addEdge(1, 3));
    REQUIRE(g.addEdge(3, 4));
    REQUIRE(g.addEdge(5, 4));
    REQUIRE(g.addEdge(3, 5));
    REQUIRE(g.addEdge(5, 2));
    REQUIRE(g.addEdge(5, 6));
    REQUIRE(g.addEdge(6, 2));

    CHECK(g.isEdge(1, 3));
    CHECK(!g.isEdge(1, 4));

    SUBCASE("Премахване на ребра") {
        REQUIRE(g.removeEdge(1, 3));
        CHECK(!g.isEdge(1, 3));
        REQUIRE(!g.removeEdge(1, 4));
    }

    SUBCASE("Обхождане на наследници") {
        TestGraph::VertexIterator it = g.successors(1);
        int s = *it;
        CHECK((s == 2 || s == 3));
        ++it;
        CHECK_EQ(*it, 5 - s);
        ++it;
        CHECK(!it);
    }

    SUBCASE("Намиране на път с DFS") {
        CHECK_PATH(g, g.DFS(1, 6), 1, 6);
    }


    SUBCASE("Намиране на път с BFS") {
        CHECK_PATH(g, g.BFS(1, 6), 1, 6);
    }
}

#endif