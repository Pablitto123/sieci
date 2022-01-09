//
// Created by nikos on 09.01.2022.
//
#include "gtest/gtest.h"
#include "nodes.hpp"
#include <functional>

TEST(PackageSenderTest, buffor_test) {
    Package temp1 = Package();
    std::function<double()> f = [](){ return 1;};
    ReceiverPreferences rp = ReceiverPreferences(f);
    PackageSender sender = PackageSender(std::move(rp));
    EXPECT_FALSE(sender.get_sending_buffer());
    Ramp ramp = Ramp(std::move(sender), 12,12);
    ramp.deliver_goods(0);
    sender.get_sending_buffer();



    Package temp2 = Package();
    //auto temp2_ID = temp2.get_id();
    PackageQueue que(PackageQueueType::FIFO);
    que.push(std::move(temp1));
    que.push(std::move(temp2));

    //EXPECT_EQ(que.pop().get_id(), temp2_ID);
}