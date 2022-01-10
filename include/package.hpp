//
// Created by nikos on 18.12.2021.
//

#ifndef SIECI_PACKAGE_HPP
#define SIECI_PACKAGE_HPP

#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>

class Package{
public:
    static void flush_ids(){ assigned_IDs = std::set<ElementID>();freed_IDs = std::set<ElementID>();};
    Package();
    explicit Package(ElementID Id );
    Package(Package&& package) = default;
    //Package(Package&& package) :Id_(package.Id_){};
    Package& operator=(Package&&) noexcept {return *this;}
    ElementID get_id() const {return Id_;};
    //void destroy();//nie używamy po tym package bo się program wyjebie.(funkcja calluje destruktor)
    //void changeID(){ Id_ = SIZE_MAX;}
    ~Package();
    //static void Add_Id(ElementID idd);

private:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID Id_;

};
#endif //SIECI_PACKAGE_HPP
