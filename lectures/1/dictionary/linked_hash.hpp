#ifndef __LINKED_HASH_CPP
#define __LINKED_HASH_CPP

#include <cstddef>
#include "dllist.hpp"
#include "dictionary.hpp"
#include "key_value_pair.hpp"

template <typename K>
using HashFunction = unsigned (*)(K const&);

template <typename K>
unsigned trivialHashFunction(K const& key) {
    return key;
}

template <typename K, typename V, HashFunction<K> hashFunction = trivialHashFunction<K>, size_t TABLE_SIZE = 100>
class LinkedHashTable : public Dictionary<K, V> {
private:
    using KVP = KeyValuePair<K, V>;
    using Bucket = DoubleLinkedList<KVP>;
    using I = typename Bucket::I;

    Bucket table[TABLE_SIZE];

    Bucket& findBucket(K const& key) {
        return table[hashFunction(key) % TABLE_SIZE];
    }

    Bucket const& findBucket(K const& key) const {
        return table[hashFunction(key) % TABLE_SIZE];
    }

    size_t count, buckets, collisions;

public:
    LinkedHashTable() : count(0), buckets(0), collisions(0) {}

    // търсене на стойност по ключ
    V* lookup(K const& key) {
        Bucket& bucket = findBucket(key);
        I it = bucket.find(key);
        if (!it)
            return nullptr;
        return &(*it).value;
    }

    V const* lookup(K const& key) const {
        Bucket const& bucket = findBucket(key);
        I it = bucket.find(key);
        if (!it)
            return nullptr;
        return &(*it).value;
    }

    // свързване на ключ със стойност
    bool add(K const& key, V const& value) {
        Bucket& bucket = findBucket(key);
        I it = bucket.find(key);
        if (it)
            return false;
        count++;
        if (bucket.empty())
            buckets++;
        else
            collisions++;
        return bucket.insertLast(KVP(key, value));        
    }

    // изтриване на стойност, свързана с ключ
    bool remove(K const& key) {
        Bucket& bucket = findBucket(key);
        I it = bucket.find(key);
        if (!it)
            return false;
        KVP tmp;
        count--;
        bucket.deleteAt(tmp, it);
        if (bucket.empty())
            buckets--;
        else
            collisions--;
        return true;
    }

    // списък от ключове
    LinkedList<K> keys() const {
        LinkedList<K> result;
        for (Bucket const& bucket : table)
            for (KVP const& kvp : bucket)
                result.insertLast(kvp.key);
        return result;
    }

    // списък от стойности
    LinkedList<V> values() const {
        LinkedList<V> result;
        for (Bucket const& bucket : table)
            for (KVP const& kvp : bucket)
                result.insertLast(kvp.value);
        return result;  
    }

    void info(std::ostream& os = std::clog) const {
        os << "елементи: " << count << ", кофи: " << buckets << ", колизии: " << collisions << std::endl;
    }

};

#endif