//
// Created by Sebastian on 16.12.2021.
//

#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include "storage_types.hpp"
#include <set>


Package PackageQueue::pop() {
    if (!empty()) {
        Package buff;
        switch (queue_type_) {
            case PackageQueueType::FIFO:
                buff = std::move(products_lst_.front());
                products_lst_.pop_front();
                return buff;
            case PackageQueueType::LIFO:
                buff = std::move(products_lst_.front());
                products_lst_.pop_front();
                break;
            default:
                break;
        }
        return buff;
    } else {
        //TODO: throw an exception
    }
}

void PackageQueue::push(Package &&pack) {
    switch (queue_type_) {
        case PackageQueueType::FIFO:
            products_lst_.emplace_back(std::move(pack));
            break;
        case PackageQueueType::LIFO:
            products_lst_.emplace_front(std::move(pack));
            break;
        default:
            break;
    }
}


