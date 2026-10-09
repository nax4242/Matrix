#include "pch.h"
#include "parameters.h"
#include "vector.h"
#include <random>

typedef Vector<int> IntVec;

static IntVec make_vec(size_t n) {
    IntVec v(nullptr, n);
    int val = 1;
    for (IntVec::iterator it = v.begin(); it != v.end(); ++it) *it = val++;
    return v;
}

static IntVec make_wrapped_vec() {
    IntVec v{ 1, 2, 3 };
    v.push_front(0);
    v.push_front(-1);
    for (int i = 4; i <= 10; ++i) v.push_back(i);
    return v;
}

TEST(IteratorCtor, DefaultIteratorsAreEqual) {
    IntVec::iterator a, b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    IntVec::const_iterator ca, cb;
    EXPECT_TRUE(ca == cb);
}

TEST(IteratorCtor, PointerCtor) {
    IntVec v = make_vec(5);

    IntVec::iterator first(&v, 0);
    EXPECT_TRUE(first == v.begin());
    EXPECT_EQ(*first, 1);

    IntVec::iterator last(&v, 4);
    EXPECT_EQ(*last, 5);

    IntVec::iterator end_it(&v, v.size());
    EXPECT_TRUE(end_it == v.end());
}

TEST(IteratorCtor, CopyCtor) {
    IntVec v = make_vec(5);
    IntVec::iterator a = v.begin() + 2;
    IntVec::iterator b(a);

    EXPECT_TRUE(a == b);
    EXPECT_EQ(*b, 3);
}

TEST(IteratorAssign, CopyAssignment) {
    IntVec v = make_vec(5);
    IntVec::iterator a = v.begin() + 2;
    IntVec::iterator c;
    c = a;

    EXPECT_TRUE(c == a);
    EXPECT_EQ(*c, 3);

    ++c;
    EXPECT_TRUE(c != a);
    EXPECT_EQ(*a, 3);
}

TEST(IteratorAssign, SelfAssignment) {
    IntVec v = make_vec(5);
    IntVec::iterator a = v.begin() + 2;
    IntVec::iterator& ref = a;
    a = ref;
    EXPECT_EQ(*a, 3);
}

TEST(IteratorAssign, ChainedAssignment) {
    IntVec v = make_vec(3);
    IntVec::iterator x, y, z;
    x = y = z = v.begin();
    EXPECT_TRUE(x == v.begin());
    EXPECT_TRUE(y == v.begin());
    EXPECT_TRUE(z == v.begin());
}

TEST(BeginEnd, EmptyVector) {
    IntVec v;
    EXPECT_TRUE(v.begin() == v.end());

    const IntVec cv;
    EXPECT_TRUE(cv.begin() == cv.end());

    int count = 0;
    for (IntVec::iterator it = v.begin(); it != v.end(); ++it) ++count;
    EXPECT_EQ(count, 0);
}

TEST(BeginEnd, DistanceEqualsSize) {
    IntVec v = make_vec(8);
    EXPECT_TRUE(v.begin() != v.end());
    EXPECT_TRUE(v.begin() + 8 == v.end());
    EXPECT_TRUE(v.end() - 8 == v.begin());
}

TEST(BeginEnd, IteratorsOfDifferentVectorsDiffer) {
    IntVec a = make_vec(3);
    IntVec b = make_vec(3);
    EXPECT_TRUE(a.begin() != b.begin());
    EXPECT_TRUE(a.end() != b.end());
}

TEST(BeginEnd, SingleElement) {
    IntVec v{ 42 };
    EXPECT_EQ(*v.begin(), 42);
    EXPECT_TRUE(v.begin() + 1 == v.end());
    EXPECT_TRUE(++v.begin() == v.end());
    EXPECT_TRUE(v.end() - 1 == v.begin());
}

TEST(Increment, Prefix) {
    IntVec v = make_vec(4);
    IntVec::iterator it = v.begin();

    IntVec::iterator& ref = ++it;
    EXPECT_EQ(&ref, &it);
    EXPECT_EQ(*it, 2);

    ++it; ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_TRUE(it == v.end());
}

TEST(Increment, Postfix) {
    IntVec v = make_vec(4);
    IntVec::iterator it = v.begin();

    IntVec::iterator old = it++;
    EXPECT_TRUE(old == v.begin());
    EXPECT_EQ(*old, 1);
    EXPECT_EQ(*it, 2);

    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it, 3);
}

TEST(Decrement, Prefix) {
    IntVec v = make_vec(4);
    IntVec::iterator it = v.end();

    IntVec::iterator& ref = --it;
    EXPECT_EQ(&ref, &it);
    EXPECT_EQ(*it, 4);

    --it; --it; --it;
    EXPECT_TRUE(it == v.begin());
    EXPECT_EQ(*it, 1);
}

TEST(Decrement, Postfix) {
    IntVec v = make_vec(4);
    IntVec::iterator it = v.begin() + 3;

    IntVec::iterator old = it--;
    EXPECT_EQ(*old, 4);
    EXPECT_EQ(*it, 3);

    EXPECT_EQ(*it--, 3);
    EXPECT_EQ(*it, 2);
}

