#ifndef MY_HASHMAP_MYHASHMAP_H
#define MY_HASHMAP_MYHASHMAP_H

#include <string>
#include <stdexcept>


template<typename K, typename V>
class HashTable {
    class List;
    class Item;
    static const int HASHTABLE_SIZE = 1024;
    List *table = nullptr;
    size_t elementsCount;

    static int hash(const K &key);

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
    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const;

    template<typename Key, typename Value>
    friend bool operator==(const HashTable<Key, Value> &a, const HashTable<Key, Value> &b);
    template<typename Key, typename Value>
    friend bool operator!=(const HashTable<Key, Value> &a, const HashTable<Key, Value> &b);

    class Iterator;

    Iterator begin() const;
    Iterator end() const;

private:
    class List {
        Item *begin = nullptr;
        Item *end = nullptr;
        int size = 0;
    public:
        List() = default;
        ~List();
        List &operator=(const List &list2);

        Item *find(const K &key) const;
        bool contains(const K &key) const;
        bool insert(const K &key, const V &value);
        bool erase(const K &key);
        void clear();

        Item *getBegin() const;
        Item *getEnd() const;

        bool nequals(const List &list2) const;
    };

    class Item {
        K *_key = nullptr;
        V *_value = nullptr;
    public:
        Item *next = nullptr;
        Item *prev = nullptr;

        Item(const K &k, const V &v, Item *pre);
        ~Item();
        Item(const Item &item2);

        K &key() const;
        V &value() const;
    };

public:
    class Iterator {
        Item *currentElement;
        int currentHash;
        const List *table;

    public:
        Iterator(Item *item, const List *arr);
        ~Iterator() = default;

        K &key() const;
        V &value() const;

        Iterator &operator++();
        Iterator &operator--();
        bool operator==(const Iterator &iter) const;

        bool operator!=(const Iterator &iter) const;

    };
};






template<typename K, typename V>
int HashTable<K, V>::hash(const K &key) {
    int k = key % (HASHTABLE_SIZE - 1);
    if(k < 0)
        return k + HASHTABLE_SIZE - 1;
    return k;
}

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
    table = new List[HASHTABLE_SIZE];
    elementsCount = b.elementsCount;
    for(int index = 0; index < HASHTABLE_SIZE - 1; index++)
        table[index] = b.table[index]; //?
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
            table[index] = b.table[index]; //?
    }
    return *this;
}

