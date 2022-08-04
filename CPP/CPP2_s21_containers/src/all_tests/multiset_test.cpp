#include "../s21_multiset.h"

using namespace s21;

template <typename T>
void test_eq(multiset<T> &a, std::multiset<T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto iter_std = std_a.begin();
  auto iter = a.begin();
  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(*iter, *iter_std);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_multiset, create_1) {
  multiset<int> a;
  std::multiset<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.insert(5), *std_a.insert(5));
  test_eq<int>(a, std_a);
}

TEST(s21_multiset, create_2) {
  multiset<int> a{1, 1, 2, 3, 3, 4, 4, 4, 5};
  std::multiset<int> std_a{1, 1, 2, 3, 3, 4, 4, 4, 5};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.insert(5), *std_a.insert(5));
  test_eq<int>(a, std_a);
}

TEST(s21_multiset, create_3_copy) {
  multiset<int> a{1, 1, 2, 3,  3,  4, 4, 4,  5,  12, 9,  4,  4, 4,
                  2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{1, 1, 2, 3,  3,  4, 4, 4,  5,  12, 9,  4,  4, 4,
                           2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  multiset<int> b(a);
  std::multiset<int> std_b(std_a);
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_multiset, create_3_move) {
  multiset<int> a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                  10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                           10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  multiset<int> b(std::move(a));
  std::multiset<int> std_b(std::move(std_a));
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_multiset, operator_eq) {
  multiset<int> a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                  10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                           10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  multiset<int> b{12};
  std::multiset<int> std_b{12};
  b = a;
  std_b = std_a;
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_multiset, insert_1) {
  multiset<int> a;
  std::multiset<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.insert(5), *std_a.insert(5));
  EXPECT_EQ(*a.insert(5), *std_a.insert(5));
  EXPECT_EQ(*a.insert(7), *std_a.insert(7));
  EXPECT_EQ(a.size(), std_a.size());
}
TEST(s21_multiset, find_1) {
  multiset<int> a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                  10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                           10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.contains(5), true);
  EXPECT_EQ(*a.find(5), *std_a.find(5));
  EXPECT_EQ(a.contains(12), true);
  EXPECT_EQ(*a.find(12), *std_a.find(12));
  EXPECT_EQ(a.contains(20), false);
  EXPECT_EQ(a.find(20) == a.end(), true);
  EXPECT_EQ(std_a.find(20) == std_a.end(), true);
}

TEST(s21_multiset, erase_1) {
  std::vector<int> v = {0, 1, 2, 2, 3,  3,  4, 4, 4,  5,  12, 9,  4,  4,
                        4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  for (auto i : v) {
    multiset<int> a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                    10, 5, 6, 18, 25, 16, 14, 17, 13};
    std::multiset<int> std_a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                             10, 5, 6, 18, 25, 16, 14, 17, 13};
    EXPECT_EQ(a.erase(i), std_a.erase(i));
    test_eq<int>(a, std_a);
  }
}

TEST(s21_multiset, erase_2) {
  std::vector<int> v = {0, 1, 2, 2, 3,  3,  4, 4, 4,  5,  12, 9,  4,  4,
                        4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  multiset<int> a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                  10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{12, 9, 4, 4,  4,  2,  1,  3,  11,
                           10, 5, 6, 18, 25, 16, 14, 17, 13};
  for (auto i : v) {
    EXPECT_EQ(a.erase(i), std_a.erase(i));
    test_eq<int>(a, std_a);
  }
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_multiset, erase_3) {
  std::multiset<int> std_a = {2, 3, 1, 2, 3, 4};
  multiset<int> a{2, 3, 1, 2, 3, 4};

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
  test_eq<int>(a, std_a);
}

TEST(s21_multiset, merge) {
  multiset<int> a{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
  multiset<int> b{12, 9, 4, 4,  4,  2,  1,  3,  11,
                  10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{10, 11, 12, 13, 14, 15, 16,
                           17, 18, 19, 20, 21, 22, 23};
  std::multiset<int> std_b{12, 9, 4, 4,  4,  2,  1,  3,  11,
                           10, 5, 6, 18, 25, 16, 14, 17, 13};
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);

  a.merge(b);
  std_a.merge(std_b);
  EXPECT_EQ(a.count(10), std_a.count(10));
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_multiset, swap_1) {
  multiset<int> a{0, 1, 2, 2, 3,  3,  4, 4, 4,  5,  12, 9,  4,  4,
                  4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{0, 1, 2, 2, 3,  3,  4, 4, 4,  5,  12, 9,  4,  4,
                           4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  multiset<int> b{5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_b{5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(b.size(), std_b.size());
  a.swap(b);
  std_a.swap(std_b);
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_multiset, equal_range) {
  multiset<int> a{12, 4, 4, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::multiset<int> std_a{12, 4, 4,  4,  2,  1,  3,  11, 10,
                           5,  6, 18, 25, 16, 14, 17, 13};
  for (int key = -1; key != 29; key++) {
    auto std_itlb = std_a.lower_bound(key);
    auto itlb = a.lower_bound(key);
    auto std_itub = std_a.upper_bound(key);
    auto itub = a.upper_bound(key);
    auto p = a.equal_range(key);
    auto std_p = std_a.equal_range(key);
    if (itlb != a.end()) {
      EXPECT_EQ(*itlb, *std_itlb);
      EXPECT_EQ(*(p.first), *(std_p.first));
    } else {
      EXPECT_EQ(itlb, a.end());
      EXPECT_EQ(std_itlb, std_a.end());
    }
    if (itub != a.end()) {
      EXPECT_EQ(*itub, *std_itub);
      EXPECT_EQ(*(p.second), *(std_p.second));
    } else {
      EXPECT_EQ(itub, a.end());
      EXPECT_EQ(std_itub, std_a.end());
    }
  }
}

TEST(s21_multiset, emplace) {
  multiset<int> a{1, 1, 2, 3, 3, 4, 4, 4, 5};
  std::multiset<int> std_a{1, 1, 2, 3, 3, 4, 4, 4, 5};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.emplace(5), *std_a.emplace(5));
  EXPECT_EQ(*a.emplace(5), *std_a.emplace(5));
  EXPECT_EQ(*a.emplace(7), *std_a.emplace(7));
  test_eq<int>(a, std_a);
}
