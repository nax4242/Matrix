#include "pch.h"
#include "MathVector.h"
#include <stdexcept>
#include "parameters.h"

#ifdef MATHVECTOR_TESTS

TEST(MathVectorTest, ArrayConstructor) {
    int arr[] = { 10, 20, 30 };
    MathVector<int> v(3, arr);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v.start_index(), 0u);
}

TEST(MathVectorTest, NullptrConstructorFillsWithDefault) {
    MathVector<int> v(4);
    EXPECT_EQ(v.size(), 4u);
    for (size_t i = 0; i < 4; ++i) EXPECT_EQ(v[i], 0);
}

TEST(MathVectorTest, InitializerListConstructor) {
    MathVector<double> v{ 1.5, 2.5, 3.5 };
    EXPECT_EQ(v.size(), 3u);
    EXPECT_DOUBLE_EQ(v[0], 1.5);
    EXPECT_DOUBLE_EQ(v[2], 3.5);
    EXPECT_EQ(v.start_index(), 0u);
}

TEST(MathVectorTest, CopyConstructor) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2(v1);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[1], 2);
}

TEST(MathVectorTest, CopyIsIndependent) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2(v1);
    v2[0] = 100;
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v2[0], 100);
}

TEST(MathVectorTest, EmptyVectorThrows) {
    int arr[] = { 1, 2, 3 };
    EXPECT_THROW(MathVector<int>(0, arr), std::logic_error);
    EXPECT_THROW(MathVector<int>(0, arr, 2), std::logic_error);
}

TEST(MathVectorTest, FullAndEmptyFlags) {
    MathVector<int> v{ 1, 2, 3 };
    EXPECT_TRUE(v.is_full());
    EXPECT_FALSE(v.is_empty());
}

TEST(MathVectorTest, IndexWrite) {
    MathVector<int> v{ 1, 2, 3 };
    v[1] = 20;
    EXPECT_EQ(v[1], 20);
}

TEST(MathVectorTest, IndexOutOfRangeThrows) {
    MathVector<int> v{ 1, 2, 3 };
    EXPECT_THROW(v[3], std::out_of_range);
    EXPECT_THROW(v[100], std::out_of_range);
}

TEST(MathVectorTest, ConstIndexAccess) {
    const MathVector<int> v{ 1, 2, 3 };
    EXPECT_EQ(v[2], 3);
    EXPECT_THROW(v[3], std::out_of_range);
}

TEST(MathVectorTest, StartIndexSizeIsStoredCount) {
    MathVector<int> v(3, nullptr, 2);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v.start_index(), 2u);
}

TEST(MathVectorTest, StartIndexShiftsIndices) {
    int arr[] = { 10, 20, 30 };
    MathVector<int> v(3, arr, 1);
    EXPECT_EQ(v[1], 10);
    EXPECT_EQ(v[2], 20);
    EXPECT_EQ(v[3], 30);
}

TEST(MathVectorTest, StartIndexReadBeforeStartIsZero) {
    int arr[] = { 10, 20, 30 };
    MathVector<int> v(3, arr, 2);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
}

TEST(MathVectorTest, StartIndexWriteBeforeStartIsIgnored) {
    int arr[] = { 10, 20, 30 };
    MathVector<int> v(3, arr, 2);
    v[0] = 99;
    v[1] = 99;
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v[2], 10);
    EXPECT_EQ(v[3], 20);
    EXPECT_EQ(v[4], 30);
    EXPECT_EQ(v.size(), 3u);
}

TEST(MathVectorTest, StartIndexWriteAfterStart) {
    MathVector<int> v(2, nullptr, 3);
    v[3] = 7;
    v[4] = 8;
    EXPECT_EQ(v[3], 7);
    EXPECT_EQ(v[4], 8);
}

TEST(MathVectorTest, StartIndexOutOfRangeThrows) {
    MathVector<int> v(3, nullptr, 2);
    EXPECT_NO_THROW(v[0]);
    EXPECT_NO_THROW(v[4]);
    EXPECT_THROW(v[5], std::out_of_range);
}

TEST(MathVectorTest, StartIndexConstAccess) {
    int arr[] = { 5, 6 };
    const MathVector<int> v(2, arr, 1);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 5);
    EXPECT_EQ(v[2], 6);
    EXPECT_THROW(v[3], std::out_of_range);
}

TEST(MathVectorTest, CopyConstructorKeepsStartIndex) {
    int arr[] = { 1, 2, 3 };
    MathVector<int> v1(3, arr, 2);
    MathVector<int> v2(v1);
    EXPECT_EQ(v2.start_index(), 2u);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 0);
    EXPECT_EQ(v2[2], 1);
    EXPECT_EQ(v2[4], 3);
}

