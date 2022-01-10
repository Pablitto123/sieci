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
    lst.front().changeID();
    lst.pop_front();

    return true;
}
Package only_move(Package&& move_){
    return std::move(move_);
}
Package PackageQueue::pop() {
    if (empty()) {
        throw std::invalid_argument("queue is empty");
    }
    //ElementID i = products_lst_.front().get_id();
    //Destructor j(i);
    return tan(pop_front(products_lst_),only_move(std::move(products_lst_.front())));

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

}

void PackageQueue::push(Package &&pack) {
    switch (queue_type_) {
        case PackageQueueType::FIFO:
            products_lst_.push_back(std::move(pack));
            break;
        case PackageQueueType::LIFO:
            products_lst_.push_front(std::move(pack));
            break;
        default:
            break;
    }
}


