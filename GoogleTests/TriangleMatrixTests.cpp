#include "pch.h"
#include "parameters.h"
#include "TriangleMatrix.h"
#include <stdexcept>

static TriangleMatrix<int> make5() {
    return TriangleMatrix<int>({
        { 3, 4, 3, 0, 0 },
        { 0, 4, 3, 5, 1 },
        { 0, 0, 3, 5, 1 },
        { 0, 0, 0, 5, 1 },
        { 0, 0, 0, 0, 1 }
        });
}

TEST(TriangleMatrix, SizeConstructorIsZeroFilled) {
    TriangleMatrix<int> A(4);
    EXPECT_EQ(A.size(), 4u);
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            EXPECT_EQ(A[i][j], 0);
}

TEST(TriangleMatrix, DefaultConstructorIsOneByOne) {
    TriangleMatrix<int> A;
    EXPECT_EQ(A.size(), 1u);
    EXPECT_EQ(A[0].size(), 1u);
    EXPECT_EQ(A[0][0], 0);
}

TEST(TriangleMatrix, DefaultConstructedInContainer) {
    std::vector<TriangleMatrix<int>> v(2);
    EXPECT_EQ(v[0].size(), 1u);
    EXPECT_EQ(v[1][0][0], 0);
}
TEST(TriangleMatrix, ZeroSizeThrows) {
    EXPECT_ANY_THROW(TriangleMatrix<int> A(0));
}

TEST(TriangleMatrix, StoresOnlyUpperPart) {
    auto A = make5();
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(A[i].size(), 5 - i);
    }
}

TEST(TriangleMatrix, InitializerListReadsAllElements) {
    auto A = make5();
    EXPECT_EQ(A[0][2], 3);
    EXPECT_EQ(A[1][3], 5);
    EXPECT_EQ(A[4][4], 1);
    EXPECT_EQ(A[3][0], 0);
}

TEST(TriangleMatrix, NonSquareInitializerThrows) {
    EXPECT_THROW((TriangleMatrix<int>({ {1, 2, 3}, {0, 1, 2} })), std::invalid_argument);
}

TEST(TriangleMatrix, NonZeroBelowDiagonalInInitializerThrows) {
    EXPECT_THROW((TriangleMatrix<int>({ {1, 2}, {3, 4} })), std::invalid_argument);
}

TEST(TriangleMatrix, WriteAboveAndOnDiagonal) {
    auto A = make5();
    A[2][3] = -6;
    A[0][0] = 10;
    EXPECT_EQ(A[2][3], -6);
    EXPECT_EQ(A[0][0], 10);
}

TEST(TriangleMatrix, WriteBelowDiagonalIsIgnored) {
    auto A = make5();
    A[4][1] = 5;
    EXPECT_EQ(A[4][1], 0);
    EXPECT_EQ(A[4][4], 1);
    EXPECT_EQ(A[4].size(), 1u);
}

TEST(TriangleMatrix, ConstAccessBelowDiagonalIsZero) {
    const auto A = make5();
    EXPECT_EQ(A[4][1], 0);
    EXPECT_EQ(A[1][1], 4);
}

TEST(TriangleMatrix, OutOfRangeThrows) {
    auto A = make5();
    EXPECT_THROW(A[5][0], std::out_of_range);
    EXPECT_THROW(A[0][5], std::out_of_range);
}

TEST(TriangleMatrix, CopyIsIndependent) {
    auto A = make5();
    TriangleMatrix<int> B(A);
    B[0][0] = 100;
    EXPECT_EQ(A[0][0], 3);
    EXPECT_EQ(B[0][0], 100);
}

TEST(TriangleMatrix, AddSubtract) {
    auto A = make5();
    TriangleMatrix<int> S = A + A;
    EXPECT_EQ(S[0][1], 8);
    EXPECT_EQ(S[4][1], 0);
    EXPECT_EQ(S[3].size(), 2u);
    TriangleMatrix<int> D = S - A;
    for (size_t i = 0; i < 5; ++i)
        for (size_t j = 0; j < 5; ++j)
            EXPECT_EQ(D[i][j], A[i][j]);
}

TEST(TriangleMatrix, SizeMismatchThrows) {
    TriangleMatrix<int> A(2), B(3);
    EXPECT_THROW(A + B, std::invalid_argument);
    EXPECT_THROW(A - B, std::invalid_argument);
}

TEST(TriangleMatrix, ScalarMultiply) {
    auto A = make5();
    auto B = A * 2.0;
    EXPECT_EQ(B[1][3], 10);
    EXPECT_EQ(B[3][0], 0);
}

TEST(TriangleMatrix, MatrixMultiply) {
    TriangleMatrix<int> A({ {1, 2}, {0, 3} });
    TriangleMatrix<int> B({ {4, 5}, {0, 6} });
    Matrix<int> C = A * B;
    EXPECT_EQ(C[0][0], 4);
    EXPECT_EQ(C[0][1], 17);
    EXPECT_EQ(C[1][0], 0);
    EXPECT_EQ(C[1][1], 18);
}

TEST(TriangleMatrix, Output) {
    TriangleMatrix<int> A({ {1, 2}, {0, 3} });
    std::ostringstream os;
    os << A;
    EXPECT_EQ(os.str(), "[ 1 2 ]\n[ 0 3 ]");
}

TEST(TriangleMatrix, DoubleType) {
    TriangleMatrix<double> A({ {1.5, 2.0}, {0.0, 3.0} });
    EXPECT_DOUBLE_EQ(A[0][0], 1.5);
    EXPECT_DOUBLE_EQ(A[1][0], 0.0);
}

