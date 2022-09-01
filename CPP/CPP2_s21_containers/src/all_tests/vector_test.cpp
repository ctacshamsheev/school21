#include <vector>

#include "../s21_vector.h"

TEST(Vector_tests, constructor_param) {
  s21::Vector<int> A(5);
  std::vector<int> B(5);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
}

TEST(Vector_tests, constructor_initializer_list) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Vector_tests, constructor_copy) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  s21::Vector<int> B(A);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Vector_tests, constructor_move) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  s21::Vector<int> B(std::move(A));
  std::vector<int> C(values);
  std::vector<int> D(std::move(C));

  EXPECT_EQ(B.size(), D.size());
  EXPECT_EQ(B.capacity(), D.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(B[i], D[i]);
  }
}

TEST(Vector_tests, reserve) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  A.reserve(10);
  B.reserve(10);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::Vector<int> C;
  std::vector<int> D;
  C.reserve(10);
  D.reserve(10);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
}

TEST(Vector_tests, push_back) {
  std::vector<int> A;
  s21::Vector<int> B;
  A.push_back(1);
  A.push_back(2);
  A.push_back(3);
  B.push_back(1);
  B.push_back(2);
  B.push_back(3);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // ===
  std::vector<int> C(10);
  s21::Vector<int> D(10);
  C.push_back(1);
  C.push_back(2);
  C.push_back(3);
  D.push_back(1);
  D.push_back(2);
  D.push_back(3);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < D.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  // ===
  std::vector<int> E;
  s21::Vector<int> F;
  E.push_back(100);
  F.push_back(100);
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < F.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}

TEST(Vector_tests, resize) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  std::vector<int> A(values);
  s21::Vector<int> B(values);
  A.resize(2);
  B.resize(2);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  A.resize(10);
  B.resize(10);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  // ===
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  A.reserve(20);
  A.resize(15);
  B.reserve(20);
  B.resize(15);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Vector_tests, pop_back) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  std::vector<int> A(values);
  s21::Vector<int> B(values);
  A.pop_back();
  B.pop_back();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Vector_tests, shrink_to_fit) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  std::vector<int> A(values);
  s21::Vector<int> B(values);
  A.push_back(6);
  B.push_back(6);
  A.reserve(10);
  B.reserve(10);
  A.shrink_to_fit();
  B.shrink_to_fit();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
}

TEST(Vector_tests, swap) {
  s21::Vector<int> A({1, 2, 77, 4, 5});
  s21::Vector<int> B({10, 11, 12});
  A.swap(B);
  std::vector<int> C({1, 2, 77, 4, 5});
  std::vector<int> D({10, 11, 12});
  C.swap(D);
  EXPECT_EQ(A.size(), C.size());
  EXPECT_EQ(A.capacity(), C.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(A[i], C[i]);
  }
}

TEST(Vector_tests, empty) {
  s21::Vector<int> A({1, 2, 77, 4, 5});
  std::vector<int> B({1, 2, 77, 4, 5});
  EXPECT_EQ(A.empty(), B.empty());
  // ===
  s21::Vector<int> C;
  std::vector<int> D;
  EXPECT_EQ(C.empty(), D.empty());
}

TEST(Vector_tests, clear) {
  s21::Vector<int> A({1, 2, 77, 4, 5});
  std::vector<int> B({1, 2, 77, 4, 5});
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
}

TEST(Vector_tests, max_size) {
  s21::Vector<int> A;
  std::vector<int> B;
  EXPECT_EQ(A.max_size(), B.max_size());
}

TEST(Vector_tests, operator_equal) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  A = std::move(A);
  B = std::move(B);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // ===
  s21::Vector<int> C(values);
  std::vector<int> D(values);
  s21::Vector<int> E;
  std::vector<int> F;
  E = C;
  F = D;
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
  // ===
  s21::Vector<int> K(values);
  s21::Vector<int> L(values);
  K = K;
  L = L;
  EXPECT_EQ(K.size(), K.size());
  EXPECT_EQ(L.capacity(), L.capacity());
  for (size_t i = 0; i < K.size(); i++) {
    EXPECT_EQ(K[i], L[i]);
  }
}

TEST(Vector_tests, at) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.at(3), B.at(3));
}

TEST(Vector_tests, front) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.front(), B.front());
}

TEST(Vector_tests, back) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(A.back(), B.back());
}

TEST(Vector_tests, data) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(*A.data(), *B.data());
  EXPECT_EQ(*(A.data() + A.size() - 1), *(B.data() + B.size() - 1));
}

TEST(Vector_tests, begin) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  auto it_21 = A.begin();
  auto it_ = B.begin();
  EXPECT_EQ(*it_21, *it_);
}

TEST(Vector_tests, end) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  auto it_21 = A.end();
  auto it_ = B.end();
  EXPECT_EQ(*(--it_21), *(--it_));
}

TEST(Vector_tests, insert) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(10);
  std::vector<int> B(10);
  EXPECT_EQ(*(A.insert((A.begin() + 5), 777)),
            *(B.insert((B.begin() + 5), 777)));
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // ===
  s21::Vector<int> C;
  std::vector<int> D;
  EXPECT_EQ(*(C.insert(C.begin(), 777)), *(D.insert(D.begin(), 777)));
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  // ===
  s21::Vector<int> E(values);
  std::vector<int> F(values);
  EXPECT_EQ(*(C.insert(--(C.end()), 777)), *(D.insert(--(D.end()), 777)));
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < E.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}

TEST(Vector_tests, erase) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  A.erase(A.begin());
  B.erase(B.begin());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  s21::Vector<int> C(values);
  std::vector<int> D(values);
  C.erase((C.begin() + 3));
  D.erase((D.begin() + 3));
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < D.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
}

TEST(Vector_tests, emplace) {
  std::initializer_list<int> values{1, 2, 3, 4, 5};
  s21::Vector<int> A(values);
  std::vector<int> B(values);
  EXPECT_EQ(*(A.emplace(A.begin(), 77)), *(B.emplace(B.begin(), 77)));
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // ===
  s21::Vector<int> C;
  std::vector<int> D;
  EXPECT_EQ(*(C.emplace(C.begin(), 77)), *(D.emplace(D.begin(), 77)));
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  // ===
  s21::Vector<int> E(values);
  std::vector<int> F(values);
  EXPECT_EQ(*(C.emplace(--(C.end()), 77)), *(D.emplace(--(D.end()), 77)));
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < E.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}

TEST(Vector_tests, emplace_back) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Vector<int> A(10);
  std::vector<int> B(10);
  A.emplace_back(666);
  B.emplace_back(666);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.capacity(), B.capacity());
  for (size_t i = 0; i < A.size(); i++) {
    EXPECT_EQ(A[i], B[i]);
  }
  // ===
  s21::Vector<int> C;
  std::vector<int> D;
  C.emplace_back(77);
  D.emplace_back(77);
  EXPECT_EQ(C.size(), D.size());
  EXPECT_EQ(C.capacity(), D.capacity());
  for (size_t i = 0; i < C.size(); i++) {
    EXPECT_EQ(C[i], D[i]);
  }
  // ===
  s21::Vector<int> E(values);
  std::vector<int> F(values);
  C.emplace_back(1);
  D.emplace_back(1);
  EXPECT_EQ(E.size(), F.size());
  EXPECT_EQ(E.capacity(), F.capacity());
  for (size_t i = 0; i < E.size(); i++) {
    EXPECT_EQ(E[i], F[i]);
  }
}
