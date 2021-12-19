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
#include <list>
#include "package.hpp"

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile {
public:
    using const_iterator = std::list<Package>::const_iterator;
    using iterator = std::list<Package>::const_iterator;

    virtual void push(Package &&pack) = 0;

    virtual const_iterator cbegin() = 0;

    virtual const_iterator cend() = 0;

    virtual iterator begin() = 0;

    virtual iterator end() = 0;

    virtual std::size_t size() = 0;

    virtual bool empty() = 0;

    virtual ~IPackageStockpile() = default;

private:

};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() const = 0;

    virtual ~IPackageQueue() = default;
};

class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType type) : queue_type_(type) {};

    const_iterator cbegin() { return products_lst_.cbegin(); }

    const_iterator cend() { return products_lst_.cbegin(); }

    iterator begin() { return products_lst_.begin(); }

    iterator end() { return products_lst_.end(); }

    std::size_t size() { return std::size_t(std::distance(cbegin(), cend())); };

    void push(Package &&pack);

    Package pop();

    bool empty() { return size() == 0; }

    PackageQueueType get_queue_type() const { return queue_type_; }

    ~PackageQueue() = default;

private:

    PackageQueueType queue_type_;

    std::list<Package> products_lst_;

};


#endif //SIECI_STORAGE_TYPES_HPP
