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
    for(auto i = begin(); i!=end(); ++i){
        i->second = (i->second)/sum;
    }
}
void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    pref_.erase(r);
    /// zapewnienie niezmiennika
    double sum = 0;
    for(auto i : pref_){
        sum += i.second;
    }
    for(auto i = begin(); i!=end(); ++i){
        i->second = (i->second)/sum;
    }
}

std::optional<Package>& PackageSender::get_sending_buffer(){///to się spierdoli
    return buffer_;
}

void PackageSender::push_package(Package&& p){
    if (!buffer_){
        buffer_ = std::move(p);
    }
}

void PackageSender::send_package(){
    receiver_preferences_.choose_receiver()->receive_package(std::move(*buffer_));/// <--- def metody potrzebóje
    buffer_.reset();
}

void Ramp::deliver_goods(Time t){
    if (t%di_ == 0) {
        Package tt = Package();
        push_package(std::move(tt));
    }
}

void Worker::do_work(Time t) {
    if(start_ == 0 and !q_->empty()){
        if (!buffer_processing_){
            buffer_processing_ = q_->pop();
            start_ = t;
        }
    }
    else if(t - start_ == pd_){
        push_package(std::move(*buffer_processing_));
        buffer_processing_.reset();
        start_ = 0;
    }
}
