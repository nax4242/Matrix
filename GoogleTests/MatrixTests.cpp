#include "pch.h"
#include "parameters.h"
#include "Matrix.h"
#include <stdexcept>
#include <sstream>

#ifdef MATRIX_TESTS

TEST(MatrixTest, DefaultConstructorIsOneByOne) {
    Matrix<int> m;
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 1);
    EXPECT_EQ(m[0][0], 0);
}

TEST(MatrixTest, DefaultConstructorEmptyBracesIsOneByOne) {
    Matrix<int> m{};
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 1);
    EXPECT_EQ(m[0][0], 0);
}

TEST(MatrixTest, DefaultConstructedIsWritable) {
    Matrix<int> m;
    m[0][0] = 42;
    EXPECT_EQ(m[0][0], 42);
}

TEST(MatrixTest, DefaultConstructedStartIndexIsZero) {
    Matrix<int> m;
    EXPECT_EQ(m[0].start_index(), 0u);
}

TEST(MatrixTest, DefaultConstructedCanBeAssignedOver) {
    Matrix<int> m;
    Matrix<int> src{ { 1, 2, 3 },{ 4, 5, 6 } };
    m = src;
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 3);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixTest, DefaultConstructedCanBeMovedOver) {
    Matrix<int> m;
    m = Matrix<int>{ { 1, 2 },{ 3, 4 } };
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTest, DefaultConstructedArithmetic) {
    Matrix<int> a, b;
    a[0][0] = 2;
    b[0][0] = 3;
    Matrix<int> sum = a + b;
    EXPECT_EQ(sum[0][0], 5);
    Matrix<int> prod = a * b;
    EXPECT_EQ(prod[0][0], 6);
}

TEST(MatrixTest, DefaultConstructedSizeMismatchThrows) {
    Matrix<int> a;
    Matrix<int> b(2, 2);
    EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(MatrixTest, DefaultConstructedTranspose) {
    Matrix<int> m;
    m[0][0] = 7;
    Matrix<int> t = m.transpose();
    EXPECT_EQ(t.rows(), 1);
    EXPECT_EQ(t.cols(), 1);
    EXPECT_EQ(t[0][0], 7);
}

TEST(MatrixTest, DefaultConstructedInContainer) {
    std::vector<Matrix<int>> v(3);
    ASSERT_EQ(v.size(), 3u);
    for (const auto& m : v) {
        EXPECT_EQ(m.rows(), 1);
        EXPECT_EQ(m[0][0], 0);
    }
    v[1][0][0] = 5;
    EXPECT_EQ(v[0][0][0], 0);
    EXPECT_EQ(v[1][0][0], 5);
}

TEST(MatrixTest, DefaultConstructedOutput) {
    Matrix<int> m;
    std::ostringstream os;
    os << m;
    EXPECT_EQ(os.str(), "[ 0 ]");
}

TEST(MatrixTest, DefaultConstructedInput) {
    Matrix<int> m;
    std::istringstream is("9");
    is >> m;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(m[0][0], 9);
}

TEST(MatrixTest, SizeConstructor) {
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.rows(), 3);
    EXPECT_EQ(m.cols(), 4);
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
    EXPECT_THROW((Matrix<int>(std::initializer_list<std::initializer_list<int>>{})), std::logic_error);
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

TEST(MatrixTest, OutputOperator) {
    Matrix<int> m{ {1, 2}, {3, 4} };
    std::ostringstream os;
    os << m;
    EXPECT_EQ(os.str(), "[ 1 2 ]\n[ 3 4 ]");
}

TEST(MatrixTest, CopyConstructorIsIndependent) {
    Matrix<int> m1{ { 1, 2 },{ 3, 4 } };
    Matrix<int> m2(m1);
    m2[0][0] = 100;
    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m2[0][0], 100);
}

TEST(MatrixTest, CopyAssignment) {
    Matrix<int> src{ { 1, 2, 3 },{ 4, 5, 6 } };
    Matrix<int> dst(1, 1);
    dst = src;
    EXPECT_EQ(dst.rows(), 2);
    EXPECT_EQ(dst.cols(), 3);
    EXPECT_EQ(dst[1][2], 6);
    dst[0][0] = 100;
    EXPECT_EQ(src[0][0], 1);
}

TEST(MatrixTest, CopyAssignmentSelfAssignment) {
    Matrix<int> m{ { 1, 2 },{ 3, 4 } };
    Matrix<int>& ref = m;
    m = ref;
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTest, MoveConstructor) {
    Matrix<int> src{ { 1, 2 },{ 3, 4 } };
    Matrix<int> dst(std::move(src));
    EXPECT_EQ(dst.rows(), 2);
    EXPECT_EQ(dst.cols(), 2);
    EXPECT_EQ(dst[0][1], 2);
    EXPECT_EQ(dst[1][0], 3);
}

TEST(MatrixTest, MoveAssignment) {
    Matrix<int> src{ { 1, 2, 3 },{ 4, 5, 6 } };
    Matrix<int> dst(1, 1);
    dst = std::move(src);
    EXPECT_EQ(dst.rows(), 2);
    EXPECT_EQ(dst.cols(), 3);
    EXPECT_EQ(dst[1][1], 5);
}

TEST(MatrixTest, MovedToMatrixIsUsable) {
    Matrix<int> src{ { 1, 2 },{ 3, 4 } };
    Matrix<int> dst(std::move(src));
    Matrix<int> r = dst + Matrix<int>{ {1, 1}, { 1, 1 } };
    EXPECT_EQ(r[0][0], 2);
    EXPECT_EQ(r[1][1], 5);
}

TEST(MatrixTest, OutputOperatorRectangular) {
    Matrix<int> m{ { 1, 2, 3 },{ 4, 5, 6 } };
    std::ostringstream os;
    os << m;
    EXPECT_EQ(os.str(), "[ 1 2 3 ]\n[ 4 5 6 ]");
}

TEST(MatrixTest, InputOperator) {
    Matrix<int> m(2, 3);
    std::istringstream is("1 2 3\n4 5 6");
    is >> m;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixTest, InputOperatorNotEnoughDataSetsFail) {
    Matrix<int> m(2, 2);
    std::istringstream is("1 2 3");
    is >> m;
    EXPECT_TRUE(is.fail());
}

TEST(MatrixTest, InputOutputRoundTrip) {
    Matrix<int> a{ { 1, 2 },{ 3, 4 } };
    std::ostringstream os;
    os << a;

    std::string text = os.str();
    for (char& c : text) if (c == '[' || c == ']') c = ' ';

    Matrix<int> b(2, 2);
    std::istringstream is(text);
    is >> b;
    EXPECT_FALSE(is.fail());
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            EXPECT_EQ(a[i][j], b[i][j]);
}

TEST(MatrixTest, InputOperatorDouble) {
    Matrix<double> m(1, 2);
    std::istringstream is("1.5 2.5");
    is >> m;
    EXPECT_DOUBLE_EQ(m[0][0], 1.5);
    EXPECT_DOUBLE_EQ(m[0][1], 2.5);
}

#endif