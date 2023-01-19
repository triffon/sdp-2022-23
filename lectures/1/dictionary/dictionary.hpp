#ifndef __DICTIONARY_HPP
#define __DICTIONARY_HPP

#include <iostream>
#include "llist.hpp"

template <typename K, typename V>
class Dictionary {
public:
    // търсене на стойност по ключ
    virtual V* lookup(K const& key) = 0;
    virtual V const* lookup(K const& key) const = 0;

    // свързване на ключ със стойност
    virtual bool add(K const& key, V const& value) = 0;

    // промяна на стойност, свързана с ключ
    void set(K const& key, V const& newValue) {
        V* pValue = lookup(key);
        if (pValue)
            *pValue = newValue;
        else
            add(key, newValue);
    }

    // изтриване на стойност, свързана с ключ
    virtual bool remove(K const& key) = 0;

    // списък от ключове
    virtual LinkedList<K> keys() const = 0;

    // списък от стойности
    virtual LinkedList<V> values() const = 0;

    // информация за речника
    virtual void info(std::ostream& os = std::clog) const {}

    virtual ~Dictionary() {}
};

#endif