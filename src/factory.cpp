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

bool Factory::is_consistent() {
    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++){
            it2-> first->get_receiver_type()
        }
    };
};