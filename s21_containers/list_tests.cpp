#include <gtest/gtest.h>
#include "list.h"

class ListTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case.
    List<int> list;
};

TEST_F(ListTest, DefaultConstructor) {
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST_F(ListTest, InitializerListConstructor) {
    List<int> list{1, 2, 3};
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST_F(ListTest, CopyConstructor) {
    List<int> list1{1, 2, 3};
    List<int> list2(list1);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

TEST_F(ListTest, MoveConstructor) {
    List<int> list1{1, 2, 3};
    List<int> list2(std::move(list1));
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
    EXPECT_EQ(list1.size(), 0);  // List1 should be empty after move
}

TEST_F(ListTest, PushFront) {
    list.push_front(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);

    list.push_front(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
}

TEST_F(ListTest, PushBack) {
    list.push_back(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);

    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
}

TEST_F(ListTest, PopFront) {
    list.push_back(1);
    list.push_back(2);
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 2);
}

TEST_F(ListTest, PopBack) {
    list.push_back(1);
    list.push_back(2);
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 1);
}

TEST_F(ListTest, Clear) {
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST_F(ListTest, Swap) {
    List<int> list1{1, 2, 3};
    List<int> list2{4, 5, 6};
    list1.swap(list2);

    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front(), 4);
    EXPECT_EQ(list1.back(), 6);

    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

TEST_F(ListTest, Merge) {
    List<int> list1{1, 3, 5};
    List<int> list2{2, 4, 6};
    list1.merge(list2);

    EXPECT_EQ(list1.size(), 6);
    EXPECT_EQ(list1.front(), 1);
    EXPECT_EQ(list1.back(), 6);
    EXPECT_TRUE(list2.empty());
}

TEST_F(ListTest, FrontBackException) {
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST_F(ListAdvancedTest, Splice) {
  List<int> list1{1, 2, 3};
  List<int> list2{4, 5, 6};
  auto it = list1.begin();
  ++it; // Pointing to 2

  list1.splice(it, list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(list2.empty());

  auto list1_it = list1.begin();
  EXPECT_EQ(*list1_it++, 1);
  EXPECT_EQ(*list1_it++, 4);
  EXPECT_EQ(*list1_it++, 5);
  EXPECT_EQ(*list1_it++, 6);
  EXPECT_EQ(*list1_it++, 2);
  EXPECT_EQ(*list1_it++, 3);
}

TEST_F(ListAdvancedTest, SpliceSelf) {
  List<int> list1{1, 2, 3};
  auto it = list1.begin();
  ++it; // Pointing to 2

  EXPECT_THROW(list1.splice(it, list1), std::invalid_argument);
}

TEST_F(ListAdvancedTest, Reverse) {
  List<int> list1{1, 2, 3};
  list1.reverse();

  EXPECT_EQ(list1.size(), 3);
  auto it = list1.begin();
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 1);
}

TEST_F(ListAdvancedTest, Unique) {
  List<int> list1{1, 1, 2, 3, 3, 3, 4};
  list1.unique();

  EXPECT_EQ(list1.size(), 4);
  auto it = list1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}

TEST_F(ListAdvancedTest, Sort) {
  List<int> list1{4, 3, 1, 2};
  list1.sort();

  EXPECT_EQ(list1.size(), 4);
  auto it = list1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}