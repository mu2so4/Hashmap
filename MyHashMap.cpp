#pragma once
#include "MyHashMap.h"
#include <string>

template<typename K, typename V>
const int HashTable<K, V>::HASHTABLE_SIZE = 1024;


template<typename K, typename V>
HashTable<K, V>::HashTable():
        elementsCount(0)
{
    table = new List[HASHTABLE_SIZE];
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    delete[] table;
    table = nullptr;
}

template<typename K, typename V>
HashTable<K, V>::HashTable(const HashTable &b) {
    clear();
    elementsCount = b.elementsCount;
    for(int index = 0; index < HASHTABLE_SIZE - 1; index++)
        table[index] = List(b.table[index]); //?
}

template<typename K, typename V>
HashTable<K, V>::HashTable(HashTable &&b) noexcept:
        elementsCount(b.elementsCount)
{
    delete[] table;
    table = b.table;
    b.table = nullptr;
}

template<typename K, typename V>
HashTable<K, V> &HashTable<K, V>::operator=(const HashTable &b) {
    if(this != &b) {
        clear();
        elementsCount = b.elementsCount;
        for(int index = 0; index < HASHTABLE_SIZE - 1; index++)
            table[index] = List(b.table[index]); //?
    }
    return *this;
}


template<typename K, typename V>
HashTable<K, V> &HashTable<K, V>::operator=(HashTable &&b) noexcept {
    if(b != this) {
        elementsCount = b.elementsCount;
        delete[] table;
        table = b.table;
        b.table = nullptr;
    }
    return *this;
}

template<typename K, typename V>
void HashTable<K, V>::swap(HashTable &b) {
    std::swap(elementsCount, b.elementsCount);
    std::swap(table, b.table);
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    for(int index = 0; index < HASHTABLE_SIZE - 1; index++)
        table[index].clear();
    elementsCount = 0;
}

template<typename K, typename V>
bool HashTable<K, V>::erase(const K &k) {
    if(table[hash(k)].erase(k)) {
        elementsCount--;
        return true;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const K &k, const V &v) {
    if(table[hash(k)].insert(k, v)) {
        elementsCount++;
        return true;
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K &key) const {
    return table[hash(key)].contains(key);
}

template<typename K, typename V>
size_t HashTable<K, V>::size() const {
    return elementsCount;
}

template<typename K, typename V>
bool HashTable<K, V>::empty() const {
    return elementsCount == 0;
}


template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::begin() const {
    for(int index = 0; index < HASHTABLE_SIZE; index++)
        if(table[index].begin != nullptr)
            return Iterator(table[index].begin, table);
    return Iterator(nullptr, table);
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::end() const {
    return Iterator(nullptr, table);
}
