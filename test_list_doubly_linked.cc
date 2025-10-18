#include <gtest/gtest.h>
#include "list_doubly_linked.h"

class ListTest : public ::testing::Test {
protected:
    ListDoublyLinked<int> list;
};

// Test initialization
TEST_F(ListTest, InitialSizeIsZero) {
    ASSERT_EQ(list.Size(), 0);
}

// Test insertion at the beginning
TEST_F(ListTest, InsertAtBeginning) {
    list.Insert(10, 0);
    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Get(0), 10);
}

// Test insertion at multiple positions
TEST_F(ListTest, InsertMultipleElements) {
    list.Insert(5, 0);
    list.Insert(15, 1);
    list.Insert(10, 1);
    
    ASSERT_EQ(list.Size(), 3);
    ASSERT_EQ(list.Get(0), 5);
    ASSERT_EQ(list.Get(1), 10);
    ASSERT_EQ(list.Get(2), 15);
}

// Test insertion at the end
TEST_F(ListTest, InsertAtEnd) {
    list.Insert(1, 0);
    list.Insert(2, 1);
    list.Insert(3, 2);
    
    ASSERT_EQ(list.Size(), 3);
    ASSERT_EQ(list.Get(2), 3);
}

// Test insertion in the middle
TEST_F(ListTest, InsertInMiddle) {
    list.Insert(1, 0);
    list.Insert(3, 1);
    list.Insert(2, 1);
    
    ASSERT_EQ(list.Get(0), 1);
    ASSERT_EQ(list.Get(1), 2);
    ASSERT_EQ(list.Get(2), 3);
}

// Test Get method
TEST_F(ListTest, GetValidPositions) {
    list.Insert(100, 0);
    list.Insert(200, 1);
    list.Insert(300, 2);
    
    ASSERT_EQ(list.Get(0), 100);
    ASSERT_EQ(list.Get(1), 200);
    ASSERT_EQ(list.Get(2), 300);
}

// Test Get out of bounds
TEST_F(ListTest, GetOutOfBounds) {
    list.Insert(42, 0);
    ASSERT_THROW(list.Get(1), std::out_of_range);
    ASSERT_THROW(list.Get(10), std::out_of_range);
}

// Test Find method
TEST_F(ListTest, FindExistingElement) {
    list.Insert(5, 0);
    list.Insert(10, 1);
    list.Insert(15, 2);
    
    ASSERT_EQ(list.Find(5), 0);
    ASSERT_EQ(list.Find(10), 1);
    ASSERT_EQ(list.Find(15), 2);
}

// Test Find non-existent element
TEST_F(ListTest, FindNonExistentElement) {
    list.Insert(5, 0);
    list.Insert(10, 1);
    ASSERT_EQ(list.Find(99), -1);
}

// Test Find on empty list
TEST_F(ListTest, FindInEmptyList) {
    ASSERT_EQ(list.Find(42), -1);
}

// Test Remove from head
TEST_F(ListTest, RemoveFromHead) {
    list.Insert(1, 0);
    list.Insert(2, 1);
    list.Insert(3, 2);
    
    list.Remove(0);
    
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Get(0), 2);
    ASSERT_EQ(list.Get(1), 3);
}

// Test Remove from end
TEST_F(ListTest, RemoveFromEnd) {
    list.Insert(1, 0);
    list.Insert(2, 1);
    list.Insert(3, 2);
    
    list.Remove(2);
    
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Get(0), 1);
    ASSERT_EQ(list.Get(1), 2);
}

// Test Remove from middle
TEST_F(ListTest, RemoveFromMiddle) {
    list.Insert(1, 0);
    list.Insert(2, 1);
    list.Insert(3, 2);
    
    list.Remove(1);
    
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Get(0), 1);
    ASSERT_EQ(list.Get(1), 3);
}

// Test Remove only element
TEST_F(ListTest, RemoveSingleElement) {
    list.Insert(42, 0);
    list.Remove(0);
    
    ASSERT_EQ(list.Size(), 0);
}

// Test Remove out of bounds
TEST_F(ListTest, RemoveOutOfBounds) {
    list.Insert(1, 0);
    ASSERT_THROW(list.Remove(1), std::out_of_range);
    ASSERT_THROW(list.Remove(5), std::out_of_range);
}

// Test complex sequence of operations
TEST_F(ListTest, ComplexOperations) {
    list.Insert(10, 0);
    list.Insert(20, 1);
    list.Insert(30, 2);
    list.Insert(15, 1);
    
    ASSERT_EQ(list.Size(), 4);
    ASSERT_EQ(list.Get(1), 15);
    
    list.Remove(1);
    ASSERT_EQ(list.Size(), 3);
    ASSERT_EQ(list.Get(1), 20);
    
    ASSERT_EQ(list.Find(30), 2);
}

// Test with string data type
TEST(ListStringTest, StringOperations) {
    ListDoublyLinked<std::string> stringList;
    
    stringList.Insert("hello", 0);
    stringList.Insert("world", 1);
    stringList.Insert("foo", 1);
    
    ASSERT_EQ(stringList.Size(), 3);
    ASSERT_EQ(stringList.Get(0), "hello");
    ASSERT_EQ(stringList.Get(1), "foo");
    ASSERT_EQ(stringList.Get(2), "world");
}

// Test Insert out of bounds
TEST_F(ListTest, InsertOutOfBounds) {
    list.Insert(1, 0);
    ASSERT_THROW(list.Insert(2, 5), std::out_of_range);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
