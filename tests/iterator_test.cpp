#include <catch2/catch_test_macros.hpp>
#include "../MyHashMap.h"

TEST_CASE("iterator increment", "[inc]") {
    HashTable<int, int> a;

    const int L1 = 100, R1 = 2048;
    for(int index = L1; index < R1; index++) {
        a.insert(index, index * index);
        a.insert(index + 8000, index);
        a.insert(-index, index - 400);
    }

    auto b = a;

    auto iter = a.begin();
    for(; iter != a.end(); ++iter) {
        REQUIRE(b.contains(iter.key()));
        REQUIRE((b.at(iter.key()) == iter.value()));
        REQUIRE(b.erase(iter.key()));
    }
    REQUIRE(iter == a.end());
    ++iter;
    REQUIRE(iter == a.end());
    REQUIRE(b.empty());
}

TEST_CASE("iterator decrement", "[dec]") {
    HashTable<int, int> a;

    const int L1 = 100, R1 = 2048;
    for(int index = L1; index < R1; index++) {
        a.insert(index, index * index);
        a.insert(index + 8000, index);
        a.insert(-index, index - 400);
    }

    auto b = a;

    auto iter = a.begin();
    ++iter;
    for(; iter != a.end(); ++iter) {
        int pre = iter.value();
        --iter;
        ++iter;
        REQUIRE((iter.value() == pre));
    }
    iter = a.end();
    --iter;
    for(; iter != a.begin(); --iter) {
        REQUIRE(b.contains(iter.key()));
        REQUIRE((b.at(iter.key()) == iter.value()));
        REQUIRE(b.erase(iter.key()));
    }
    REQUIRE(b.size() == 1);
    --iter;
    REQUIRE(iter == a.begin());
}