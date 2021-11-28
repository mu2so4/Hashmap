#ifndef MY_HASHMAP_MYHASHMAP_H
#define MY_HASHMAP_MYHASHMAP_H

#include <string>
template<typename T>
int hash(const T &obj);

template<typename K, typename V>
class HashTable {
    class List;
    class Item;
    static const int HASHTABLE_SIZE;
    List *table;
    size_t elementsCount;

    static int hash(const K &key) {
        return ::hash(key) % (HASHTABLE_SIZE - 1);
    }
public:

    HashTable();
    ~HashTable();

    HashTable(const HashTable &b);
    HashTable(HashTable &&b) noexcept;

    HashTable &operator=(const HashTable &b);
    HashTable &operator=(HashTable &&b) noexcept;

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

    class Iterator;
    Iterator &begin() const;
    Iterator &end() const;

private:
    class List {
        Item *begin = nullptr;
        Item *end = nullptr;
    public:
        List() = default;
        ~List();
        List(const List &list2);

        bool contains(const K &key) const;
        bool insert(const K &key, const V &value);
        bool erase(const K &key);
        void clear();
    };

    class Item {
        K *key;
        V *value;
        Item *next = nullptr;
        Item *prev = nullptr;

    public:
        Item(const K &k, const V &v, const Item &pre);
        ~Item();
        Item(const Item &item2);
    };
public:


    class Iterator {
        Item &currentElement;
        int currentHash;
        List &table;
    public:
        Iterator(const Item &item, const List &arr);
        ~Iterator() = default;

        K &key() const;
        V &value() const;

        Iterator &operator++();
        Iterator &operator--();
        Iterator &operator==(const Iterator &iter) const;
        Iterator &operator!=(const Iterator &iter) const;
    };
};

#endif //MY_HASHMAP_MYHASHMAP_H
