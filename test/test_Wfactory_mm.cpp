//
// Created by nikos on 09.01.2022.
//
#include "gtest/gtest.h"
#include "nodes.hpp"
#include <functional>
/**/
TEST(ZPackageSenderTest, buffor_test) {

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
    //std::optional<Package>& tt2(worker.get_sending_buffer());
    //EXPECT_TRUE(bool(tt2));
}