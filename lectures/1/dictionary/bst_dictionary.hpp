#ifndef BST_DICTIONARY_HPP
#define BST_DICTIONARY_HPP

#include "dictionary.hpp"
#include "bstree.hpp"
#include "key_value_pair.hpp"

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V>, BinSearchTree<KeyValuePair<K,V>> {
private:
    using KVP = KeyValuePair<K, V>;
    using P = BinTreePosition<KVP>;
    void collectKeys  (P pos, LinkedList<K>& keys) const {
        if (pos) {
            keys.insertLast((*pos).key);
            collectKeys(-pos, keys);
            collectKeys(+pos, keys);
        }
    }
    void collectValues(P pos, LinkedList<V>& values) const {
        if (pos) {
            values.insertLast((*pos).value);
            collectValues(-pos, values);
            collectValues(+pos, values);
        }

    }
public:

    using BinSearchTree<KVP>::search;
    using BinSearchTree<KVP>::insert;
    using BinSearchTree<KVP>::root;

    // търсене на стойност по ключ
    V* lookup(K const& key) {
        P pos = search(key);
        if (!pos)
            return nullptr;
        return &(*pos).value;
    }

    V const* lookup(K const& key) const {
        P pos = search(key);
        if (!pos)
            return nullptr;
        return &(*pos).value;
    }

    // свързване на ключ със стойност
    bool add(K const& key, V const& value) {
        return insert(KVP(key, value));
    }

    // изтриване на стойност, свързана с ключ
    bool remove(K const& key) {
        //std::ofstream of("bstdict.dot");
        //BinSearchTree<KVP>::DOTprint(of);
        return BinSearchTree<KVP>::remove(key);
    }

    // списък от ключове
    LinkedList<K> keys() const {
        LinkedList<K> result;
        collectKeys(root(), result);
        return result;
    }

    // списък от стойности
    LinkedList<V> values() const {
        LinkedList<V> result;
        collectValues(root(), result);
        return result;
    }

};

#endif