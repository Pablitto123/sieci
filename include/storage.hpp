//
// Created by Sebastian on 16.12.2021.
//
#ifndef SIECI_STORAGE_HPP
#define SIECI_STORAGE_HPP

#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>

class Package{
private:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID Id_;
public:
    Package();
    //Package(ElementID Id ){Id_=Id;}
    //Package(Package&&)
    //operator=(Package&&) : Package&
    ElementID get_id(){return Id_;};
    ~Package(){delete &Id_; /*delete &assigned_IDs; delete &freed_IDs;*/ };

    };


class PackageQueue{};

class IPackageQueue{};

class IPackageStockpile{};

class PackageQueueType{};



#endif //SIECI_STORAGE_HPP
