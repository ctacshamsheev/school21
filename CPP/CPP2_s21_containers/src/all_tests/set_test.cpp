#include "../s21_set.h"

using namespace s21;

template <typename T>
void test_eq(set<T> &a, std::set<T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto iter_std = std_a.begin();
  auto iter = a.begin();
  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(*iter, *iter_std);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_set, create_1) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.empty(), std_a.empty());
  a.max_size();
  a.insert(5);
  std_a.insert(5);
  test_eq<int>(a, std_a);
}

TEST(s21_set, create_2) {
  set<int> a{1, 2, 3, 4, 5};
  std::set<int> std_a{1, 2, 3, 4, 5};
  a.insert(5);
  std_a.insert(5);
  test_eq<int>(a, std_a);
}

TEST(s21_set, create_3_copy) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b(a);
  std::set<int> std_b(std_a);
  test_eq<int>(a, std_a);
}

TEST(s21_set, create_3_move) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b(std::move(a));
  std::set<int> std_b(std::move(std_a));
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, operator_equal) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b{1};
  std::set<int> std_b{1};
  b = a;
  std_b = std_a;
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, operator_eq) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b{1};
  std::set<int> std_b{1};
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
  b = a;
  std_b = std_a;
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, insert_1) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.insert(5).first, *std_a.insert(5).first);
  EXPECT_EQ(a.insert(5).second, std_a.insert(5).second);
  EXPECT_EQ(a.insert(6).second, std_a.insert(6).second);
  EXPECT_EQ(*a.insert(7).first, *std_a.insert(7).first);
  test_eq<int>(a, std_a);
}

TEST(s21_set, find_1) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.contains(5), true);
  // EXPECT_EQ(std_a.contains(5), true);
  // class std::set<int>’ has no member named ‘contains’
  EXPECT_EQ(*a.find(5), *std_a.find(5));
  EXPECT_EQ(a.contains(12), true);
  EXPECT_EQ(*a.find(12), *std_a.find(12));
  EXPECT_EQ(a.contains(20), false);
  EXPECT_EQ(a.find(20) == a.end(), true);
  EXPECT_EQ(std_a.find(20) == std_a.end(), true);
}

TEST(s21_set, erase_1) {
  std::vector<int> v = {0, 1,  2,  3, 4, 5,  12, 9,  4,  2,  1,
                        3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  for (auto i : v) {
    set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
    std::set<int> std_a{12, 9, 4,  2,  1,  3,  11, 10,
                        5,  6, 18, 25, 16, 14, 17, 13};
    EXPECT_EQ(a.erase(i), std_a.erase(i));
    test_eq<int>(a, std_a);
  }
}

TEST(s21_set, erase_2) {
  std::vector<int> v = {0, 1,  2,  3, 4, 5,  12, 9,  4,  2,  1,
                        3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  for (auto i : v) {
    EXPECT_EQ(a.erase(i), std_a.erase(i));
    test_eq<int>(a, std_a);
  }
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_set, erase_3) {
  std::set<int> std_a = {1, 2, 3, 4, 5, 6, 7, 8};

  set<int> a{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(a.size(), std_a.size());
  int i = 0;
  auto iter_std = std_a.begin();
  auto iter = a.begin();

  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(*iter, *iter_std);
    auto tmp_std = iter_std;
    auto tmp = iter;
    ++iter_std;
    ++iter;
    if (i % 2 == 0) {
      std_a.erase(tmp_std);
      a.erase(tmp);
    }
    i++;
  }
  test_eq<int>(a, std_a);
  EXPECT_EQ(a.erase(1), std_a.erase(1));
  EXPECT_EQ(a.erase(2), std_a.erase(2));
  EXPECT_EQ(a.erase(2), std_a.erase(2));
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_set, merge) {
  set<int> a{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
  set<int> b{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
  std::set<int> std_b{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
  a.merge(b);
  std_a.merge(std_b);
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.count(10), std_a.count(10));
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, swap_1) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10};
  set<int> b{5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_b{5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(b.size(), std_b.size());
  a.swap(b);
  std_a.swap(std_b);
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, emplace) {
  set<int> a{1, 2, 3, 4, 5};
  std::set<int> std_a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.emplace(7).second, std_a.emplace(7).second);
  EXPECT_EQ(a.emplace(7).second, std_a.emplace(7).second);
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.emplace(9).first, *std_a.emplace(9).first);
  test_eq<int>(a, std_a);
}

// утечка на маке в leaks
#ifndef __APPLE__
TEST(s21_set, except_throw) {
  set<int> a{};
  auto iter = a.end();
  EXPECT_THROW(*iter, std::out_of_range);
  EXPECT_THROW(a.swap(a), std::invalid_argument);
}
#endif