#include "pch.h"
#include "MathVector.h"
#include <stdexcept>
#include "parameters.h"

#ifdef MATHVECTOR_TESTS

TEST(MathVectorTest, ArrayConstructor) {
    int arr[] = { 10, 20, 30 };
    MathVector<int> v(3, arr);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v.size(), v.capacity());
}

TEST(MathVectorTest, InitializerListConstructor) {
    MathVector<double> v{ 1.5, 2.5, 3.5 };
    EXPECT_EQ(v.size(), 3);
    EXPECT_DOUBLE_EQ(v[0], 1.5);
    EXPECT_DOUBLE_EQ(v[2], 3.5);
    EXPECT_EQ(v.size(), v.capacity());
}

TEST(MathVectorTest, CopyConstructor) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[1], 2);
}

TEST(MathVectorTest, EmptyVectorThrows) {
    int arr[] = { 1, 2, 3 };
    EXPECT_THROW(MathVector<int>(0, arr), std::logic_error);
    EXPECT_THROW(MathVector<int>{}, std::logic_error);
}

TEST(MathVectorTest, ScalarMultiplication) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2 = v1 * 2.0;
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 4);
    EXPECT_EQ(v2[2], 6);
}

TEST(MathVectorTest, ScalarMultiplicationAssign) {
    MathVector<int> v1{ 1, 2, 3 };
    v1 *= 3.0;
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[1], 6);
    EXPECT_EQ(v1[2], 9);
}

TEST(MathVectorTest, VectorAddition) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2{ 4, 5, 6 };
    MathVector<int> v3 = v1 + v2;
    EXPECT_EQ(v3[0], 5);
    EXPECT_EQ(v3[1], 7);
    EXPECT_EQ(v3[2], 9);
}

TEST(MathVectorTest, VectorAdditionAssign) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2{ 4, 5, 6 };
    v1 += v2;
    EXPECT_EQ(v1[0], 5);
    EXPECT_EQ(v1[2], 9);
}

TEST(MathVectorTest, VectorSubtraction) {
    MathVector<int> v1{ 4, 5, 6 };
    MathVector<int> v2{ 1, 2, 3 };
    MathVector<int> v3 = v1 - v2;
    EXPECT_EQ(v3[0], 3);
    EXPECT_EQ(v3[1], 3);
    EXPECT_EQ(v3[2], 3);
}

TEST(MathVectorTest, VectorSubtractionAssign) {
    MathVector<int> v1{ 4, 5, 6 };
    MathVector<int> v2{ 1, 2, 3 };
    v1 -= v2;
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[2], 3);
}

TEST(MathVectorTest, DotProduct) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2{ 4, 5, 6 };
    double dot = v1 * v2;
    EXPECT_DOUBLE_EQ(dot, 32.0);
}

TEST(MathVectorTest, SizeMismatchOnAddition) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 + v2, std::logic_error);
    EXPECT_THROW(v1 += v2, std::logic_error);
}

TEST(MathVectorTest, SizeMismatchOnSubtraction) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 - v2, std::logic_error);
    EXPECT_THROW(v1 -= v2, std::logic_error);
}

TEST(MathVectorTest, SizeMismatchOnDotProduct) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 * v2, std::logic_error);
}

TEST(MathVectorTest, CannotModifySize) {
    MathVector<int> v{ 1, 2, 3 };
    EXPECT_EQ(v.size(), 3);
}

#endif