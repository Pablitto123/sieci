//
// Created by nikos on 18.12.2021.
//
#include <algorithm>
#include <iostream>
#include "package.hpp"
#include <set>

std::set<ElementID> Package::freed_IDs = {};
std::set<ElementID> Package::assigned_IDs = {};
Package::Package() {
    if(freed_IDs.empty() && assigned_IDs.empty()) {
        Id_ = 0;
        assigned_IDs.insert(Id_);
    }
    else if(!freed_IDs.empty()){
        Id_ = *std::min_element(freed_IDs.cbegin(),freed_IDs.cend());
        freed_IDs.erase(Id_);
        assigned_IDs.insert(Id_);
    }
    else if(freed_IDs.empty() && !assigned_IDs.empty()){
        Id_ = (*std::max_element(assigned_IDs.cbegin(), assigned_IDs.cend()) + 1);
        assigned_IDs.insert(Id_);
    }
}

Package::Package(ElementID Id) {
    if(!(assigned_IDs.find(Id) == assigned_IDs.end())){
        throw std::invalid_argument("Id is already taken");
    }
    Id_ = Id;
    freed_IDs.erase(Id_);
    assigned_IDs.insert(Id_);
}
void Package::Add_Id(ElementID idd){
    freed_IDs.erase(idd);
    assigned_IDs.insert(idd);
}

void Package::destroy() {
    freed_IDs.insert(Id_);
    assigned_IDs.erase(Id_);
    delete this;
}
Package::~Package() {
    if(Id_ != SIZE_MAX){
        freed_IDs.insert(Id_);
        assigned_IDs.erase(Id_);
    }
}