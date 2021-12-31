//
// Created by Sebastian on 16.12.2021.
//

#include <algorithm>
#include <iostream>
#include "storage_types.hpp"



Package PackageQueue::pop() {
    Package* buff;
    if (!empty()) {
        switch (queue_type_) {
            case PackageQueueType::FIFO:
                buff = &products_lst_.front();
                products_lst_.pop_front();
                break;
            case PackageQueueType::LIFO:
                buff = &products_lst_.front();
                products_lst_.pop_front();
                break;
            default:
                throw std::invalid_argument("no such a queue type");
        }
        return std::move(*buff);
    } else {
        //TODO: throw an exception
        throw std::invalid_argument("queue is empty");
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