TEST(MathVectorTest, AssignmentCopiesStartIndex) {
    int arr[] = { 1, 2, 3 };
    MathVector<int> src(3, arr, 4);
    MathVector<int> dst(2);
    dst = src;
    EXPECT_EQ(dst.start_index(), 4u);
    EXPECT_EQ(dst.size(), 3u);
    EXPECT_EQ(dst[4], 1);
    EXPECT_EQ(dst[6], 3);
    EXPECT_EQ(dst[0], 0);
}

TEST(MathVectorTest, ScalarMultiplication) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2 = v1 * 2.0;
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 4);
    EXPECT_EQ(v2[2], 6);
    EXPECT_EQ(v1[0], 1);
}

TEST(MathVectorTest, ScalarMultiplicationAssign) {
    MathVector<int> v1{ 1, 2, 3 };
    v1 *= 3.0;
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[1], 6);
    EXPECT_EQ(v1[2], 9);
}

TEST(MathVectorTest, ScalarMultiplicationWithStartIndex) {
    int arr[] = { 1, 2 };
    MathVector<int> v(2, arr, 2);
    MathVector<int> r = v * 5.0;
    EXPECT_EQ(r.start_index(), 2u);
    EXPECT_EQ(r[0], 0);
    EXPECT_EQ(r[2], 5);
    EXPECT_EQ(r[3], 10);
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

TEST(MathVectorTest, VectorAdditionWithStartIndex) {
    int a[] = { 1, 2 };
    int b[] = { 10, 20 };
    MathVector<int> v1(2, a, 3);
    MathVector<int> v2(2, b, 3);
    MathVector<int> r = v1 + v2;
    EXPECT_EQ(r.start_index(), 3u);
    EXPECT_EQ(r.size(), 2u);
    EXPECT_EQ(r[0], 0);
    EXPECT_EQ(r[3], 11);
    EXPECT_EQ(r[4], 22);
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

TEST(MathVectorTest, VectorSubtractionWithStartIndex) {
    int a[] = { 10, 20 };
    int b[] = { 1, 2 };
    MathVector<int> v1(2, a, 1);
    MathVector<int> v2(2, b, 1);
    MathVector<int> r = v1 - v2;
    EXPECT_EQ(r.start_index(), 1u);
    EXPECT_EQ(r[0], 0);
    EXPECT_EQ(r[1], 9);
    EXPECT_EQ(r[2], 18);
}

TEST(MathVectorTest, DotProduct) {
    MathVector<int> v1{ 1, 2, 3 };
    MathVector<int> v2{ 4, 5, 6 };
    double dot = v1 * v2;
    EXPECT_DOUBLE_EQ(dot, 32.0);
}

TEST(MathVectorTest, DotProductWithStartIndex) {
    int a[] = { 1, 2 };
    int b[] = { 3, 4 };
    MathVector<int> v1(2, a, 5);
    MathVector<int> v2(2, b, 5);
    EXPECT_DOUBLE_EQ(v1 * v2, 11.0);
}

TEST(MathVectorTest, SizeMismatchOnAddition) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 + v2, std::invalid_argument);
    EXPECT_THROW(v1 += v2, std::invalid_argument);
}

TEST(MathVectorTest, SizeMismatchOnSubtraction) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 - v2, std::invalid_argument);
    EXPECT_THROW(v1 -= v2, std::invalid_argument);
}

TEST(MathVectorTest, SizeMismatchOnDotProduct) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 * v2, std::invalid_argument);
}

TEST(MathVectorTest, StartIndexMismatchThrows) {
    MathVector<int> v1(3, nullptr, 0);
    MathVector<int> v2(3, nullptr, 1);
    EXPECT_THROW(v1 + v2, std::invalid_argument);
    EXPECT_THROW(v1 += v2, std::invalid_argument);
    EXPECT_THROW(v1 - v2, std::invalid_argument);
    EXPECT_THROW(v1 -= v2, std::invalid_argument);
    EXPECT_THROW(v1 * v2, std::invalid_argument);
}

TEST(MathVectorTest, FailedOperationDoesNotModifyVector) {
    MathVector<int> v1{ 1, 2 };
    MathVector<int> v2{ 1, 2, 3 };
    EXPECT_THROW(v1 += v2, std::invalid_argument);
    EXPECT_EQ(v1.size(), 2u);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
}

#endif