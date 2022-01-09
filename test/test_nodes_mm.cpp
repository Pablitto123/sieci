//
// Created by nikos on 09.01.2022.
//
#include "gtest/gtest.h"
#include "nodes.hpp"
#include <functional>
/**/
TEST(PackageSenderTest, buffor_and_ramp_test) {

    std::function<double()> f = [](){ return 1;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    PackageSender sender_ramp = PackageSender(std::move(rp));
    PackageSender sender_worker = PackageSender(std::move(rp2));
    EXPECT_FALSE(sender_ramp.get_sending_buffer());
    EXPECT_FALSE(sender_worker.get_sending_buffer());
    Ramp ramp(std::move(sender_ramp), 12,12);
    Worker worker(std::move(sender_worker), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    ramp.receiver_preferences_.add_receiver(&worker);
    ramp.deliver_goods(0);
    std::optional<Package>& tt(ramp.get_sending_buffer());
    EXPECT_TRUE(bool(tt));
    ramp.send_package();
    EXPECT_FALSE(sender_ramp.get_sending_buffer());
    EXPECT_FALSE(sender_ramp.get_sending_buffer());
    worker.do_work(0);
    worker.do_work(12);
    std::optional<Package>& tt2(worker.get_sending_buffer());
    EXPECT_TRUE(bool(tt2));
}

TEST(ReceiverPreferencesTest, add_test) {
    std::function<double()> f = [](){ return 1;};
    std::function<double()> f2 = [](){ return 0.45;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp_2 = ReceiverPreferences(f2);
    ReceiverPreferences rp1 = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    ReceiverPreferences rp3 = ReceiverPreferences(f);
    ReceiverPreferences rp4 = ReceiverPreferences(f);
    PackageSender sender_worker1 = PackageSender(std::move(rp1));
    PackageSender sender_worker2 = PackageSender(std::move(rp2));
    PackageSender sender_worker3 = PackageSender(std::move(rp3));
    PackageSender sender_worker4 = PackageSender(std::move(rp4));
    Worker worker1(std::move(sender_worker1), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker2(std::move(sender_worker2), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker3(std::move(sender_worker3), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Worker worker4(std::move(sender_worker4), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    rp.add_receiver(&worker1);
    rp.add_receiver(&worker2);
    rp.add_receiver(&worker3);
    rp.add_receiver(&worker4);
    rp_2.add_receiver(&worker1);
    rp_2.add_receiver(&worker2);
    rp_2.add_receiver(&worker3);
    rp_2.add_receiver(&worker4);
    double sum = 0;
    for(auto i : rp.get_preferences()){
        sum+=i.second;
    }
    EXPECT_EQ(sum,1);
    sum = 0;
    rp.remove_receiver(&worker1);
    for(auto i : rp.get_preferences()){
        sum+=i.second;
    }
    EXPECT_EQ(sum,1);
    EXPECT_EQ(rp.choose_receiver()->get_id(),worker4.get_id());
    EXPECT_EQ(rp_2.choose_receiver()->get_id(),worker3.get_id());
}
TEST(WorkerTest, worker_test) {
    std::function<double()> f = [](){ return 1;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    PackageSender sender_ramp = PackageSender(std::move(rp));
    PackageSender sender_worker = PackageSender(std::move(rp2));
    Ramp ramp(std::move(sender_ramp), 12,12);
    Worker worker(std::move(sender_worker), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    ramp.receiver_preferences_.add_receiver(&worker);
    ramp.deliver_goods(0);
    std::optional<Package>& tt(ramp.get_sending_buffer());
    EXPECT_TRUE(bool(tt));
    worker.do_work(0);
    worker.do_work(1);
    ramp.send_package();
    EXPECT_FALSE(sender_ramp.get_sending_buffer());
    EXPECT_FALSE(sender_ramp.get_sending_buffer());
    worker.do_work(0);
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    worker.do_work(1);
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    worker.do_work(3);
    ramp.deliver_goods(0);
    ramp.send_package();
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    worker.do_work(5);
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    worker.do_work(7);
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    worker.do_work(11);
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    worker.do_work(12);
    EXPECT_TRUE(bool(worker.get_sending_buffer()));
    /// Worker odbierający
    ReceiverPreferences rp4 = ReceiverPreferences(f);
    PackageSender sender_worker4 = PackageSender(std::move(rp4));
    Worker worker4(std::move(sender_worker4), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    worker.receiver_preferences_.add_receiver(&worker4);
    worker.send_package();
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
}

TEST(StorageTest, storage_test) {
    std::function<double()> f = [](){ return 1;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    ReceiverPreferences rp2 = ReceiverPreferences(f);
    PackageSender sender_ramp = PackageSender(std::move(rp));
    PackageSender sender_worker = PackageSender(std::move(rp2));
    Ramp ramp(std::move(sender_ramp), 12,12);
    Worker worker(std::move(sender_worker), 12,12,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    ramp.receiver_preferences_.add_receiver(&worker);
    ramp.deliver_goods(0);
    worker.do_work(0);
    worker.do_work(1);
    ramp.send_package();
    worker.do_work(0);
    worker.do_work(1);
    worker.do_work(3);
    ramp.deliver_goods(0);
    worker.do_work(12);
    /// Storehouse odbierający
    Storehouse store(13,std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    worker.receiver_preferences_.add_receiver(&store);
    worker.send_package();
    EXPECT_FALSE(bool(worker.get_sending_buffer()));
    /// z debugera widać że ok :)  (brak dostępu do ipackagestockpile)
}