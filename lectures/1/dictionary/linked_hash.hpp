#ifndef __LINKED_HASH_CPP
#define __LINKED_HASH_CPP

#include <cstddef>
#include "dictionary.hpp"

template <typename K>
using HashFunction = unsigned (*)(K const&);

template <typename K>
unsigned trivialHashFunction(K const& key) {
    return key;
}

template <typename K, typename V, HashFunction<K> hashFunction = trivialHashFunction<K>, size_t TABLE_SIZE = 100>
class LinkedHashTable : public Dictionary<K, V> {
public:
    // търсене на стойност по ключ
    V* lookup(K const& key) {
        return nullptr;
    }

    V const* lookup(K const& key) const {
        return nullptr;
    }

    // свързване на ключ със стойност
    bool add(K const& key, V const& value) {
        return false;
    }

    // изтриване на стойност, свързана с ключ
    bool remove(K const& key) {
        return false;
    }

    // списък от ключове
    LinkedList<K> keys() const {
        return LinkedList<K>();
    }

    // списък от стойности
    LinkedList<V> values() const {
        return LinkedList<V>();
    }

};

#endif