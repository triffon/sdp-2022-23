#ifndef __KEY_VALUE_PAIR_HPP
#define __KEY_VALUE_PAIR_HPP

#include <iostream>

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;

    KeyValuePair(K const& _key = K(), V const& _value = V()) :
        key(_key), value(_value) {}

    bool operator==(KeyValuePair const& kvp) const {
        return key == kvp.key;
    }

    bool operator!=(KeyValuePair const& kvp) const {
        return !(*this == kvp);
    }

    bool operator<(KeyValuePair const& kvp) const {
        return key < kvp.key;
    }

    bool operator>=(KeyValuePair const& kvp) const {
        return !(*this < kvp);
    }

    bool operator<=(KeyValuePair const& kvp) const {
        return !(kvp < *this);
    }

    bool operator>(KeyValuePair const& kvp) const {
        return !(*this <= kvp);
    }

};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, KeyValuePair<K,V> const& kvp) {
    os << '(' << kvp.key << ", " << kvp.value << ')';
}

#endif