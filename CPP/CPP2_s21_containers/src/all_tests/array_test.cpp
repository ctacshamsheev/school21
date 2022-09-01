#include <gtest/gtest.h>

#include <array>

#include "../s21_array.h"

TEST(Array_tests, constructor_initializer_list) {
  std::initializer_list<int> values{1, 2, 3, 4, 5};
  s21::Array<int, 5> A(values);
  std::array<int, 5> B = {1, 2, 3, 4, 5};
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Array_tests, constructor_copy) {
  std::initializer_list<int> values{1, 2, 3, 4, 5};
  s21::Array<int, 5> C(values);
  std::array<int, 5> D = {1, 2, 3, 4, 5};
  s21::Array<int, 5> A(C);
  std::array<int, 5> B(D);
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Array_tests, constructor_move) {
  std::initializer_list<int> values{1, 2, 3, 4, 5};
  s21::Array<int, 5> C(values);
  std::array<int, 5> D = {1, 2, 3, 4, 5};
  s21::Array<int, 5> A(std::move(C));
  std::array<int, 5> B(std::move(D));
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Array_tests, operator_equal) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B;
  B = {1, 2, 3, 4, 5};
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // s21::Array<int, 5> C;
  // ASSERT_ANY_THROW(C = {1, 2, 3, 4, 5, 6});
}

TEST(Array_tests, operator_equal_lValue) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  s21::Array<int, 5> B;
  B = A;
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // s21::Array<int, 10> C = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  // s21::Array<int, 10> D;
  // ASSERT_ANY_THROW((D = C));
}

TEST(Array_tests, at) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  EXPECT_EQ(A.at(3), B.at(3));
  ASSERT_ANY_THROW(A.at(10));
}

TEST(Array_tests, swap) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  s21::Array<int, 5> B{10, 11, 12, 13, 14};
  std::array<int, 5> C{1, 2, 3, 4, 5};
  std::array<int, 5> D{10, 11, 12, 13, 14};
  A.swap(B);
  C.swap(D);
  EXPECT_EQ(A.size(), C.size());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(A[i], C[i]);
  }
  // s21::Array<int, 7> E{1, 2, 3, 4, 5, 6, 7};
  // s21::Array<int, 5> F{10, 11, 12, 13, 14};
  // ASSERT_ANY_THROW(F.swap(E));
}

TEST(Array_tests, fill) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  A.fill(10);
  B.fill(10);
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Array_tests, front) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  EXPECT_EQ(A.front(), B.front());
}

TEST(Array_tests, back) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  EXPECT_EQ(A.back(), B.back());
}

TEST(Array_tests, data) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  EXPECT_EQ(*(A.data()), *(B.data()));
}

TEST(Array_tests, empty) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  s21::Array<int, 0> C;
  s21::Array<int, 0> D;
  EXPECT_EQ(A.empty(), B.empty());
  EXPECT_EQ(C.empty(), D.empty());
}

TEST(Array_tests, begin) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  EXPECT_EQ(*(A.begin()), *(B.begin()));
}

TEST(Array_tests, end) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  auto it_21 = A.end();
  auto it_ = B.end();
  EXPECT_EQ(*(--it_21), *(--it_));
}

TEST(Array_tests, max_size) {
  s21::Array<int, 5> A{1, 2, 3, 4, 5};
  std::array<int, 5> B{1, 2, 3, 4, 5};
  EXPECT_EQ(A.max_size(), B.max_size());
}
