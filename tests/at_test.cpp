#include <catch2/catch_test_macros.hpp>
#include "../MyHashMap.h"

TEST_CASE("at test", "[at]") {
    SECTION("simple at invoking") {
        HashTable<int, int> a;
        const int LEFT = -1024, RIGHT = 2048;
        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index + 19);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a.at(index) == index + 19);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index - 19);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a.at(index) == index + 19);
        }
        a.insert(LEFT-1, 100000);
        REQUIRE(a.at(LEFT-1) == 100000);
    }

    SECTION("at invoking with the same hash") {
        HashTable<int, int> b;
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
        }
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
            REQUIRE(b.at(6 + index * 1023) == index * 6);
        }

        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index + 6);
        }
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
            REQUIRE(b.at(6 + index * 1023) == index * 6);
        }
    }
}

TEST_CASE("brackets test", "[brackets]") {

    SECTION("simple at invoking") {
        HashTable<int, int> a;
        const int LEFT = -1024, RIGHT = 2048;
        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index + 19);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a[index] == index + 19);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index - 19);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a[index] == index + 19);
        }
        a.insert(LEFT-1, 100000);
        REQUIRE(a[LEFT-1] == 100000);

        for(int index = RIGHT; index < RIGHT * 2; index++)
            REQUIRE(a[index] == 0);
    }

    SECTION("at invoking with the same hash") {
        HashTable<int, int> b;
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
        }
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
            REQUIRE(b[6 + index * 1023] == index * 6);
        }

        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index + 6);
        }
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
            REQUIRE(b[6 + index * 1023] == index * 6);
        }

        for(int index = 200; index < 400; index++)
            REQUIRE(b[index * 1023] == 0);
    }
}