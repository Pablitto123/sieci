//
// Created by Sebastian on 16.12.2021.
//

#include <algorithm>
#include <iostream>
#include "storage_types.hpp"



Package PackageQueue::pop() {



    if (!empty()) {
        Package temp(std::move(products_lst_.front()));
        products_lst_.pop_front();
        return std::move(temp);
//        switch (queue_type_) {
//            case PackageQueueType::FIFO:
//                buff = &products_lst_.front();
//                return std::move(products_lst_.front());
//                temp = std::move(products_lst_.front());
//                return std::move(temp);
//                //buff = &products_lst_.front();
//                //Package temp2();
//                //products_lst_.pop_front();
//
//            case PackageQueueType::LIFO:
//                buff = &products_lst_.front();
//                products_lst_.pop_front();
//                return temp;
//            default:
//                throw std::invalid_argument("no such a queue type");
//        }
//        //return std::move(*buff);
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