TEST(MathVector, StartIndex) {
    MathVector<int> v(3, nullptr, 2);
    v[3] = 7;
    EXPECT_EQ(v[3], 7);
    EXPECT_EQ(v[0], 0);
    v[1] = 9;
    EXPECT_EQ(v[1], 0);
    EXPECT_THROW(v[5], std::out_of_range);
}

TEST(TriangleMatrix, CopyConstructorKeepsTriangleShape) {
    auto A = make5();
    TriangleMatrix<int> B(A);
    for (size_t i = 0; i < 5; ++i)
        EXPECT_EQ(B[i].size(), 5 - i);
    EXPECT_EQ(B[1][3], 5);
}

TEST(TriangleMatrix, CopyAssignment) {
    auto A = make5();
    TriangleMatrix<int> C(2);
    C = A;
    EXPECT_EQ(C.size(), 5u);
    for (size_t i = 0; i < 5; ++i)
        EXPECT_EQ(C[i].size(), 5 - i);
    C[0][0] = 100;
    EXPECT_EQ(A[0][0], 3);
    EXPECT_EQ(C[4][1], 0);
}

TEST(TriangleMatrix, CopyAssignmentSelfAssignment) {
    auto A = make5();
    TriangleMatrix<int>& ref = A;
    A = ref;
    EXPECT_EQ(A.size(), 5u);
    EXPECT_EQ(A[2][3], 5);
}

TEST(TriangleMatrix, MoveConstructor) {
    auto A = make5();
    TriangleMatrix<int> B(std::move(A));
    EXPECT_EQ(B.size(), 5u);
    for (size_t i = 0; i < 5; ++i)
        EXPECT_EQ(B[i].size(), 5 - i);
    EXPECT_EQ(B[0][2], 3);
    EXPECT_EQ(B[4][4], 1);
    EXPECT_EQ(B[3][0], 0);
}

TEST(TriangleMatrix, MoveAssignment) {
    auto A = make5();
    TriangleMatrix<int> C(2);
    C = std::move(A);
    EXPECT_EQ(C.size(), 5u);
    EXPECT_EQ(C[1][3], 5);
    EXPECT_EQ(C[4].size(), 1u);
}

TEST(TriangleMatrix, MovedToMatrixIsUsable) {
    auto A = make5();
    TriangleMatrix<int> B(std::move(A));
    TriangleMatrix<int> S = B + B;
    EXPECT_EQ(S[0][1], 8);
    EXPECT_EQ(S[4][1], 0);
}

TEST(TriangleMatrix, OutputPrintsFullSquare) {
    TriangleMatrix<int> A({ { 1, 2, 3 },{ 0, 4, 5 },{ 0, 0, 6 } });
    std::ostringstream os;
    os << A;
    EXPECT_EQ(os.str(), "[ 1 2 3 ]\n[ 0 4 5 ]\n[ 0 0 6 ]");
}

TEST(TriangleMatrix, InputReadsFullSquare) {
    TriangleMatrix<int> A(3);
    std::istringstream is("1 2 3  0 4 5  0 0 6");
    is >> A;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(A[0][0], 1);
    EXPECT_EQ(A[0][2], 3);
    EXPECT_EQ(A[1][1], 4);
    EXPECT_EQ(A[1][2], 5);
    EXPECT_EQ(A[2][2], 6);
    EXPECT_EQ(A[1][0], 0);
    EXPECT_EQ(A[2][0], 0);
    EXPECT_EQ(A[2][1], 0);
}

TEST(TriangleMatrix, InputNonZeroBelowDiagonalThrows) {
    TriangleMatrix<int> A(3);
    std::istringstream is("1 2 3  7 4 5  0 0 6");
    EXPECT_THROW(is >> A, std::invalid_argument);
}

TEST(TriangleMatrix, InputThrowKeepsOriginalMatrix) {
    auto A = make5();
    std::istringstream is("1 1 1 1 1  1 1 1 1 1  1 1 1 1 1  1 1 1 1 1  1 1 1 1 1");
    EXPECT_THROW(is >> A, std::invalid_argument);
    EXPECT_EQ(A[0][0], 3);
    EXPECT_EQ(A[1][3], 5);
    EXPECT_EQ(A[4][4], 1);
}

TEST(TriangleMatrix, InputDoesNotConsumeExtraValues) {
    TriangleMatrix<int> A(2);
    std::istringstream is("1 2 0 3 99");
    is >> A;
    EXPECT_FALSE(is.fail());
    int rest;
    is >> rest;
    EXPECT_EQ(rest, 99);
}

TEST(TriangleMatrix, InputNotEnoughDataSetsFail) {
    TriangleMatrix<int> A(3);
    std::istringstream is("1 2 3 0 4 5 0 0");   // 8 из 9
    is >> A;
    EXPECT_TRUE(is.fail());
}

TEST(TriangleMatrix, InputKeepsTriangleShape) {
    TriangleMatrix<int> A(3);
    std::istringstream is("1 2 3 0 4 5 0 0 6");
    is >> A;
    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(A[i].size(), 3 - i);
}

TEST(TriangleMatrix, InputThenOutput) {
    TriangleMatrix<int> A(2);
    std::istringstream is("1 2 0 3");
    is >> A;
    std::ostringstream os;
    os << A;
    EXPECT_EQ(os.str(), "[ 1 2 ]\n[ 0 3 ]");
}

TEST(TriangleMatrix, OutputInputRoundTrip) {
    auto A = make5();
    std::ostringstream os;
    os << A;

    std::string text = os.str();
    for (char& c : text) if (c == '[' || c == ']') c = ' ';

    TriangleMatrix<int> B(5);
    std::istringstream is(text);
    is >> B;
    EXPECT_FALSE(is.fail());
    for (size_t i = 0; i < 5; ++i)
        for (size_t j = 0; j < 5; ++j)
            EXPECT_EQ(A[i][j], B[i][j]);
}

