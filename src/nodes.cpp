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
}
