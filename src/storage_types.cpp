//
// Created by Sebastian on 16.12.2021.
//

#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include "storage_types.hpp"
#include <set>

PackageQueue::PackageQueue(PackageQueueType type){
    queue_type_ = type;
}

Package PackageQueue::pop() {}

void PackageQueue::push(Package &pack) {}


