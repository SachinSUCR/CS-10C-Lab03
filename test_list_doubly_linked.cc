#include <gtest/gtest.h>
#include "list_doubly_linked.h"

TEST(List, BasicOperations) {
    ListDoublyLinked<int> list;
    ASSERT_EQ(list.Size(), 0);

    list.Insert(10, 0); // [10]
    list.Insert(20, 1); // [10, 20]
    list.Insert(15, 1); // [10, 15, 20]
    ASSERT_EQ(list.Size(), 3);
    ASSERT_EQ(list.Get(0), 10);
    ASSERT_EQ(list.Get(1), 15);
    ASSERT_EQ(list.Get(2), 20);

    list.Remove(1); // [10, 20]
    ASSERT_EQ(list.Size(), 2);
    ASSERT_EQ(list.Find(20), 1);
    ASSERT_EQ(list.Find(15), -1);
}
