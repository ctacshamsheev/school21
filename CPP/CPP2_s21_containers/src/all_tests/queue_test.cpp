#include <queue>

#include "../s21_queue.h"

TEST(Queue_tests, constructor_initializer_list) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Queue<int> A(values);
  std::queue<int> B(values);
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A.front(), B.front());
  }
}

TEST(Queue_tests, constructor_copy) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Queue<int> A(values);
  s21::Queue<int> B(A);
  EXPECT_EQ(A.size(), B.size());
  while (!A.empty()) {
    EXPECT_EQ(A.front(), B.front());
    A.pop();
    B.pop();
  }
}

TEST(Queue_tests, constructor_move) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Queue<int> A(values);
  s21::Queue<int> B(std::move(A));
  std::queue<int> C(values);
  std::queue<int> D(std::move(C));
  EXPECT_EQ(B.size(), D.size());
  while (!B.empty()) {
    EXPECT_EQ(B.front(), D.front());
    B.pop();
    D.pop();
  }
}

TEST(Queue_tests, operator_equal) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Queue<int> A(values);
  s21::Queue<int> B({1, 2, 3});
  B = A;
  EXPECT_EQ(A.size(), B.size());
  while (!A.empty()) {
    EXPECT_EQ(A.front(), B.front());
    A.pop();
    B.pop();
  }
  s21::Queue<int> C(values);
  s21::Queue<int> D;
  D = C;
  EXPECT_EQ(C.size(), D.size());
  while (!D.empty()) {
    EXPECT_EQ(C.front(), D.front());
    C.pop();
    D.pop();
  }
}

TEST(Queue_tests, operator_equal_move) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Queue<int> A(values);
  s21::Queue<int> B;
  std::queue<int> C(values);
  std::queue<int> D;
  B = std::move(A);
  D = std::move(C);
  EXPECT_EQ(B.size(), D.size());
  while (!D.empty()) {
    EXPECT_EQ(B.front(), D.front());
    B.pop();
    D.pop();
  }
}

TEST(Queue_tests, push) {
  s21::Queue<int> A;
  std::queue<int> B;
  A.push(100);
  A.push(200);
  A.push(300);
  B.push(100);
  B.push(200);
  B.push(300);
  EXPECT_EQ(A.size(), B.size());
  while (!B.empty()) {
    EXPECT_EQ(A.front(), B.front());
    A.pop();
    B.pop();
  }
}

TEST(Queue_tests, back) {
  s21::Queue<int> A({1, 2, 3, 4, 5});
  std::queue<int> B({1, 2, 3, 4, 5});
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.back(), B.back());
}

TEST(Queue_tests, swap) {
  s21::Queue<int> A({1, 2, 3, 4, 5});
  std::queue<int> B({1, 2, 3, 4, 5});
  s21::Queue<int> C({11, 12, 13, 14, 15});
  std::queue<int> D({11, 12, 13, 14, 15});
  A.swap(C);
  B.swap(D);
  EXPECT_EQ(A.size(), B.size());
  while (!A.empty()) {
    EXPECT_EQ(A.front(), B.front());
    A.pop();
    B.pop();
  }
}

TEST(Queue_tests, emplace_front) {
  s21::Queue<int> A;
  std::queue<int> B;
  A.emplace_back(777);
  B.emplace(777);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.front(), B.front());
}
