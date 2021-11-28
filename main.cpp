#include <iostream>
#include "MyHashMap.h"

int main() {
    HashTable<int, int> table{};
    std::cout << table.size();
    return 0;
}
