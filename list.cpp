#pragma once
#include "MyHashMap.h"

template<typename K, typename V>
HashTable<K, V>::List::~List() {
    for(Item &iter = begin; iter != nullptr;) {
        Item &next = iter->next;
        delete iter;
        iter = next;
    }
    begin = end = nullptr; //?
}

template<typename K, typename V>
HashTable<K, V>::List::List(const List &list2) {
    if(list2.begin == nullptr)
        return;
    begin = end = new Item(list2.begin);
    for(Item *iter = list2->begin->next; iter != nullptr; iter = iter->next) {
        end->next = new Item(iter);
        end->next->prev = end->next;
        end = end->next;
    }
}

template<typename K, typename V>
bool HashTable<K,V>::List::contains(const K &key) const {
    for(Item &iter = begin; iter != nullptr; iter = iter.next)
        if(key == iter.key)
            return true;
    return false;
}

template<typename K, typename V>
bool HashTable<K,V>::List::insert(const K &key, const V &value) {
    if(contains(key))
        return false;
    Item *item = new Item(key, value, end);
    end->next = item;
    end = item;
    return true;
}

template<typename K, typename V>
bool HashTable<K,V>::List::erase(const K &key) {
    for(Item *iter = begin; iter != nullptr; iter = iter->next)
        if(key == iter->key) {
            if(iter == begin)
                begin = iter->next;
            if(iter == end)
                end = iter->prev;
            if(iter->prev != nullptr)
                iter->prev->next = iter->next;
            if(iter->next != nullptr)
                iter->next->prev = iter->prev;
            delete iter;
            return true;
        }

    return false;
}

template<typename K, typename V>
void HashTable<K,V>::List::clear() {
    for(Item *iter = begin; iter != nullptr;) {
        Item *next = iter->next;
        delete iter;
        iter = next;
    }
    begin = end = nullptr;
}
