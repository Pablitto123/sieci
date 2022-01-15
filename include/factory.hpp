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
public:
    using const_iterator = typename std::list<T>::const_iterator;
    using iterator = typename std::list<T>::iterator;
    const_iterator cbegin() const { return collection_.cbegin(); }

    const_iterator cend() const { return collection_.cend(); }

    const_iterator cbegin() { return collection_.cbegin(); }

    const_iterator cend()  { return collection_.cend(); }

    iterator begin()  { return collection_.begin(); }

    iterator end()  { return collection_.end(); }

    iterator find_by_id(ElementID id);

    const_iterator find_by_id(ElementID id) const;
    void add(T&& node){collection_.push_back(std::move(node));};
    void remove_by_id(ElementID id){collection_.erase(find_by_id(id));};

};


template<> class NodeCollection<Ramp>{
private:
    std::list<Ramp> collection_;
public:
    using const_iterator = typename std::list<Ramp>::const_iterator;
    using iterator = typename std::list<Ramp>::iterator;
    const_iterator cbegin() { return collection_.cbegin(); }

    const_iterator cbegin() const { return collection_.cbegin(); }

    const_iterator cend()  { return collection_.cend(); }

    const_iterator cend() const { return collection_.cend(); }

    iterator begin()  { return collection_.begin(); }

    iterator end()  { return collection_.end(); }

    iterator find_by_id(ElementID id);

    const_iterator find_by_id(ElementID id) const;
    void add(Ramp&& node){collection_.push_back(std::move(node));};
    void remove_by_id(ElementID id){collection_.erase(find_by_id(id));};

};

template<> class NodeCollection<Worker>{
private:
    std::list<Worker> collection_;
public:
    using const_iterator = typename std::list<Worker>::const_iterator;
    using iterator = typename std::list<Worker>::iterator;
    const_iterator cbegin() { return collection_.cbegin(); }

    const_iterator cend()  { return collection_.cend(); }

    const_iterator cbegin() const { return collection_.cbegin(); }

    const_iterator cend() const { return collection_.cend(); }

    iterator begin()  { return collection_.begin(); }

    iterator end()  { return collection_.end(); }

    iterator find_by_id(ElementID id);
    const_iterator find_by_id(ElementID id) const;
    void add(Worker&& node){collection_.push_back(std::move(node));};
    void remove_by_id(ElementID id){collection_.erase(find_by_id(id));};
};

template<> class NodeCollection<Storehouse>{
private:
    std::list<Storehouse> collection_;
public:
    using const_iterator = typename std::list<Storehouse>::const_iterator;
    using iterator = typename std::list<Storehouse>::iterator;
    const_iterator cbegin() { return collection_.cbegin(); }

    const_iterator cbegin() const { return collection_.cbegin(); }

    const_iterator cend()  { return collection_.cend(); }

    const_iterator cend() const { return collection_.cend(); }

    iterator begin()  { return collection_.begin(); }

    iterator end()  { return collection_.end(); }

    iterator find_by_id(ElementID id);
    const_iterator find_by_id(ElementID id) const;
    void add(Storehouse&& node){collection_.push_back(std::move(node));};
    void remove_by_id(ElementID id){collection_.erase(find_by_id(id));};

};



class Factory{
private:
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;

public:
    Factory()=default;
    void add_ramp(Ramp&& ramp){ramps_.add(std::move(ramp));};
    void remove_ramp(ElementID id){ramps_.remove_by_id(id);};/// ok brak nadawcow
    std::list<Ramp>::iterator find_ramp_by_id(ElementID id){return ramps_.find_by_id(id);};
    [[nodiscard]] std::list<Ramp>::const_iterator find_ramp_by_id(ElementID id) const{return ramps_.find_by_id(id);};
    [[nodiscard]] std::list<Ramp>::const_iterator ramp_cbegin() const { return ramps_.cbegin(); };
    [[nodiscard]] std::list<Ramp>::const_iterator ramp_cend() const { return ramps_.cend(); };
    std::list<Ramp>::const_iterator ramp_cbegin() { return ramps_.cbegin(); };
    std::list<Ramp>::const_iterator ramp_cend() { return ramps_.cend(); };



    void add_worker(Worker&& worker){workers_.add(std::move(worker));};
    //void remove_worker(ElementID id){workers_.remove_by_id(id);};
    void remove_worker(ElementID id);
    std::list<Worker>::iterator find_worker_by_id(ElementID id){return workers_.find_by_id(id);};
    [[nodiscard]] std::list<Worker>::const_iterator find_worker_by_id(ElementID id) const{return workers_.find_by_id(id);};
    [[nodiscard]] std::list<Worker>::const_iterator worker_cbegin() const { return workers_.cbegin(); };
    [[nodiscard]] std::list<Worker>::const_iterator worker_cend() const { return workers_.cend(); };
    std::list<Worker>::const_iterator worker_cbegin() { return workers_.cbegin(); };
    std::list<Worker>::const_iterator worker_cend() { return workers_.cend(); };



    void add_Storehouse(Storehouse&& storage){storehouses_.add(std::move(storage));};
    void remove_storehouse(ElementID id);
    std::list<Storehouse>::iterator find_Storehouse_by_id(ElementID id){return storehouses_.find_by_id(id);};
    [[nodiscard]] std::list<Storehouse>::const_iterator find_Storehouse_by_id(ElementID id) const{return storehouses_.find_by_id(id);};
    [[nodiscard]] std::list<Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_.cbegin(); };
    [[nodiscard]] std::list<Storehouse>::const_iterator storehouse_cend() const { return storehouses_.cend(); };
    std::list<Storehouse>::const_iterator storehouse_cbegin() { return storehouses_.cbegin(); };
    std::list<Storehouse>::const_iterator storehouse_cend() { return storehouses_.cend(); };

    bool is_consistent();
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
private:
    template<typename T>
    void remove_receiver(NodeCollection<T>& lst,ElementID id);
};
Factory load_factory_structure(std::istream& is);
void save_factory_structure( Factory& factory, std::ostream& os);

#endif //SIECI_FACTORY_HPP
