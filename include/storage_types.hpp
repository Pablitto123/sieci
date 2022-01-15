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
#include <memory>
#include "package.hpp"

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile {
public:
    using const_iterator = std::list<Package>::const_iterator;
    using iterator = std::list<Package>::const_iterator;

    virtual void push(Package &&pack) = 0;
    virtual const_iterator cbegin() const = 0;

    virtual const_iterator cend() const = 0;

    virtual const_iterator cbegin() = 0;

    virtual const_iterator cend() = 0;



    virtual iterator begin() = 0;

    virtual iterator end() = 0;

    virtual unsigned int size() = 0;

    virtual bool empty() = 0;

    virtual ~IPackageStockpile() = default;

private:

};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() const = 0;

    ~IPackageQueue() override = default;
};

class PackageQueue : public IPackageQueue{
public:
    explicit PackageQueue(PackageQueueType type) : queue_type_(type) {};

    const_iterator cbegin() const override { return products_lst_.cbegin(); }

    const_iterator cend() const override { return products_lst_.cend(); }

    const_iterator cbegin() override { return products_lst_.cbegin(); }

    const_iterator cend() override { return products_lst_.cend(); }

    iterator begin() override { return products_lst_.begin(); }

    iterator end() override { return products_lst_.end(); }

    unsigned int size() override { return std::distance(begin(), end()); };

    void push(Package &&pack) override;

    Package pop() override;

    bool empty() override { return size() == 0; }

    PackageQueueType get_queue_type() const override { return queue_type_; }

    ~PackageQueue() override = default;

private:

    PackageQueueType queue_type_;

    std::list<Package> products_lst_;

};


#endif //SIECI_STORAGE_TYPES_HPP
