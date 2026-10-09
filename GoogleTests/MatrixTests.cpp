#include "pch.h"
#include "parameters.h"
#include "Matrix.h"
#include <stdexcept>

#ifdef MATRIX_TESTS

TEST(MatrixTest, SizeConstructor) {
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.rows(), 3);
    EXPECT_EQ(m.cols(), 4);
    EXPECT_EQ(m.size(), 3);
}

TEST(MatrixTest, InitializerListConstructor) {
    Matrix<int> m{ {1, 2, 3}, {4, 5, 6} };
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 3);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix<int> m1{ {1, 2}, {3, 4} };
    Matrix<int> m2(m1);
    EXPECT_EQ(m2.rows(), 2);
    EXPECT_EQ(m2.cols(), 2);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[1][1], 4);
}

TEST(MatrixTest, EmptyMatrixThrows) {
    EXPECT_THROW(Matrix<int>(0, 0), std::logic_error);
    EXPECT_THROW(Matrix<int>{}, std::logic_error);
}

TEST(MatrixTest, ZeroRowsThrows) {
    EXPECT_THROW(Matrix<int>(0, 5), std::logic_error);
}

TEST(MatrixTest, ZeroColsThrows) {
    EXPECT_THROW(Matrix<int>(5, 0), std::logic_error);
}

TEST(MatrixTest, InconsistentRowsThrows) {
    EXPECT_THROW((Matrix<int>{{1, 2}, { 3, 4, 5 }}), std::invalid_argument);
}

TEST(MatrixTest, ElementAccess) {
    Matrix<int> m{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[2][2], 9);

    m[1][1] = 10;
    EXPECT_EQ(m[1][1], 10);
}

TEST(MatrixTest, RowAccess) {
    Matrix<int> m{ {1, 2}, {3, 4} };
    auto row = m[0];
    EXPECT_EQ(row[0], 1);
    EXPECT_EQ(row[1], 2);
}

TEST(MatrixTest, RectangularMatrixAccess) {
    Matrix<int> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
}

TEST(MatrixTest, CannotModifySize) {
    Matrix<int> m{ {1, 2}, {3, 4} };
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);
}

TEST(MatrixTest, InheritedScalarMultiplication) {
    Matrix<int> m{ {1, 2}, {3, 4} };
    Matrix<int> result = m * 2.0;
    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[1][0], 6);
    EXPECT_EQ(result[1][1], 8);
}

TEST(MatrixTest, InheritedScalarMultiplicationAssign) {
    Matrix<int> m{ {1, 2}, {3, 4} };
    m *= 3.0;
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[1][1], 12);
}

TEST(MatrixTest, InheritedAddition) {
    Matrix<int> m1{ {1, 2}, {3, 4} };
    Matrix<int> m2{ {5, 6}, {7, 8} };
    Matrix<int> result = m1 + m2;
    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 8);
    EXPECT_EQ(result[1][0], 10);
    EXPECT_EQ(result[1][1], 12);
}

TEST(MatrixTest, InheritedAdditionAssign) {
    Matrix<int> m1{ {1, 2}, {3, 4} };
    Matrix<int> m2{ {5, 6}, {7, 8} };
    m1 += m2;
    EXPECT_EQ(m1[0][0], 6);
    EXPECT_EQ(m1[1][1], 12);
}

TEST(MatrixTest, InheritedSubtraction) {
    Matrix<int> m1{ {5, 6}, {7, 8} };
    Matrix<int> m2{ {1, 2}, {3, 4} };
    Matrix<int> result = m1 - m2;
    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[1][1], 4);
}

TEST(MatrixTest, InheritedSubtractionAssign) {
    Matrix<int> m1{ {5, 6}, {7, 8} };
    Matrix<int> m2{ {1, 2}, {3, 4} };
    m1 -= m2;
    EXPECT_EQ(m1[0][0], 4);
    EXPECT_EQ(m1[1][1], 4);
}

TEST(MatrixTest, SizeMismatchOnAddition) {
    Matrix<int> m1{ {1, 2}, {3, 4} };
    Matrix<int> m2{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(MatrixTest, SizeMismatchOnSubtraction) {
    Matrix<int> m1{ {1, 2}, {3, 4} };
    Matrix<int> m2{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    EXPECT_THROW(m1 - m2, std::invalid_argument);
}

#endif