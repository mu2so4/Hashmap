#include <catch2/catch_test_macros.hpp>
#include "../MyHashMap.h"

TEST_CASE( "insertion-test", "[int-int]" ) {
    SECTION("simple inserting") {
        HashTable<int, int> a;
        const int LEFT = -1024, RIGHT = 2048;
        for(int index = LEFT; index < RIGHT; index++)
            REQUIRE(a.insert(index, index + 19));
        for(int index = LEFT; index < RIGHT; index++)
            REQUIRE(!a.insert(index, index - 16));
        REQUIRE(a.insert(LEFT-1, 100000));
        REQUIRE(a.insert(RIGHT, 52151));
    }

    SECTION("inserting with the same hash") {
        HashTable<int, int> b;
        for(int index = 0; index < 18000; index += 1023)
            REQUIRE(b.insert(index, index * 6));
        for(int index = 0; index < 18000; index += 1023)
            REQUIRE(!b.insert(index, index + 6));
    }
}

TEST_CASE( "sizes test", "[sizes]" ) {
    SECTION("simple sizes") {
        HashTable<int, int> a;
        REQUIRE(a.empty());
        const int LEFT = -1024, RIGHT = 2048;
        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index + 19);
            REQUIRE(a.size() == index - LEFT + 1);
        }
        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index - 19);
            REQUIRE(a.size() == RIGHT - LEFT);
        }
        a.insert(LEFT-1, 100000);
        REQUIRE(a.size() == RIGHT - LEFT + 1);
    }

    SECTION("inserting with the same hash") {
        HashTable<int, int> b;
        REQUIRE(b.empty());
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
            REQUIRE(b.size() == index + 1);
        }

        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index + 6);
            REQUIRE(b.size() == 200);
        }
    }
}

TEST_CASE( "containing test", "[contains]" ) {
    SECTION("simple contains") {
        HashTable<int, int> a;
        const int LEFT = -1024, RIGHT = 2048;

        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(!a.contains(index));
        }

        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index + 19);
            REQUIRE(a.contains(index));
        }

        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index - 19);
            REQUIRE(a.contains(index));
        }

        a.insert(LEFT-1, 100000);
        REQUIRE(a.contains(LEFT-1));
    }

    SECTION("contains with the same hash") {
        HashTable<int, int> b;
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
            REQUIRE(b.contains(6 + index * 1023));
        }

        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index + 6);
            REQUIRE(b.contains(6 + index * 1023));
        }
    }
}

TEST_CASE( "erasing test", "[erase]" ) {
    SECTION("simple erasing") {
        HashTable<int, int> a;
        const int LEFT = -1024, RIGHT = 2048;

        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(!a.erase(index));
        }

        for(int index = LEFT; index < RIGHT; index++) {
            a.insert(index, index + 19);
        }

        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a.erase(index));
        }

        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(!a.contains(index));
        }

        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a.insert(index, index - 19));
        }

        for(int index = LEFT; index < RIGHT; index++) {
            REQUIRE(a.erase(index));
        }

        a.insert(LEFT-1, 100000);
        REQUIRE(a.erase(LEFT-1));
    }

    SECTION("contains with the same hash") {
        HashTable<int, int> b;
        for(int index = 0; index < 200; index++) {
            b.insert(6 + index * 1023, index * 6);
        }
        for(int index = 0; index < 200; index++) {
            REQUIRE(b.erase(6 + index * 1023));
        }
        for(int index = 0; index < 200; index++) {
            REQUIRE(!b.contains(6 + index * 1023));
        }

        for(int index = 0; index < 200; index++) {
            REQUIRE(b.insert(6 + index * 1023, index + 6));
        }
        for(int index = 0; index < 200; index++) {
            REQUIRE(b.erase(6 + index * 1023));
        }
        for(int index = 0; index < 200; index++) {
            REQUIRE(!b.contains(6 + index * 1023));
        }
    }
}
