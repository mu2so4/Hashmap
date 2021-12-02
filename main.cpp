#include <iostream>
#include "MyHashMap.h"



int main() {
    HashTable<int, int> table{};
    std::cout << table.size() << '\n';
    int a = 2, b = 4;
    table.insert(a, b);
    std::cout << table.size() << '\n';
    std::cout << table.contains(2) << '\n';
    std::cout << table.contains(4) << '\n';
    std::cout << table.size() << '\n';
    std::cout << table.at(2) << '\n';
    std::cout << table.contains(4) << '\n';
    table.clear();
    const int e = table.at(2);
    std::cout << e << '\n';
    std::cout << table.size() << '\n';
    std::cout << table.at(2) << '\n';
    std::cout << table.contains(4) << '\n';

    return 0;
}
