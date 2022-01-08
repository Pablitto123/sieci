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
    for(auto it = ramp_cbegin(); it != ramp_cend(); it ++){
        for(auto it2=it->receiver_preferences_.begin();it2 < it->receiver_preferences_.end();++it2)
    }
};