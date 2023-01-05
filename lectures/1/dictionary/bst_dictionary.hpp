#ifndef BST_DICTIONARY_HPP
#define BST_DICTIONARY_HPP

#include "dictionary.hpp"
#include "bstree.hpp"
#include "key_value_pair.hpp"

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V>, BinSearchTree<KeyValuePair<K,V>> {
public:

    using KVP = KeyValuePair<K, V>;
    using BinSearchTree<KVP>::search;

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