#ifndef MY_HASHMAP_MYHASHMAP_H
#define MY_HASHMAP_MYHASHMAP_H

#include <string>

//namespace NewHash {

/*
struct Chessplayer {
    unsigned rating;
    unsigned birthYear;
};
*/

//typedef std::string Key;
//typedef Chessplayer Value;

    template<typename K, typename V>
    class HashTable {
        struct Item {
            K key;
            V value;
            Item *next = nullptr;
        };
        struct List {
            Item *begin, *end;
        };

        List *table;
        size_t elementsCount, tableSize, uniqueHashCount;
    public:
        HashTable();
        ~HashTable();

        HashTable(const HashTable &b); //copy constructor. We just copy its state: all nodes, all fields. b won't be destroyed
        HashTable(HashTable &&b); //move constructor: b will be destroyed

        //int hash(const K &key);

        HashTable &operator=(const HashTable &b);
        HashTable &operator=(HashTable &&b);

        void swap(HashTable &b);
        void clear();
        bool erase(const K &k);
        bool insert(const K &k, const V &v);
        bool contains(const K &k) const;
        V &operator[](const K &k);
        V &at(const K &k);
        const V &at(const K &k) const;
        size_t size() const;
        bool empty() const;

        friend bool operator==(const HashTable &a, const HashTable &b);
        friend bool operator!=(const HashTable &a, const HashTable &b);
    };
//}


#endif //MY_HASHMAP_MYHASHMAP_H
