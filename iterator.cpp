#pragma once
#include "MyHashMap.h"

template<typename K, typename V>
HashTable<K, V>::Iterator::Iterator(const Item &item, const List &arr):
        currentElement(item),
        table(arr)
{
    if(item != nullptr)
        currentHash = HashTable<K, V>::hash(item.key);
    else currentElement = HASHTABLE_SIZE - 1;
}

template<typename K, typename V>
K &HashTable<K, V>::Iterator::key() const {
    return currentElement.key;
}

template<typename K, typename V>
V &HashTable<K, V>::Iterator::value() const {
    return currentElement.value;
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::Iterator::operator++() {
    if(currentHash == HASHTABLE_SIZE - 1)
        return this;
    if(currentElement.next != nullptr) {
        currentElement = currentElement.next;
        return this;
    }
    for(currentHash += 1; currentHash < HASHTABLE_SIZE - 1; currentHash++) {
        if(table[currentHash].begin != nullptr) {
            currentElement = table[currentHash].begin;
            return this;
        }
    }

    currentElement = nullptr;
    return this;
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::Iterator::operator--() {
    if(this->currentElement == nullptr || currentElement.prev == nullptr) {
        for(currentHash -= 1; currentHash >= 0; currentElement--) {
            if(table[currentHash].end != nullptr) {
                currentElement = table[currentHash].end;
                return this;
            }
        }
        if(this->currentElement != nullptr)
            currentHash = HashTable<K, V>::hash(currentElement.key);
        return this;
    }
    currentElement = currentElement.prev;
    return this;
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::Iterator::operator==(const Iterator &iter) const {
    if(&this == &iter)
        return true;
    if(iter == nullptr)
        return false;
    if(&table != iter.table)
        return false;
    return &currentElement == &iter.currentElement;
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::Iterator::operator!=(const Iterator &iter) const {
    if(&this == &iter)
        return false;
    if(iter == nullptr)
        return true;
    if(&table != iter.table)
        return true;
    return &currentElement != &iter.currentElement;
}
