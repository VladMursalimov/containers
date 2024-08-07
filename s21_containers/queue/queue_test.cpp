#include <gtest/gtest.h>
#include "queue.h"

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