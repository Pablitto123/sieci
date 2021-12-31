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
private:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID Id_;
public:
    Package();
    explicit Package(ElementID Id );
    Package(Package&& package) noexcept :Id_(package.Id_){};
    Package& operator=(Package&&){return *this;}
    ElementID get_id() const {return Id_;};
    ~Package();

};
#endif //SIECI_PACKAGE_HPP
