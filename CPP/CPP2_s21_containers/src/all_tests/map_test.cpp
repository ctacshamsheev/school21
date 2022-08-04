#include "../s21_map.h"

using namespace s21;

template <typename K, typename T>
void test_eq(map<K, T> &a, std::map<K, T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto iter_std = std_a.begin();
  auto iter = a.begin();
  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(iter->first, iter_std->first);
    EXPECT_EQ(iter->second, iter_std->second);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_map, create_1) {
  std::map<int, double> std_a;
  map<int, double> a;
  test_eq(a, std_a);
  std_a.insert({5, 2});
  a.insert({5, 2});
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, create_2) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, create_3_copy) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  map<int, double> b(a);
  std::map<int, double> std_b(std_a);
  test_eq<int, double>(a, std_a);
  test_eq<int, double>(b, std_b);
}

TEST(s21_map, create_3_move) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  map<int, double> b(std::move(a));
  std::map<int, double> std_b(std::move(std_a));
  test_eq<int, double>(a, std_a);
  test_eq<int, double>(b, std_b);
}

TEST(s21_map, insert_1) {
  std::map<int, double> std_a;
  map<int, double> a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ((std_a.insert({1, 2}).second), (a.insert({1, 2}).second));  // true
  EXPECT_EQ((std_a.insert({1, 3}).second), (a.insert({1, 3}).second));  // false
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ((std_a.insert({0, 4}).first->second),
            (a.insert({0, 4}).first->second));
  EXPECT_EQ((std_a.insert({2, 4}).first->first),
            (a.insert({2, 4}).first->first));
  std_a.insert({5, 2});
  std_a.insert({2, 2});
  std_a.insert({3, 2});
  std_a.insert({3, 3});
  std_a.insert({3, 0});
  a.insert({5, 2});
  a.insert({2, 2});
  a.insert({3, 2});
  a.insert({3, 3});
  a.insert({3, 0});
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, erase_it) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};

  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};

  EXPECT_EQ(a.size(), std_a.size());
  int i = 0;
  auto iter_std = std_a.begin();
  auto iter = a.begin();

  while (iter_std != std_a.end() && iter != a.end()) {
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
  test_eq(a, std_a);
}

TEST(s21_map, operator_eq) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  map<int, double> b{{1, 1}};
  std::map<int, double> std_b{{1, 1}};
  b = a;
  std_b = std_a;
  test_eq<int, double>(a, std_a);
  test_eq<int, double>(b, std_b);
}

TEST(s21_map, contains) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());

  for (int i = -1; i < 20; i++) {
    auto iter_std = std_a.find(i);
    bool flag = (iter_std != std_a.end());
    EXPECT_EQ(a.contains(i), flag);
  }
}

TEST(s21_map, find) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};

  for (int i = -1; i < 20; i++) {
    if (a.contains(i)) {
      EXPECT_EQ(a.find(5)->first, std_a.find(5)->first);
      EXPECT_EQ(a.find(5)->second, std_a.find(5)->second);
    } else {
      EXPECT_EQ((std_a.find(i) == std_a.end()), (a.find(i) == a.end()));
    }
  }
}

TEST(s21_map, at) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  std_a.at(5) = 20;
  a.at(5) = 20;
  std_a.at(3) = 30;
  a.at(3) = 30;
// утечка на маке в leaks
#ifndef __APPLE__
  EXPECT_THROW(std_a.at(-1), std::out_of_range);
  EXPECT_THROW(a.at(-1), std::out_of_range);
#endif
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, operator_at) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  std_a[5] = 20;
  a[5] = 20;
  std_a[3] = 30;
  a[3] = 30;

  test_eq<int, double>(a, std_a);
// утечка на маке в leaks
#ifndef __APPLE__
  EXPECT_THROW(a[-1], std::out_of_range);
#endif
}

TEST(s21_map, insert_or_assign) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int, double>(a, std_a);

  for (int i = -1; i < 10; i++) {
    EXPECT_EQ(a.insert_or_assign(i, i * 2).second,
              std_a.insert_or_assign(i, i * 2).second);
  }
  test_eq<int, double>(a, std_a);
}

// утечка на маке в leaks
#ifndef __APPLE__
TEST(s21_map, except_throw) {
  set<int> a{};
  auto iter = a.end();
  EXPECT_THROW(*iter, std::out_of_range);
  EXPECT_THROW(a.swap(a), std::invalid_argument);
}
#endif

TEST(s21_map, emplace) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  test_eq<int, double>(a, std_a);
  EXPECT_EQ((std_a.emplace(7, 1).first)->first,
            (a.emplace(std::pair{7, 1}).first)->first);
  EXPECT_EQ((std_a.emplace(10, 1).first)->second,
            (a.emplace(std::pair{10, 1}).first)->second);
  EXPECT_EQ((std_a.emplace(12, 1).second),
            (a.emplace(std::pair{12, 1}).second));
  EXPECT_EQ((std_a.emplace(12, 2).second),
            (a.emplace(std::pair{12, 2}).second));
  test_eq<int, double>(a, std_a);
}