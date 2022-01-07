//
// Created by nikos on 07.01.2022.
//

#ifndef SIECI_NODES_HPP
#define SIECI_NODES_HPP

#include "types.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"
#include <map>
#include <optional>

/// definicja żeby nie było czerwono:
class IPackageReceiver{
};

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    ReceiverPreferences(ProbabilityGenerator pg): pg_(pg){};
    void add_receiver( IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    preferences_t& get_preferences(){ return pref_;}
    const_iterator cbegin(){ return pref_.cbegin(); }
    const_iterator cend(){ return pref_.cend(); }
    preferences_t::iterator begin(){ return pref_.begin(); }
    preferences_t::iterator end(){ return pref_.end(); }
private:
    preferences_t pref_;
    ProbabilityGenerator pg_;
};

class PackageSender{
public:
    PackageSender(PackageSender&& sender) : receiver_preferences_(sender.receiver_preferences_){};
    void send_package();
    std::optional<Package>& get_sending_buffer();
    ~PackageSender() = default;
protected:
    void push_package(Package&&);
private:
    ReceiverPreferences receiver_preferences_;

};

class Ramp: public PackageSender {
public:
    Ramp(PackageSender &&sender, ElementID id, TimeOffset di) : PackageSender(std::move(sender)), id_(id), di_(di) {};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval(){ return di_; };
    ElementID get_id(){ return id_; };
    ~Ramp() = default;
private:
    ElementID id_;
    TimeOffset di_;
};


#endif //SIECI_NODES_HPP