TEST(IncDec, Roundtrip) {
    IntVec v = make_vec(6);
    IntVec::iterator start = v.begin() + 3;
    IntVec::iterator it = start;

    ++it; --it;
    EXPECT_TRUE(it == start);
    it++; it--;
    EXPECT_TRUE(it == start);
}

TEST(Arithmetic, PlusMinus) {
    IntVec v = make_vec(8);
    IntVec::iterator b = v.begin();
    IntVec::iterator e = v.end();

    EXPECT_EQ(*(b + 0), 1);
    EXPECT_EQ(*(b + 3), 4);
    EXPECT_EQ(*(b + 7), 8);
    EXPECT_TRUE(b + 8 == v.end());

    EXPECT_EQ(*(e - 1), 8);
    EXPECT_EQ(*(e - 8), 1);

    EXPECT_TRUE(b == v.begin());
    EXPECT_TRUE(e == v.end());
}

TEST(Arithmetic, PlusMinusAssign) {
    IntVec v = make_vec(8);
    IntVec::iterator it = v.begin();

    IntVec::iterator& r1 = (it += 5);
    EXPECT_EQ(&r1, &it);
    EXPECT_EQ(*it, 6);

    IntVec::iterator& r2 = (it -= 2);
    EXPECT_EQ(&r2, &it);
    EXPECT_EQ(*it, 4);

    it += 5;
    EXPECT_TRUE(it == v.end());
    it -= 8;
    EXPECT_TRUE(it == v.begin());
}

TEST(Arithmetic, NegativeOffsets) {
    IntVec v = make_vec(8);
    IntVec::iterator it = v.begin() + 4;

    EXPECT_EQ(*(it + (-2)), 3);
    EXPECT_EQ(*(it - (-2)), 7);

    it += -1;
    EXPECT_EQ(*it, 4);
    it -= -3;
    EXPECT_EQ(*it, 7);
}

TEST(Arithmetic, ConstIteratorArithmetic) {
    const IntVec v = make_vec(8);
    IntVec::const_iterator it = v.begin();

    EXPECT_EQ(*(it + 3), 4);
    it += 7;
    EXPECT_EQ(*it, 8);
    --it; it -= 2;
    EXPECT_EQ(*it, 5);
    EXPECT_TRUE(it + 4 == v.end());
}

TEST(Comparison, EqualityAndInequality) {
    IntVec v = make_vec(5);

    EXPECT_TRUE(v.begin() == v.begin());
    EXPECT_FALSE(v.begin() != v.begin());
    EXPECT_TRUE(v.begin() != v.end());
    EXPECT_FALSE(v.begin() == v.end());

    IntVec::iterator it = v.begin();
    ++it;
    EXPECT_TRUE(it == v.begin() + 1);
    EXPECT_TRUE(it != v.begin());
}

TEST(Dereference, WriteThroughIterator) {
    IntVec v = make_vec(5);

    *v.begin() = 100;
    EXPECT_EQ(v[0], 100);

    IntVec::iterator it = v.begin() + 2;
    *it = 300;
    EXPECT_EQ(v[2], 300);

    *it += 1;
    EXPECT_EQ(v[2], 301);

    int& ref = *(v.end() - 1);
    ref = -5;
    EXPECT_EQ(v[4], -5);
}

TEST(Dereference, ConstOverloadOnConstIteratorObject) {
    IntVec v = make_vec(3);
    const IntVec::iterator cit = v.begin();

    EXPECT_EQ(*cit, 1);
    const int& r = *cit;
    EXPECT_EQ(r, 1);
}

TEST(Dereference, ConstIteratorReadsConstVector) {
    const IntVec v = make_vec(5);

    int sum = 0;
    for (IntVec::const_iterator it = v.begin(); it != v.end(); ++it) sum += *it;
    EXPECT_EQ(sum, 15);

    EXPECT_EQ(*v.begin(), 1);
    EXPECT_EQ(*(v.end() - 1), 5);
}

TEST(CBeginCEnd, OnNonConstVector) {
    IntVec v = make_vec(5);

    IntVec::const_iterator b = v.cbegin();
    IntVec::const_iterator e = v.cend();

    EXPECT_TRUE(b != e);
    EXPECT_EQ(*b, 1);
    EXPECT_EQ(*(e - 1), 5);
    EXPECT_TRUE(b + 5 == e);
    EXPECT_TRUE(e - 5 == b);

    int sum = 0;
    for (IntVec::const_iterator it = v.cbegin(); it != v.cend(); ++it) sum += *it;
    EXPECT_EQ(sum, 15);
}

TEST(CBeginCEnd, OnConstVector) {
    const IntVec v = make_vec(4);

    EXPECT_TRUE(v.cbegin() == v.begin());
    EXPECT_TRUE(v.cend() == v.end());
    EXPECT_EQ(*v.cbegin(), 1);
    EXPECT_EQ(*(v.cend() - 1), 4);
}

