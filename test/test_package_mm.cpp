//
// Created by Sebastian on 19.12.2021.
//
#include "gtest/gtest.h"
#include "storage_types.hpp"
TEST(QueueTest, FIFO) {
    Package temp1 = Package();
    auto temp1_ID = temp1.get_id();
    Package temp2 = Package();
    auto temp2_ID = temp2.get_id();
    PackageQueue que(PackageQueueType::FIFO);
    que.push(std::move(temp1));
    que.push(std::move(temp2));
    auto temp1_1(que.pop());
    auto temp2_1(que.pop());
    EXPECT_EQ(temp1_1.get_id(), temp1_ID);
    EXPECT_EQ(temp2_1.get_id(), temp2_ID);
}
TEST(QueueTest, LIFO) {
    Package temp1 = Package();
    auto temp1_ID = temp1.get_id();
    Package temp2 = Package();
    auto temp2_ID = temp2.get_id();
    PackageQueue que(PackageQueueType::LIFO);
    que.push(std::move(temp1));
    que.push(std::move(temp2));
    EXPECT_EQ(que.pop().get_id(), temp2_ID);
    EXPECT_EQ(que.pop().get_id(), temp1_ID);
}
TEST(PackageTest, ID_not_equal) {
    Package temp1 = Package();
    Package temp2 = Package();
    EXPECT_TRUE(temp1.get_id()!= temp2.get_id());
}