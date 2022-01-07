//
// Created by Sebastian on 07.01.2022.
//

#ifndef SIECI_FACTORY_HPP
#define SIECI_FACTORY_HPP


template<typename T>

class NodeCollection{
private:
    std::vector<T> collection_;
public:
    add(node: Node&&);
    remove_by_id(id: ElementID);
    find_by_id(id: ElementID);
    find_by_id(id: ElementID);
    //iteratory
};


class Factory{
private:
    Colletion NodeCollection
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
