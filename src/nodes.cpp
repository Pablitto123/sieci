//
// Created by nikos on 07.01.2022.
//
#include "nodes.hpp"

IPackageReceiver* ReceiverPreferences::choose_receiver(){

    double centyl = pg_();
    double dystrybution = 0;
    for(auto i : pref_){
        dystrybution += i.second;
        if(centyl<dystrybution){
            return i.first;
        }
    }
    /// niepotrzebne !!!
    return (*pref_.begin()).first;
}
void ReceiverPreferences::add_receiver( IPackageReceiver* r){
    pref_.insert(std::pair<IPackageReceiver*, double>(r,1)); /// kaj prawdopodobieństwo? >:/
    /// zapewnienie niezmiennika
    double sum = 0;
    for(auto i : pref_){
        sum += i.second;
    }
    for(auto i : pref_){
        i.second = i.second/sum;
    }
}
void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    pref_.erase(r);
    /// zapewnienie niezmiennika
    double sum = 0;
    for(auto i : pref_){
        sum += i.second;
    }
    for(auto i : pref_){
        i.second = i.second/sum;
    }
}

std::optional<Package>& PackageSender::get_sending_buffer(){///to się spierdoli
    return buffor_;
}

void PackageSender::push_package(Package&& p){
    if (!buffor_){
        buffor_ = std::move(p);
    }
}

void PackageSender::send_package(){
    ///receiver_preferences_.choose_receiver().receive_package(std::move(buffor_));/// <--- def metody potrzebóje
    buffor_.reset();
}
void Ramp::deliver_goods(Time t){
    if (t%di_) {
        Package tt = Package();
        push_package(std::move(tt));
    }
}