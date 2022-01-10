//
// Created by nikos on 10.01.2022.
//
#include "gtest/gtest.h"
#include "nodes.hpp"
#include <functional>
#include "factory.hpp"
TEST(NodeColectionTest, node_worker_test) {
    std::function<double()> f = [](){ return 1;};
    std::function<double()> f2 = [](){ return 0.45;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp_2 = ReceiverPreferences(f2);

    /// worker
    ReceiverPreferences rp1 = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    ReceiverPreferences rp3 = ReceiverPreferences(f);
    ReceiverPreferences rp4 = ReceiverPreferences(f);
    PackageSender sender_worker1 = PackageSender(std::move(rp1));
    PackageSender sender_worker2 = PackageSender(std::move(rp2));
    PackageSender sender_worker3 = PackageSender(std::move(rp3));
    PackageSender sender_worker4 = PackageSender(std::move(rp4));
    Worker worker1(std::move(sender_worker1), 1,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker2(std::move(sender_worker2), 2,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker3(std::move(sender_worker3), 3,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker4(std::move(sender_worker4), 4,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    ///
    NodeCollection<Worker> n;
    n.add(std::move(worker1));
    n.add(std::move(worker2));
    n.add(std::move(worker3));
    n.add(std::move(worker4));
    ///

    EXPECT_EQ(n.find_by_id(3)->get_id(),3);
    ///remove by id
    n.remove_by_id(3);
    EXPECT_EQ(n.find_by_id(3),n.end());
}
TEST(NodeColectionTest, node_ramp_test) {
    std::function<double()> f = [](){ return 1;};
    std::function<double()> f2 = [](){ return 0.45;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp_2 = ReceiverPreferences(f2);

    /// worker
    ReceiverPreferences rp1 = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    ReceiverPreferences rp3 = ReceiverPreferences(f);
    ReceiverPreferences rp4 = ReceiverPreferences(f);
    PackageSender sender_worker1 = PackageSender(std::move(rp1));
    PackageSender sender_worker2 = PackageSender(std::move(rp2));
    PackageSender sender_worker3 = PackageSender(std::move(rp3));
    PackageSender sender_worker4 = PackageSender(std::move(rp4));
    Ramp worker1(std::move(sender_worker1), 1,6);
    Ramp worker2(std::move(sender_worker2), 2,6);
    Ramp worker3(std::move(sender_worker3), 3,6);
    Ramp worker4(std::move(sender_worker4), 4,6);
    ///
    NodeCollection<Ramp> n;
    n.add(std::move(worker1));
    n.add(std::move(worker2));
    n.add(std::move(worker3));
    n.add(std::move(worker4));
    ///

    EXPECT_EQ(n.find_by_id(3)->get_id(),3);
    ///remove by id
    n.remove_by_id(3);
    EXPECT_EQ(n.find_by_id(3),n.end());
}
TEST(NodeColectionTest, node_storage_test) {

    /// worker

    Storehouse worker1( 1,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Storehouse worker2( 2,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Storehouse worker3( 3,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Storehouse worker4( 4,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    ///
    NodeCollection<Storehouse> n;
    n.add(std::move(worker1));
    n.add(std::move(worker2));
    n.add(std::move(worker3));
    n.add(std::move(worker4));
    ///

    EXPECT_EQ(n.find_by_id(3)->get_id(),3);
    ///remove by id
    n.remove_by_id(3);
    EXPECT_EQ(n.find_by_id(3),n.end());
}
TEST(FabricTest, node_fabric_test) {
    std::function<double()> f = [](){ return 1;};
    std::function<double()> f2 = [](){ return 0.45;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp_2 = ReceiverPreferences(f2);

    /// worker
    ReceiverPreferences rp1 = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    ReceiverPreferences rp3 = ReceiverPreferences(f);
    ReceiverPreferences rp4 = ReceiverPreferences(f);
    PackageSender sender_worker1 = PackageSender(std::move(rp1));
    PackageSender sender_worker2 = PackageSender(std::move(rp2));
    PackageSender sender_worker3 = PackageSender(std::move(rp3));
    PackageSender sender_worker4 = PackageSender(std::move(rp4));
    Worker worker1(std::move(sender_worker1), 1,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker2(std::move(sender_worker2), 2,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker3(std::move(sender_worker3), 3,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker4(std::move(sender_worker4), 4,6,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    ///
    NodeCollection<Worker> n;
    n.add(std::move(worker1));
    n.add(std::move(worker2));
    n.add(std::move(worker3));
    n.add(std::move(worker4));
    ///

    EXPECT_EQ(n.find_by_id(3)->get_id(),3);
    ///remove by id
    n.remove_by_id(3);
    EXPECT_EQ(n.find_by_id(3),n.end());
}