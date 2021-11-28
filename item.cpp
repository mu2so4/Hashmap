#pragma once
#include "MyHashMap.h"

template<typename K, typename V>
HashTable<K, V>::Item::Item(const K &k, const V &v, const Item &pre) {
    key = new K(k);
    value = new V(v);
    prev = pre;
}

template<typename K, typename V>
HashTable<K, V>::Item::~Item() {
    delete key;
    delete value;
}

template<typename K, typename V>
HashTable<K, V>::Item::Item(const Item &item2) {
    key = new K(item2.key);
    value = new V(item2.value);
}
