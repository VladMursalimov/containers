#include <gtest/gtest.h>
#include "vector.h"
#include <stdexcept>

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
