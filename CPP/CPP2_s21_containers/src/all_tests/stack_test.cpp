#include <stack>

#include "../s21_stack.h"

TEST(Stack_tests, constructor_initializer_list) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Stack<int> A(values);
  std::stack<int> B(values);
  EXPECT_EQ(A.size(), B.size());
  for (size_t i = 0; i < B.size(); i++) {
    EXPECT_EQ(A.top(), B.top());
  }
}

TEST(Stack_tests, constructor_copy) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Stack<int> A(values);
  s21::Stack<int> B(A);
  EXPECT_EQ(A.size(), B.size());
  while (!A.empty()) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(Stack_tests, constructor_move) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Stack<int> A(values);
  s21::Stack<int> B(std::move(A));
  std::stack<int> C(values);
  std::stack<int> D(std::move(C));
  EXPECT_EQ(B.size(), D.size());
  while (!B.empty()) {
    EXPECT_EQ(B.top(), D.top());
    B.pop();
    D.pop();
  }
}

TEST(Stack_tests, operator_equal) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Stack<int> A(values);
  s21::Stack<int> B({1, 2, 3});
  B = A;
  EXPECT_EQ(A.size(), B.size());
  while (!A.empty()) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
  s21::Stack<int> C(values);
  s21::Stack<int> D;
  D = C;
  EXPECT_EQ(C.size(), D.size());
  while (!D.empty()) {
    EXPECT_EQ(C.top(), D.top());
    C.pop();
    D.pop();
  }
}

TEST(Stack_tests, operator_equal_move) {
  std::initializer_list<int> values{1, 2, 77, 4, 5};
  s21::Stack<int> A(values);
  s21::Stack<int> B;
  std::stack<int> C(values);
  std::stack<int> D;
  B = std::move(A);
  D = std::move(C);
  EXPECT_EQ(B.size(), D.size());
  while (!D.empty()) {
    EXPECT_EQ(B.top(), D.top());
    B.pop();
    D.pop();
  }
}

TEST(Stack_tests, push) {
  s21::Stack<int> A;
  std::stack<int> B;
  A.push(100);
  A.push(200);
  A.push(300);
  B.push(100);
  B.push(200);
  B.push(300);
  EXPECT_EQ(A.size(), B.size());
  while (!B.empty()) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(Stack_tests, swap) {
  s21::Stack<int> A({1, 2, 3, 4, 5});
  std::stack<int> B({1, 2, 3, 4, 5});
  s21::Stack<int> C({11, 12, 13, 14, 15});
  std::stack<int> D({11, 12, 13, 14, 15});
  A.swap(C);
  B.swap(D);
  EXPECT_EQ(A.size(), B.size());
  while (!A.empty()) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(Stack_tests, emplace_front) {
  s21::Stack<int> A;
  std::stack<int> B;
  A.emplace_front(777);
  B.emplace(777);
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.top(), B.top());
}
