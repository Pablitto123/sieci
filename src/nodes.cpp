//
// Created by nikos on 07.01.2022.
//
#include "nodes.hpp"

IPackageReceiver* ReceiverPreferences::choose_receiver(){

    double centyl = pg_();
    double dystrybution = 0;
    for(auto i : pref_){
        dystrybution += i.second;
        if(centyl<=dystrybution){
            return i.first;
        }
    }
    /// niepotrzebne !!!
    return (*pref_.begin()).first;
}
void ReceiverPreferences::add_receiver( IPackageReceiver* r){
    pref_.insert(std::pair<IPackageReceiver*, double>(r,1)); /// kaj prawdopodobieństwo? >:/
    /// zapewnienie niezmiennika
    for(auto i = pref_.begin(); i!=pref_.end(); ++i){
        i->second = 1.0/double(std::size(pref_));
    }
}
void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    pref_.erase(r);
    /// zapewnienie niezmiennika
    for(auto i = pref_.begin(); i!=pref_.end(); ++i){
        i->second = 1.0/double(std::size(pref_));
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
    if(bool(buffer_)){
        receiver_preferences_.choose_receiver()->receive_package(std::move(buffer_.value()));/// <--- def metody potrzebóje
//        buffer_->changeID();
        buffer_.reset();
    }
}

void Ramp::deliver_goods(Time t){///TODO: problem z poprawnym ID produktów
    if(start_time_ == UINTMAX_MAX) start_time_ = t;
    if ((t-start_time_)%di_ == 0) {
        if (!buffer_){
            Package tt = Package();
            push_package(std::move(tt));
//            tt.changeID();
        }
    }
}

void Worker::do_work(Time t) {
    if(!q_->empty() and !buffer_processing_){
        buffer_processing_ = q_->pop();
        start_ = t;
    }
    if(t - start_+1>= pd_ and bool(buffer_processing_)){

        push_package(std::move(buffer_processing_.value()));
//        buffer_processing_->changeID();
        buffer_processing_.reset();
        start_ = 0;
    }
}
