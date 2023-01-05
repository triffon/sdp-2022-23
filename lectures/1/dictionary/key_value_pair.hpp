#ifndef __KEY_VALUE_PAIR_HPP
#define __KEY_VALUE_PAIR_HPP

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
};

#endif