template<typename K, typename V>
HashTable<K, V> &HashTable<K, V>::operator=(HashTable &&b) noexcept {
    if(&b != this) {
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
bool HashTable<K, V>::contains(const K &k) const {
    return table[hash(k)].contains(k);
}

template<typename K, typename V>
V &HashTable<K, V>::operator[](const K &k) {
    List &list = table[hash(k)];
    Item *item = list.find(k);
    if(item != nullptr)
        return item->value();
    list.insert(k, V());

    return list.getEnd()->value();
}

template<typename K, typename V>
V &HashTable<K, V>::at(const K &k) {
    List &list = table[hash(k)];
    Item *item = list.find(k);
    if(item != nullptr)
        return item->value();
    throw std::runtime_error("Hashmap::&at(const K&) const: key not found");
}

template<typename K, typename V>
V const &HashTable<K, V>::at(const K &k) const {
    List &list = table[hash(k)];
    Item *item = list.find(k);
    if(item != nullptr)
        return item->value();
    throw std::runtime_error("Hashmap::&at(const K&) const: key not found");
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
bool operator==(const HashTable<K, V> &a, const HashTable<K, V> &b) {
    if(a.elementsCount != b.elementsCount)
        return false;
    for(int index = 0; index < HashTable<K, V>::HASHTABLE_SIZE - 1; index++) {
        if(a.table[index].nequals(b.table[index]))
            return false;
    }
    return true;
}

template<typename K, typename V>
bool operator!=(const HashTable<K, V> &a, const HashTable<K, V> &b) {
    if(a.elementsCount != b.elementsCount)
        return true;
    for(int index = 0; index < HashTable<K, V>::HASHTABLE_SIZE - 1; index++) {
        if(a.table[index].nequals(b.table[index]))
            return true;
    }
    return false;
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator HashTable<K, V>::begin() const {
    for(int index = 0; index < HASHTABLE_SIZE; index++)
        if(table[index].getBegin() != nullptr)
            return Iterator(table[index].getBegin(), table);
    return Iterator(nullptr, table);
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator HashTable<K, V>::end() const {
    return Iterator(nullptr, table);
}





template<typename K, typename V>
HashTable<K, V>::List::~List() {
    for(Item *iter = begin; iter != nullptr;) {
        Item *next = iter->next;
        delete iter;
        iter = next;
    }
    begin = end = nullptr; //?
}

template<typename K, typename V>
typename HashTable<K, V>::List &HashTable<K, V>::List::operator=(const List &list2) {
    if(this == &list2 || list2.begin == nullptr)
        return *this;
    clear();
    size = list2.size;
    end = new Item(*list2.begin);
    begin = end;

    for(Item *iter = list2.begin->next; iter != nullptr; iter = iter->next) {
        Item *next = new Item(*iter);
        end->next = next;
        next->prev = end;
        end = next;
    }

    return *this;
}

template<typename K, typename V>
typename HashTable<K, V>::Item *HashTable<K, V>::List::find(const K &key) const {
    for(Item *iter = begin; iter != nullptr; iter = iter->next)
        if(key == iter->key())
            return iter;
    return nullptr;
}

template<typename K, typename V>
bool HashTable<K, V>::List::contains(const K &key) const {
    return find(key) != nullptr;
}

template<typename K, typename V>
bool HashTable<K, V>::List::insert(const K &key, const V &value) {
    if(contains(key))
        return false;
    Item *item = new Item(key, value, end);
    if(begin != nullptr)
        end->next = item;
    else begin = item;
    end = item;
    size++;
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::List::erase(const K &key) {
    Item *item = find(key);
    if(item == nullptr)
        return false;
    if(item == begin)
        begin = item->next;
    if(item == end)
        end = item->prev;
    if(item->prev != nullptr)
        item->prev->next = item->next;
    if(item->next != nullptr)
        item->next->prev = item->prev;
    delete item;
    size--;
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::List::clear() {
    for(Item *iter = begin; iter != nullptr;) {
        Item *next = iter->next;
        delete iter;
        iter = next;
    }
    size = 0;
    begin = end = nullptr;
}

template<typename K, typename V>
typename HashTable<K, V>::Item *HashTable<K, V>::List::getBegin() const {
    return begin;
}

template<typename K, typename V>
typename HashTable<K, V>::Item *HashTable<K, V>::List::getEnd() const {
    return end;
}

template<typename K, typename V>
bool HashTable<K, V>::List::nequals(const List &list2) const {
    if(size != list2.size)
        return true;
    for(auto *iter = begin; iter != nullptr; iter = iter->next) {
        auto *found = list2.find(iter->key());
        if(found == nullptr || found->value() != iter->value())
            return true;
    }
    return false;
}




template<typename K, typename V>
HashTable<K, V>::Item::Item(const K &k, const V &v, Item *pre) {
    _key = new K(k);
    _value = new V(v);
    prev = pre;
}

template<typename K, typename V>
HashTable<K, V>::Item::~Item() {
    delete _key;
    delete _value;
}

template<typename K, typename V>
HashTable<K, V>::Item::Item(const Item &item2) {
    //Item(*item2._key, *item2._value, nullptr);
    _key = new K(item2.key());
    _value = new V(item2.value());
    assert(_key != nullptr);
}

template<typename K, typename V>
K &HashTable<K, V>::Item::key() const {
    return *_key;
}

template<typename K, typename V>
V &HashTable<K, V>::Item::value() const {
    return *_value;
}



template<typename K, typename V>
HashTable<K, V>::Iterator::Iterator(Item *item, const List *arr):
        currentElement(item),
        table(arr)
{
    if(item != nullptr)
        currentHash = HashTable<K, V>::hash(item->key());
    else currentHash = HASHTABLE_SIZE - 1;
}

template<typename K, typename V>
K &HashTable<K, V>::Iterator::key() const {
    return currentElement->key();
}

template<typename K, typename V>
V &HashTable<K, V>::Iterator::value() const {
    return currentElement->value();
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::Iterator::operator++() {
    if(currentHash == HASHTABLE_SIZE - 1)
        return *this;
    if(currentElement->next != nullptr) {
        currentElement = currentElement->next;
        return *this;
    }
    for(currentHash += 1; currentHash < HASHTABLE_SIZE - 1; currentHash++) {
        if(table[currentHash].getBegin() != nullptr) {
            currentElement = table[currentHash].getBegin();
            return *this;
        }
    }

    currentElement = nullptr;
    return *this;
}

template<typename K, typename V>
typename HashTable<K, V>::Iterator &HashTable<K, V>::Iterator::operator--() {
    if(this->currentElement == nullptr || currentElement->prev == nullptr) {
        for(currentHash -= 1; currentHash >= 0; currentElement--) {
            if(table[currentHash].getEnd() != nullptr) {
                currentElement = table[currentHash].getEnd();
                return *this;
            }
        }
        if(this->currentElement != nullptr)
            currentHash = HashTable<K, V>::hash(currentElement->key());
        return *this;
    }
    currentElement = currentElement->prev;
    return *this;
}

template<typename K, typename V>
bool HashTable<K, V>::Iterator::operator==(const Iterator &iter) const {
    if(this == &iter)
        return true;
    if(table != iter.table)
        return false;
    return currentElement == iter.currentElement;
}

template<typename K, typename V>
bool HashTable<K, V>::Iterator::operator!=(const Iterator &iter) const {
    if(this == &iter)
        return false;
    if(table != iter.table)
        return true;
    return currentElement != iter.currentElement;
}

#endif //MY_HASHMAP_MYHASHMAP_H
