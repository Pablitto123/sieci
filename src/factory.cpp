//
// Created by Sebastian on 07.01.2022.
//
#include <stack>
#include <functional>
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

//template<typename T>
//typename NodeCollection<T>::iterator NodeCollection<T>::find_by_id(ElementID id) {
//    return begin();
//}


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
    bool pom = false;
    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++) {
            if(it2->first->get_receiver_type() == ReceiverType::STOREHOUSE){
                pom = true;
            };
        };
        storage_access.push_back(pom);
        pom = false;
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


    std::function<bool(std::vector<std::vector<bool>>&,std::size_t,std::vector<bool>)> dfs_algorithm_function = [](std::vector<std::vector<bool>>& graph,std::size_t index,std::vector<bool> access){
        if(graph.empty()){
            return true;
        }
        std::vector<bool> is_checked;
        for(auto i : graph){
            is_checked.push_back(false);
        }
        std::stack<int> stack;
        stack.push(index);
        if(access[index]){return true;};

        int top = stack.top();
        while(!stack.empty()){
            top = stack.top();
            stack.pop();
            is_checked[top] = true;
            for(auto i : graph[top]){
                if(!is_checked[i]){
                    if(access[i]){return true;};
                    stack.push(i);
                }
            }
        }
        return false;

    };

    for(auto it: ramp_id){
        if(!dfs_algorithm_function(workers_connection, find_index(it,map_workers),storage_access)){return false;};

    };
    return true;

};

