#ifndef __LIST_DICTIONARY_HPP
#define __LIST_DICTIONARY_HPP

#include "key_value_pair.hpp"
#include "llist.hpp"
#include "dictionary.hpp"

template <typename K, typename V>
class ListDictionary : public Dictionary<K, V>, LinkedList<KeyValuePair<K,V>> {
public:
    using KVP = KeyValuePair<K, V>;
    using LinkedList<KVP>::insertLast;
    using LinkedList<KVP>::empty;
    using LinkedList<KVP>::deleteFirst;
    using LinkedList<KVP>::deleteAfter;
    using LinkedList<KVP>::begin;
    using I = LinkedListIterator<KVP>;

    // търсене на стойност по ключ
    V* lookup(K const& key) {
        for(KVP& kvp : *this)
            if (kvp == key)
                return &kvp.value;
        return nullptr; 
    }
    V const* lookup(K const& key) const {
        for(KVP const& kvp : *this)
            if (kvp == key)
                return &kvp.value;
        return nullptr;
    }

    // свързване на ключ със стойност
    bool add(K const& key, V const& value) {
        if (lookup(key) != nullptr)
            return false;
        return insertLast(KVP(key, value));
    }

    // изтриване на стойност, свързана с ключ
    bool remove(K const& key) {
        KVP temp;
        if (empty())
            return false;
        I it = begin();
        if (*it == key) {
            deleteFirst(temp);
            return true; 
        }

        while(it.next() && it.next().get() != key)
            ++it;
        
        return deleteAfter(temp, it);
    }

    // списък от ключове
    LinkedList<K> keys() const {
        LinkedList<K> result;
        for(KVP const& kvp : *this)
            result.insertLast(kvp.key);
        return result;
    }

    // списък от стойности
    LinkedList<V> values() const {
        LinkedList<V> result;
        for(KVP const& kvp : *this)
            result.insertLast(kvp.value);
        return result;
    }

};

#endif