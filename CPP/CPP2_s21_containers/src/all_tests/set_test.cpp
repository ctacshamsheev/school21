

#include "../s21_set.h"

using namespace s21;

using std::cin;
using std::cout;
using std::endl;

TEST(s21_set, create_1) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  a.insert(5);
  std_a.insert(5);
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_set, create_2) {
  set<int> a{1, 2, 3, 4, 5};
  std::set<int> std_a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), std_a.size());

  a.insert(5);
  std_a.insert(5);
  EXPECT_EQ(a.size(), std_a.size());

  auto iter_std = std_a.begin();
  auto iter = a.begin();

  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(*iter, *iter_std);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_set, create_3_copy) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b(a);
  std::set<int> std_b(std_a);
  EXPECT_EQ(b.size(), std_b.size());
  auto iter_std = std_b.begin();
  auto iter = b.begin();
  while (iter_std != std_b.end() && iter != b.end()) {
    EXPECT_EQ(*iter, *iter_std);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_set, create_3_move) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b(std::move(a));
  std::set<int> std_b(std::move(std_a));
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  auto iter_std = std_b.begin();
  auto iter = b.begin();
  while (iter_std != std_b.end() && iter != b.end()) {
    EXPECT_EQ(*iter, *iter_std);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_set, insert_1) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.insert(5).first, *std_a.insert(5).first);
  EXPECT_EQ(a.insert(5).second, std_a.insert(5).second);
  EXPECT_EQ(a.insert(6).second, std_a.insert(6).second);
  EXPECT_EQ(*a.insert(7).first, *std_a.insert(7).first);
  EXPECT_EQ(a.size(), std_a.size());
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

    auto iter_std = std_a.begin();
    auto iter = a.begin();
    while (iter_std != std_a.end() && iter != a.end()) {
      EXPECT_EQ(*iter, *iter_std);
      ++iter;
      ++iter_std;
    }
  }
}

