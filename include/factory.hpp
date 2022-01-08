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
#include <list>
#include "nodes.hpp"

template<typename T>

class NodeCollection{
private:
    std::list<T> collection_;
    using const_iterator = typename std::list<T>::const_iterator;
    using iterator = typename std::list<T>::iterator;
public:
    const_iterator cbegin() const { return collection_.cbegin(); }

    const_iterator cend()  const { return collection_.cbegin(); }

    iterator begin()  { return collection_.begin(); }

    iterator end()  { return collection_.end(); }

    iterator find_by_id(ElementID id) {std::find(begin(),end(),id);};
    const_iterator find_by_id(ElementID id) const{std::find(cbegin(),cend(),id);};
    void add(T&& node){collection_.push_back(std::move(node));};
    void remove_by_id(ElementID id){collection_.erase(find_by_id(id));};

};

class Factory{
private:
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> Storehouses_;

public:
    void add_ramp(Ramp&& ramp){ramps_.add(std::move(ramp));};
    void remove_ramp(ElementID id){ramps_.remove_by_id(id);};
    std::list<Ramp>::iterator find_ramp_by_id(ElementID id){return ramps_.find_by_id(id);};
//    std::list<Ramp>::const_iterator find_ramp_by_id(ElementID id){return ramps_.find_by_id(id);};
    std::list<Ramp>::const_iterator ramp_cbegin()const { return ramps_.cbegin(); };
    std::list<Ramp>::const_iterator ramp_cend() const { return ramps_.cend(); };

    void add_worker(Worker&& worker){workers_.add(std::move(worker));};
    void remove_worker(ElementID id){workers_.remove_by_id(id);};
    std::list<Worker>::iterator find_worker_by_id(ElementID id){return workers_.find_by_id(id);};
//    std::list<Worker>::const_iterator find_worker_by_id(ElementID id){return workers_.find_by_id(id);};
    std::list<Worker>::const_iterator worker_cbegin()const { return workers_.cbegin(); };
    std::list<Worker>::const_iterator worker_cend()const { return workers_.cend(); };

    void add_Storehouse(Storehouse&& storage){Storehouses_.add(std::move(storage));};
    void remove_Storehouse(ElementID id){Storehouses_.remove_by_id(id);};
    std::list<Storehouse>::iterator find_Storehouse_by_id(ElementID id){return Storehouses_.find_by_id(id);};
//    std::list<Storehouse>::const_iterator find_worker_by_id(ElementID id){return Storehouses_.find_by_id(id);};
    std::list<Storehouse>::const_iterator Storehouse_cbegin() const{ return Storehouses_.cbegin(); };
    std::list<Storehouse>::const_iterator Storehouse_cend() const{ return Storehouses_.cend(); };

    bool is_consistent ();
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);


};


#endif //SIECI_FACTORY_HPP
