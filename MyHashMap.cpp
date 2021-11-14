#include "MyHashMap.h"
#include <string>

//namespace NewHash {
    template<typename K, typename V>
    HashTable<K, V>::HashTable() {
        table = new List[6];
        tableSize = 6;
        elementsCount = uniqueHashCount = 0;
    }

    template<typename K, typename V>
    HashTable<K, V>::~HashTable() {
        for (int index = 0; index < uniqueHashCount; index++) {
            while (table[index].begin) {
                Item *next = table[index].begin.next;
                ~table[index].begin;
                table[index].begin = next;
            }
        }
        ~table;
        elementsCount = uniqueHashCount = tableSize = 0;
    }

    template<typename K, typename V>
    size_t HashTable<K, V>::size() const {
        return elementsCount;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::empty() const {
        return elementsCount == 0;
    }
//}