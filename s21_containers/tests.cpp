#include "list/list.h"
#include "vector/vector.h"
#include "stack/stack.h"
#include "queue/queue.h"
#include <stdexcept>
#include <gtest/gtest.h>
namespace s21 {
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
  List<int> list = {1, 2, 3};
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

TEST_F(ListTest, Splice) {
  List<int> list1{1, 2, 3};
  List<int> list2{4, 5, 6};
  auto it = list1.begin();
  ++it;  // Pointing to 2

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

TEST_F(ListTest, SpliceSelf) {
  List<int> list1{1, 2, 3};
  auto it = list1.begin();
  ++it;  // Pointing to 2

  EXPECT_THROW(list1.splice(it, list1), std::invalid_argument);
}

TEST_F(ListTest, Reverse) {
  List<int> list1{1, 2, 3};
  list1.reverse();

  EXPECT_EQ(list1.size(), 3);
  auto it = list1.begin();
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 1);
}

TEST_F(ListTest, Unique) {
  List<int> list1{1, 1, 2, 3, 3, 3, 4};
  list1.unique();

  EXPECT_EQ(list1.size(), 4);
  auto it = list1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}

TEST_F(ListTest, Sort) {
  List<int> list1{4, 3, 1, 2};
  list1.sort();

  EXPECT_EQ(list1.size(), 4);
  auto it = list1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}


// Тестирование конструктора по умолчанию
TEST(VectorTest, DefaultConstructor) {
  s21::Vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

// Тестирование конструктора с размером
TEST(VectorTest, SizeConstructor) {
  s21::Vector<int> v(5);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
}

// Тестирование конструктора с инициализатором
TEST(VectorTest, InitializerListConstructor) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 3);
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
}

// Тестирование копирующего конструктора
TEST(VectorTest, CopyConstructor) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2.capacity(), 3);
  EXPECT_EQ(v2.front(), 1);
  EXPECT_EQ(v2.back(), 3);
}

// Тестирование перемещающего конструктора
TEST(VectorTest, MoveConstructor) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2.capacity(), 3);
  EXPECT_EQ(v2.front(), 1);
  EXPECT_EQ(v2.back(), 3);
  EXPECT_TRUE(v1.empty());
}

// Тестирование перемещающего оператора присваивания
TEST(VectorTest, MoveAssignment) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2.capacity(), 3);
  EXPECT_EQ(v2.front(), 1);
  EXPECT_EQ(v2.back(), 3);
  EXPECT_TRUE(v1.empty());
}

// Тестирование метода at
TEST(VectorTest, At) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_THROW(v.at(3), std::out_of_range);
}

// Тестирование метода operator[]
TEST(VectorTest, BracketOperator) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

// Тестирование метода front
TEST(VectorTest, Front) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v.front(), 1);
}

// Тестирование метода back
TEST(VectorTest, Back) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v.back(), 3);
}

// Тестирование метода data
TEST(VectorTest, Data) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v.data()[0], 1);
  EXPECT_EQ(v.data()[1], 2);
  EXPECT_EQ(v.data()[2], 3);
}

// Тестирование метода empty
TEST(VectorTest, Empty) {
  s21::Vector<int> v;
  EXPECT_TRUE(v.empty());
  v.push_back(1);
  EXPECT_FALSE(v.empty());
}

// Тестирование метода size
TEST(VectorTest, Size) {
  s21::Vector<int> v({1, 2, 3});
  EXPECT_EQ(v.size(), 3);
}

// Тестирование метода max_size
TEST(VectorTest, MaxSize) {
  s21::Vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

// Тестирование метода reserve
TEST(VectorTest, Reserve) {
  s21::Vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_THROW(v.reserve(v.max_size() + 1), std::length_error);
}

// Тестирование метода shrink_to_fit
TEST(VectorTest, ShrinkToFit) {
  s21::Vector<int> v({1, 2, 3});
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

// Тестирование метода clear
TEST(VectorTest, Clear) {
  s21::Vector<int> v({1, 2, 3});
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

// Тестирование метода insert
TEST(VectorTest, Insert) {
  s21::Vector<int> v({1, 3});
  v.insert(v.begin() + 1, 2);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[1], 2);
}

// Тестирование метода erase
TEST(VectorTest, Erase) {
  s21::Vector<int> v({1, 2, 3});
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[1], 3);
}

// Тестирование метода push_back
TEST(VectorTest, PushBack) {
  s21::Vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.back(), 1);
}

