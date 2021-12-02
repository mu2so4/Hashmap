#include <catch2/catch_test_macros.hpp>
#include "../MyHashMap.h"

TEST_CASE("swapping", "[swap]") {
    HashTable<int, int> a, b;

    const int L1 = -1024, R1 = 2048, L2 = 4000, R2 = 10000;
    for(int index = L1; index < R1; index++) {
        a.insert(index, index * index);
    }
    for(int index = L2; index < R2; index++) {
        b.insert(index, index - 500);
    }

    a.swap(b);

    REQUIRE(a.size() == R2 - L2);
    REQUIRE(b.size() == R1 - L1);

    for(int index = L1; index < R1; index++) {
        REQUIRE(!a.contains(index));
        REQUIRE(b.at(index) == index * index);
    }

    for(int index = L2; index < R2; index++) {
        REQUIRE(!b.contains(index));
        REQUIRE(a.at(index) == index - 500);
    }
}

TEST_CASE("equals test", "[equals]") {
    SECTION("simple test") {
        HashTable<int, int> n, m;
        n.insert(12, 100);
        m.insert(12, 100);
        REQUIRE(((n == m)));

        n.insert(12 + 1023, 1000);
        m.insert(12 + 1023, 999);
        REQUIRE((!(n == m)));
    }

    SECTION("heavy test") {
        HashTable<int, int> a, b, c;

        const int L1 = 100, R1 = 2048;
        for (int index = L1; index < R1; index++) {
            a.insert(index, index * index);
            a.insert(index + 8000, index);
            a.insert(-index, index - 400);

            b.insert(-index, index - 400);
            b.insert(index + 8000, index);
            b.insert(index, index * index);

            c.insert(index, index * index);
            c.insert(-index, index - 400);
            c.insert(index + 8000, index);
        }

        REQUIRE((a == a));
        REQUIRE((b == b));
        REQUIRE((c == c));

        REQUIRE((a == b));
        REQUIRE((b == a));

        REQUIRE((b == c));
        REQUIRE((a == c));

        a.erase(2000);
        REQUIRE((!(a == b)));
        a.insert(2000, 12);
        REQUIRE((!(a == b)));
        c.erase(1999);
        c.insert(2001, 1235);
        REQUIRE((!(c == b)));
    }
}

TEST_CASE("not equals test", "[not equals]") {
    SECTION("simple test") {
        HashTable<int, int> n, m;
        n.insert(12, 100);
        m.insert(12, 100);
        REQUIRE((!(n != m)));

        n.insert(12 + 1023, 1000);
        m.insert(12 + 1023, 999);
        REQUIRE(((n != m)));
    }

    SECTION("heavy test") {
        HashTable<int, int> a, b, c;

        const int L1 = 100, R1 = 2048;
        for (int index = L1; index < R1; index++) {
            a.insert(index, index * index);
            a.insert(index + 8000, index);
            a.insert(-index, index - 400);

            b.insert(-index, index - 400);
            b.insert(index + 8000, index);
            b.insert(index, index * index);

            c.insert(index, index * index);
            c.insert(-index, index - 400);
            c.insert(index + 8000, index);
        }

        REQUIRE(!(a != a));
        REQUIRE(!(b != b));
        REQUIRE(!(c != c));

        REQUIRE(!(a != b));
        REQUIRE(!(b != a));

        REQUIRE(!(b != c));
        REQUIRE(!(a != c));

        a.erase(2000);
        REQUIRE(((a != b)));
        a.insert(2000, 12);
        REQUIRE(((a != b)));
        c.erase(1999);
        c.insert(2001, 1235);
        REQUIRE(((c != b)));
    }
}

TEST_CASE("clearing", "[clearing]") {
    SECTION("simple test") {
        HashTable<int, int> n;
        n.insert(12, 100);
        n.insert(120, 1000);
        n.clear();

        REQUIRE(n.empty());
        for(int index = 0; index < 2000; index++) {
            REQUIRE(!n.contains(index));
        }
    }

    SECTION("heavy test") {
        HashTable<int, int> a;

        const int L1 = 100, R1 = 2048;
        for(int index = L1; index < R1; index++) {
            a.insert(index, index * index);
            a.insert(index + 8000, index);
            a.insert(-index, index - 400);
        }

        a.clear();
        REQUIRE(a.empty());

        for(int index = L1; index < R1; index++) {
            REQUIRE(!a.contains(index));
            REQUIRE(!a.contains(index + 8000));
            REQUIRE(!a.contains(-index));
        }

        for(int index = L1; index < R1; index++) {
            REQUIRE(a.insert(index, index * index));
            REQUIRE(a.insert(index + 8000, index));
            REQUIRE(a.insert(-index, index - 400));
        }
    }
}