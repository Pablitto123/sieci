//
// Created by Sebastian on 16.12.2021.
//

#include <algorithm>
#include <iostream>
#include "storage_types.hpp"
//class Destructor{
//public:
//    Destructor(ElementID i): i_(i){};
//    ElementID i_;
//    ~Destructor(){
//        Package i(SIZE_MAX - 1);
//        i.Add_Id(i_);
//        int t = 0;
//        t++;
//    }
//};
Package tan(bool,Package&& move_){
    return std::move(move_);
}
bool pop_front(std::list<Package>& lst){
    //lst.front().changeID();
    lst.pop_front();

    return true;
}
Package only_move(Package&& move_){
    return std::move(move_);
}
Package PackageQueue::pop() {
    Package* buff;
    if (!empty()) {
        switch (queue_type_) {
            case PackageQueueType::LIFO:
                buff = &products_lst_.front();
                products_lst_.pop_front();
                break;
            case PackageQueueType::FIFO:
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
        case PackageQueueType::LIFO:
            products_lst_.emplace_back(std::move(pack));
            break;
        case PackageQueueType::FIFO:
            products_lst_.emplace_front(std::move(pack));
            break;
        default:
            break;
    }
}



