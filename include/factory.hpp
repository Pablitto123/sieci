//
// Created by Sebastian on 07.01.2022.
//

#ifndef SIECI_FACTORY_HPP
#define SIECI_FACTORY_HPP

#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>
#include "factory.hpp"

template<typename T>

class NodeCollection{
private:
    std::vector<T> collection_;
    using const_iterator = std::vector<T>::const_iterator;
    using iterator =  std::vector<T>::iterator;
public:
    const_iterator cbegin() { return collection_.cbegin(); }

    const_iterator cend()  { return collection_.cbegin(); }

    iterator begin()  { return collection_.begin(); }

    iterator end()  { return collection_.end(); }

    iterator find_by_id(ElementID id){
        collection_.find
    };
//    void add(Node&& node);
    void remove_by_id(ElementID id);
//    const_iterator find_by_id(ElementID id);

};


class Factory{
private:
    Colletion NodeCollection;
public:
    add_ramp(Ramp&&);
    remove_ramp(id: ElementID);
    find_ramp_by_id(id: ElementID);
    find_ramp_by_id(id: ElementID);
    ramp_cbegin();
    ramp_cend();
    add_worker(Worker&&);
    remove_worker(id: ElementID);
    find_worker_by_id(id: ElementID);
    find_worker_by_id(id: ElementID);
    worker_cbegin();
    worker_cend();
    add_Storehouse(Storehouse&&);
    remove_Storehouse(id: ElementID);
    find_Storehouse_by_id(id: ElementID);
    find_Storehouse_by_id(id: ElementID);
    Storehouse_cbegin();
    Storehouse_cend();
    remove_receiver(collection: NodeCollection<Node>&, id: ElementID);

    is_consistent();
    do_deliveries(Time);
    do_package_passing();
    do_work(Time);


};


#endif //SIECI_FACTORY_HPP