// Тестирование метода pop_back
TEST(VectorTest, PopBack) {
  s21::Vector<int> v({1, 2, 3});
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);
}

// Тестирование метода swap
TEST(VectorTest, Swap) {
  s21::Vector<int> v1({1, 2, 3});
  s21::Vector<int> v2({4, 5});
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
}


// Тестирование конструктора по умолчанию
TEST(StackTest, DefaultConstructor) {
  s21::Stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// Тестирование конструктора с инициализатором
TEST(StackTest, InitializerListConstructor) {
  s21::Stack<int> s({1, 2, 3});
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
}

// Тестирование копирующего конструктора
TEST(StackTest, CopyConstructor) {
  s21::Stack<int> s1({1, 2, 3});
  s21::Stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

// Тестирование перемещающего конструктора
TEST(StackTest, MoveConstructor) {
  s21::Stack<int> s1({1, 2, 3});
  s21::Stack<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_TRUE(s1.empty());
}

// Тестирование перемещающего оператора присваивания
TEST(StackTest, MoveAssignment) {
  s21::Stack<int> s1({1, 2, 3});
  s21::Stack<int> s2;
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_TRUE(s1.empty());
}

// Тестирование метода top
TEST(StackTest, Top) {
  s21::Stack<int> s({1, 2, 3});
  EXPECT_EQ(s.top(), 3);
  s.push(4);
  EXPECT_EQ(s.top(), 4);
  s.pop();
  EXPECT_EQ(s.top(), 3);
}

// Тестирование метода push
TEST(StackTest, Push) {
  s21::Stack<int> s;
  s.push(1);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 1);
  s.push(2);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 2);
}

// Тестирование метода pop
TEST(StackTest, Pop) {
  s21::Stack<int> s({1, 2, 3});
  s.pop();
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_TRUE(s.empty());
}

// Тестирование метода swap
TEST(StackTest, Swap) {
  s21::Stack<int> s1({1, 2, 3});
  s21::Stack<int> s2({4, 5});
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s1.top(), 5);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}


// Тестирование конструктора по умолчанию
TEST(QueueTest, DefaultConstructor) {
  s21::Queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

// Тестирование конструктора с инициализатором
TEST(QueueTest, InitializerListConstructor) {
  s21::Queue<int> q({1, 2, 3});
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

// Тестирование копирующего конструктора
TEST(QueueTest, CopyConstructor) {
  s21::Queue<int> q1({1, 2, 3});
  s21::Queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

// Тестирование перемещающего конструктора
TEST(QueueTest, MoveConstructor) {
  s21::Queue<int> q1({1, 2, 3});
  s21::Queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_TRUE(q1.empty());
}

// Тестирование перемещающего оператора присваивания
TEST(QueueTest, MoveAssignment) {
  s21::Queue<int> q1({1, 2, 3});
  s21::Queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_TRUE(q1.empty());
}

// Тестирование методов front и back
TEST(QueueTest, FrontBack) {
  s21::Queue<int> q({1, 2, 3});
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
  q.push(4);
  EXPECT_EQ(q.back(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 2);
}

// Тестирование метода push
TEST(QueueTest, Push) {
  s21::Queue<int> q;
  q.push(1);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 1);
  q.push(2);
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.back(), 2);
}

// Тестирование метода pop
TEST(QueueTest, Pop) {
  s21::Queue<int> q({1, 2, 3});
  q.pop();
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_TRUE(q.empty());
}

// Тестирование метода swap
TEST(QueueTest, Swap) {
  s21::Queue<int> q1({1, 2, 3});
  s21::Queue<int> q2({4, 5});
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 5);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
}  // namespace s21