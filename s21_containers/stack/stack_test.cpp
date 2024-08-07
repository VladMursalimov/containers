#include <gtest/gtest.h>
#include "stack.h"

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}