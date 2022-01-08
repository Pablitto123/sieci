//
// Created by Sebastian on 07.01.2022.
//
#include "nodes.hpp"
#include "factory.hpp"
#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <types.hpp>


std::size_t find_index(ElementID id, std::vector<ElementID>& map_work){
    std::size_t size;
    for(std::size_t i=0;i < std::size(map_work);i++) {
        if (map_work[i] == id) {
            return size;
        }
    }
    return 0;
};

bool Factory::is_consistent() {

    std::vector<bool> storage_access;
    std::vector<ElementID> ramp_id;
    std::vector<ElementID> map_workers;

    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
        map_workers.push_back(it->get_id());

    };
    std::vector<std::vector<bool>> workers_connection;

    for(auto it = ramp_cbegin(); it != ramp_cend(); it ++){
        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++) {
            if (it2->first->get_receiver_type() == ReceiverType::WORKER) {
                ramp_id.push_back(it2->first->get_id());
            };
        };
    };
    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
        if(it->get_receiver_type() == ReceiverType::STOREHOUSE){
            storage_access.push_back(true);

        }else{
            storage_access.push_back(false);
        };
    };

    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
        workers_connection.emplace_back(std::vector<bool>(std::size(map_workers)));
    };


    for(auto it = worker_cbegin(); it != worker_cend(); it ++){

        std::size_t index = find_index(it->get_id(),map_workers);

        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++){
            if (it2->first->get_receiver_type() == ReceiverType::WORKER) {
                workers_connection[index][it2->first->get_id()] = true;
            };
        };
    };




};
