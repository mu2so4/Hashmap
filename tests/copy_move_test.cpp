#include <catch2/catch_test_macros.hpp>
#include "../MyHashMap.h"

TEST_CASE("copy constructor", "[copy_constr]") {
    SECTION("simple copy") {
        HashTable<int, int> a;

        for(int index = 0; index < 12; index++)
            a.insert(index, index + 60);
        HashTable<int, int> b{a};
        REQUIRE(a.contains(4));
        REQUIRE(b.contains(4));
        REQUIRE((a == b));
    }

    SECTION("heavy copy") {
        HashTable<int, int> n;
        const int L1 = 100, R1 = 2048;
        for (int index = L1; index < R1; index++) {
            n.insert(index, index * index);
            n.insert(index + 8000, index);
            n.insert(-index, index - 400);
        }

        HashTable<int, int> m{n}, k{m};

        REQUIRE((n == m));
        REQUIRE((m == k));
        REQUIRE((n == k));
    }
}

TEST_CASE("copy assignment", "[copy_assign]") {
    SECTION("simple copy assignment") {
        HashTable<int, int> a;

        for(int index = 0; index < 12; index++)
            a.insert(index, index + 60);
        HashTable<int, int> b = a;
        REQUIRE(a.contains(4));
        REQUIRE(b.contains(4));
        REQUIRE((a == b));
        a = a;
        REQUIRE((a == b));
    }

    SECTION("heavy copy assignment") {
        HashTable<int, int> n;
        const int L1 = 100, R1 = 2048;
        for(int index = L1; index < R1; index++) {
            n.insert(index, index * index);
            n.insert(index + 8000, index);
            n.insert(-index, index - 400);
        }

        HashTable<int, int> m = n, k = m;

        REQUIRE((n == m));
        REQUIRE((m == k));
        REQUIRE((n == k));

        for(int index = L1; index < R1; index++) {
            REQUIRE((n.at(index) == m.at(index)));
            REQUIRE((n.at(index + 8000) == m.at(index + 8000)));
            REQUIRE((n.at(-index) == m.at(-index)));

            REQUIRE((n.at(index) == k.at(index)));
            REQUIRE((n.at(index + 8000) == k.at(index + 8000)));
            REQUIRE((n.at(-index) == k.at(-index)));
        }

        n = n;
        k = k;
        REQUIRE((n == m));
        REQUIRE((m == k));
        REQUIRE((n == k));
    }
}

TEST_CASE("move constructor", "[move_constr]") {
    SECTION("simple move") {
        HashTable<int, int> a;

        for(int index = 0; index < 12; index++)
            a.insert(index, index + 60);
        HashTable<int, int> b{a}, c{std::move(a)};
        REQUIRE(b.contains(4));
        REQUIRE(c.contains(4));
        REQUIRE((c == b));
    }

    SECTION("heavy move") {
        HashTable<int, int> n;
        const int L1 = 100, R1 = 2048;
        for(int index = L1; index < R1; index++) {
            n.insert(index, index * index);
            n.insert(index + 8000, index);
            n.insert(-index, index - 400);
        }

        HashTable<int, int> m{n}, k{std::move(n)};
        REQUIRE((m == k));
    }
}

TEST_CASE("move assignment", "[move_assign]") {
    SECTION("simple move assignment") {
        HashTable<int, int> a;

        for(int index = 0; index < 12; index++)
            a.insert(index, index + 60);
        HashTable<int, int> b = a;
        REQUIRE(a.contains(4));
        REQUIRE(b.contains(4));
        REQUIRE((a == b));
        a = a;
        REQUIRE((a == b));
    }

    SECTION("heavy move assignment") {
        HashTable<int, int> n;
        const int L1 = 100, R1 = 2048;
        for(int index = L1; index < R1; index++) {
            n.insert(index, index * index);
            n.insert(index + 8000, index);
            n.insert(-index, index - 400);
        }

        HashTable<int, int> m = n;
        auto k = std::move(n);

        REQUIRE((m == k));

        for(int index = L1; index < R1; index++) {
            REQUIRE((k.at(index) == m.at(index)));
            REQUIRE((k.at(index + 8000) == m.at(index + 8000)));
            REQUIRE((k.at(-index) == m.at(-index)));
        }

        auto *mv = new HashTable<int, int>(m);
        mv = std::move(mv);
        REQUIRE((m == *mv));
        REQUIRE((k == *mv));

        delete mv;
    }
}