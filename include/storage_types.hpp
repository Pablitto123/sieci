//
// Created by Sebastian on 16.12.2021.
//
#ifndef SIECI_STORAGE_TYPES_HPP
#define SIECI_STORAGE_TYPES_HPP

#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>

class PackageQueue{};

class IPackageQueue{};

class IPackageStockpile{};

enum class PackageQueueType{
    FIFO,LIFO
};



#endif //SIECI_STORAGE_TYPES_HPP
