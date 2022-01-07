//
// Created by nikos on 07.01.2022.
//

#ifndef SIECI_NODES_HPP
#define SIECI_NODES_HPP

#include "types.hpp"

class ReceiverPreferences{
public:


private:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
};
class PackageSender{
public:

private:

};

class Ramp(public: PackageSender){
public:
    Ramp(ElementID id)
private:

}


#endif //SIECI_NODES_HPP