TEST(CBeginCEnd, EmptyVector) {
    IntVec v;
    EXPECT_TRUE(v.cbegin() == v.cend());

    const IntVec cv;
    EXPECT_TRUE(cv.cbegin() == cv.cend());
}

TEST(CBeginCEnd, SingleElement) {
    IntVec v{ 7 };
    EXPECT_TRUE(v.cbegin() + 1 == v.cend());
    EXPECT_EQ(*v.cbegin(), 7);
}

TEST(CBeginCEnd, WrappedBuffer) {
    IntVec v = make_wrapped_vec();

    int expected = -1;
    for (IntVec::const_iterator it = v.cbegin(); it != v.cend(); ++it)
        EXPECT_EQ(*it, expected++);
    EXPECT_EQ(expected, 11);

    IntVec::const_iterator it = v.cend();
    int back = 10;
    while (it != v.cbegin()) {
        --it;
        EXPECT_EQ(*it, back--);
    }
    EXPECT_EQ(back, -2);
}

TEST(CBeginCEnd, AllOperationsOnConstIterator) {
    IntVec v = make_vec(6);
    IntVec::const_iterator it = v.cbegin();

    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(*++it, 3);
    EXPECT_EQ(*it--, 3);
    EXPECT_EQ(*--it, 1);
    it += 4;  EXPECT_EQ(*it, 5);
    it -= 2;  EXPECT_EQ(*it, 3);
    EXPECT_EQ(*(it + 3), 6);
    EXPECT_EQ(*(it - 2), 1);
}

TEST(CBeginCEnd, SeesChangesMadeThroughIterator) {
    IntVec v = make_vec(3);
    IntVec::const_iterator c = v.cbegin();
    *v.begin() = 99;
    EXPECT_EQ(*c, 99);
}

TEST(Scenario, TaskMain) {
    IntVec my_vec(nullptr, 8);
    int val = 1;

    for (IntVec::iterator it = my_vec.begin(); it != my_vec.end(); ++it) *it = val++;

    std::string out;
    for (IntVec::const_iterator it = my_vec.cbegin(); it != my_vec.cend(); ++it)
        out += std::to_string(*it) + " ";

    EXPECT_EQ(out, "1 2 3 4 5 6 7 8 ");
    EXPECT_EQ(val, 9);
}

TEST(Scenario, WrappedRingBuffer) {
    IntVec v = make_wrapped_vec();

    int expected = -1;
    int n = 0;
    for (IntVec::iterator it = v.begin(); it != v.end(); ++it, ++n)
        EXPECT_EQ(*it, expected++);

    EXPECT_EQ(n, 12);
    EXPECT_EQ(static_cast<size_t>(n), v.size());

    IntVec::iterator it = v.end();
    int back = 10;
    while (it != v.begin()) {
        --it;
        EXPECT_EQ(*it, back--);
    }
    EXPECT_EQ(back, -2);
}

TEST(Scenario, FullVector) {
    IntVec v = make_vec(15);
    ASSERT_EQ(v.size(), v.capacity());

    int n = 0, sum = 0;
    for (IntVec::iterator it = v.begin(); it != v.end(); ++it) {
        sum += *it;
        if (++n > 100) break;
    }
    EXPECT_EQ(n, 15);
    EXPECT_EQ(sum, 120);

    n = 0;
    for (IntVec::const_iterator it = v.cbegin(); it != v.cend(); ++it)
        if (++n > 100) break;
    EXPECT_EQ(n, 15);
}

TEST(Scenario, LargeVector) {
    IntVec v = make_vec(1000);
    long long sum = 0;
    for (IntVec::iterator it = v.begin(); it != v.end(); ++it) sum += *it;
    EXPECT_EQ(sum, 500500LL);
    EXPECT_EQ(*(v.begin() + 999), 1000);
}

TEST(Scenario, RangeBasedFor) {
    IntVec v = make_vec(5);
    for (int& x : v) x *= 10;
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[4], 50);

    int sum = 0;
    const IntVec& cv = v;
    for (int x : cv) sum += x;
    EXPECT_EQ(sum, 150);
}

TEST(Scenario, StepByTwo) {
    IntVec v = make_vec(6);
    for (IntVec::iterator it = v.begin(); it != v.end(); it += 2) *it = 0;

    EXPECT_EQ(v[0], 0); EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 0); EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 0); EXPECT_EQ(v[5], 6);
}

TEST(Scenario, OtherElementTypes) {
    Vector<std::string> s(nullptr, 3);
    s[0] = "a"; s[1] = "b"; s[2] = "c";
    std::string joined;
    for (Vector<std::string>::iterator it = s.begin(); it != s.end(); ++it) joined += *it;
    EXPECT_EQ(joined, "abc");

    Vector<double> d{ 1.5, 2.5 };
    double sum = 0;
    for (Vector<double>::const_iterator it = d.cbegin(); it != d.cend(); ++it) sum += *it;
    EXPECT_DOUBLE_EQ(sum, 4.0);
}