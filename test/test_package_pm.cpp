//
// Created by pawel on 19.12.2021.
//
#include "gtest/gtest.h"
#include "storage_types.hpp"

TEST(PackageTest, package_id_test_pm){
    std::vector<Package*> pcgs;
    pcgs.reserve(5);
    for(int i =0; i<5;i++){
        pcgs[i]=new Package();
    }
    delete pcgs[3];
    Package pcg;
    EXPECT_EQ(pcg.get_id(), 3);
    for(int i =0; i<5;i++){
        if(i!= 3)
        delete pcgs[i];
    }
}


TEST(PackageTest, package_id_eq_pm){
    Package p1 = Package(12);
    EXPECT_THROW(Package p2 = Package(12), std::invalid_argument);
}

TEST(QueueTest, queue_FIFO_test_pm){
    PackageQueue queue(PackageQueueType::FIFO);
    queue.push(Package(5));
    queue.push(Package(3));
    queue.push(Package(2));
    auto tp = queue.pop();
    EXPECT_EQ(tp.get_id(), 5);
}

TEST(QueueTest, queue_LIFO_test_pm){
    PackageQueue queue(PackageQueueType::LIFO);
    queue.push(Package(5));
    queue.push(Package(3));
    queue.push(Package(2));
    auto tp = queue.pop();
    EXPECT_EQ(tp.get_id(), 2);
}