TEST(s21_set, erase_2) {
  std::vector<int> v = {0, 1,  2,  3, 4, 5,  12, 9,  4,  2,  1,
                        3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  for (auto i : v) {
    EXPECT_EQ(a.erase(i), std_a.erase(i));

    auto iter_std = std_a.begin();
    auto iter = a.begin();
    while (iter_std != std_a.end() && iter != a.end()) {
      EXPECT_EQ(*iter, *iter_std);
      ++iter;
      ++iter_std;
    }
  }
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(s21_set, balance) {
  set<int> a{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
  std::cout << a << std::endl;
}

// EXPECT_EQ(a.size(), std_a.size());
// iter_std = std_a.begin();
// iter = a.begin();

// std::cout << "iterator [ ";
// while (iter_std != std_a.end() && iter != a.end()) {
//   EXPECT_EQ(*iter, *iter_std);
//   std::cout << *iter << " " << *iter_std << std::endl;

//   ++iter;
//   ++iter_std;
// }
// std::cout << "]" << std::endl;

// std::cout << a << std::endl;
// a.erase(9);
// std::cout << a << std::endl;
// a.erase(12);
// std::cout << a << std::endl;
// a.erase(-1);
// std::cout << a << std::endl;
// std::cout << "___________________ 13 ___________________ " << std::endl;
// a.erase(13);
// std::cout << a << std::endl;

// TEST(s21_set, create) {
//   std::cout << std::endl
//             << "___________________ d ___________________ " << std::endl;
//   set<int> d = {6, 1, 2, -1, 11, 4, 3, 5, 7};
//   std::cout << d << std::endl;
//   // std::cout << "begin" << *d.begin() << std::endl;
//   //  std::cout << *d.end() << std::endl;
//   std::cout << "size " << d.size() << std::endl;
//   std::cout << "___________________ v ___________________ " << std::endl;

//   set<int> v;
//   v.say();
//   v.insert(5);
//   v.insert(2);
//   bool flag = v.insert(7);
//   EXPECT_TRUE(flag);
//   v.insert(1);
//   v.insert(1);
//   v.insert(4);
//   flag = v.insert(7);
//   EXPECT_FALSE(flag);
//   v.insert(6);
//   v.insert(8);
//   v.insert(4);
//   v.insert(7);
//   v.insert(6);
//   v.insert(8);
//   v.insert(9);
//   std::cout << v << std::endl;
//   // std::cout << "begin" << *v.begin() << std::endl;
//   //  std::cout << *v.end() << std::endl;
//   std::cout << "size " << v.size() << std::endl;

//   // std::cout << std::endl
//   //           << "___________________ cp ___________________ " <<
//   std::endl;

//   // set<int> cp(v);
//   // std::cout << cp << std::endl;

//   std::cout << std::endl
//             << "___________________ move ___________________ " <<
//             std::endl;

//   // set<int> m(std::move(cp));
//   // std::cout << m << std::endl;
//   // // std::cout << cp << std::endl; /// cppcheck Access of moved variable
//   'cp'. std::cout << std::endl
//             << "___________________ tree ___________________ " <<
//             std::endl;

//   set<int> tree = {12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17,
//   13}; std::cout << tree << std::endl;
//   // set<int>::iterator iter = tree.begin();
//   std::cout << "iterator [ ";
//   for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
//     std::cout << *iter << " ";
//   }
//   std::cout << "]" << std::endl;

//   tree.insert(7);
//   tree.insert(7);
//   tree.insert(8);
//   tree.insert(15);
//   tree.insert(19);
//   tree.insert(20);

//   std::cout << std::endl
//             << "___________________ 1 ___________________ " << std::endl;
//   int key = 21;
//   std::cout << "count " << key << " = " << tree.count(key) << std::endl;
//   key = 7;
//   std::cout << "count " << key << " = " << tree.count(key) << std::endl;
//   key = 9;
//   std::cout << "count " << key << " = " << tree.count(key) << std::endl;

//   std::cout << tree << std::endl;

//   std::cout << "iterator [ ";
//   for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
//     std::cout << *iter << " ";
//   }
//   std::cout << "]" << std::endl;
//   std::cout << std::endl
//             << "___________________ end ___________________ " << std::endl;
//   // TODO erase
//   // tree.erase(4);
//   // std::cout << tree << std::endl;

//   EXPECT_EQ(1, 1);
//   std::cout << " =) " << std::endl;
// }

// TEST(s21_set, DISABLED_string) {
//   std::cout << std::endl
//             << "___________________ str ___________________ " << std::endl;

//   set<char> tree = {
//       'E', 'l', 'E', 't', 'm', 'F', 'a', 'P', 'f', 'r', 'K', 'A', 'l', 't',
//       'T',
//   };
//   std::cout << tree << std::endl;
//   // set<char>::iterator iter = tree.begin();
//   std::cout << "iterator [ ";
//   for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
//     std::cout << *iter << " ";
//   }
//   std::cout << "]" << std::endl;

//   tree.insert('z');
//   tree.insert('z');
//   tree.insert('B');
//   tree.insert('b');
//   tree.insert('v');
//   tree.insert('V');

//   char key = 'p';
//   std::cout << "count " << key << " = " << tree.count(key) << std::endl;
//   key = 'a';
//   std::cout << "count " << key << " = " << tree.count(key) << std::endl;
//   key = 'z';
//   std::cout << "count " << key << " = " << tree.count(key) << std::endl;

//   std::cout << tree << std::endl;

//   std::cout << "iterator [ ";
//   for (set<char>::iterator iter = tree.begin(); iter != tree.end(); ++iter)
//   {
//     std::cout << *iter << " ";
//   }
//   std::cout << "]" << std::endl;

//   EXPECT_EQ(1, 1);
//   std::cout << " =) " << std::endl;
// }

// TEST(method, det_calc_comp_invers_err2) {
//   // S21Matrix a(3, 3);
//   // S21Matrix b(2, 2);
//   // S21Matrix c(1, 1);
//   // double f[]{0, 1, 2, 3, 4, 5, 6, 7, 8};
//   // double f2[]{1, 2, 4, 8};
//   // a.set_matrix(f);
//   // b.set_matrix(f2);
//   // c.set_matrix(f);
//   // // определитель = 0
//   // EXPECT_EQ(a.determinant(), 0);
//   // EXPECT_EQ(b.determinant(), 0);
//   // EXPECT_EQ(c.determinant(), 0);
//   // EXPECT_THROW(a.inverse_matrix(), std::invalid_argument);
//   // EXPECT_THROW(b.inverse_matrix(), std::invalid_argument);
//   // EXPECT_THROW(c.inverse_matrix(), std::invalid_argument);
// }
