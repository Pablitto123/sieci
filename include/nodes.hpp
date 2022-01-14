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
#include <memory>

/// definicja żeby nie było czerwono:
enum class ReceiverType{
    WORKER,
    STOREHOUSE
};


class IPackageReceiver{
public:
    virtual void receive_package(Package&&) =0;
    virtual ElementID get_id() const= 0;
    //virtual ElementID get_id() = 0;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;
    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual ReceiverType get_receiver_type() const =0 ;
//    virtual IPackageStockpile::const_iterator cbegin() = 0;
//    virtual IPackageStockpile::const_iterator cend() = 0;
//    virtual IPackageStockpile::const_iterator begin()  = 0;
//    virtual IPackageStockpile::const_iterator end()  = 0;
};

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator): pg_(pg){};
    void add_receiver( IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    preferences_t& get_preferences(){ return pref_;}

    const_iterator cbegin() const{ return pref_.cbegin(); }
    const_iterator cend() const{ return pref_.cend(); }
//    preferences_t::iterator begin() { return pref_.begin(); }
//    preferences_t::iterator end() { return pref_.end(); }
    bool empty() const {return pref_.empty();}
    const_iterator cbegin()  { return pref_.cbegin(); }
    const_iterator cend()  { return pref_.cend(); }
    const_iterator begin() const { return pref_.cbegin(); }
    const_iterator end() const { return pref_.cend(); }

    ~ReceiverPreferences() = default;
private:
    preferences_t pref_;
    ProbabilityGenerator pg_;
};

class PackageSender{
public:
    explicit PackageSender(ReceiverPreferences&& rp): receiver_preferences_(std::move(rp)){}
    PackageSender(): receiver_preferences_(ReceiverPreferences()){}
    PackageSender(PackageSender&& sender) = default;
    void send_package();
    std::optional<Package>& get_sending_buffer();
    ~PackageSender() = default;
    ReceiverPreferences receiver_preferences_;
protected:
    void push_package(Package&& p);
    std::optional<Package> buffer_;
};

class Ramp: public PackageSender {
public:
    Ramp(PackageSender &&sender, ElementID id, TimeOffset di) : PackageSender(std::move(sender)), id_(id), di_(di) {};
    Ramp(ElementID id, TimeOffset di) : PackageSender(), id_(id), di_(di) {};

    Ramp(Ramp&&) = default;
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval(){ return di_; };
    ElementID get_id() const{ return id_; };
    ElementID get_id() { return id_; };
    ~Ramp() = default;
private:
    unsigned long long start_time_ = UINTMAX_MAX;
    ElementID id_;
    TimeOffset di_;
};

class Worker: public PackageSender, public IPackageReceiver{
public:
    Worker(PackageSender &&sender, ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q):PackageSender(std::move(sender)), id_(id), pd_(pd), q_(std::move(q)){}; //??
    Worker( ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q):PackageSender(), id_(id), pd_(pd), q_(std::move(q)){}; //??
    IPackageStockpile::const_iterator cbegin() const override {return q_.get()->cbegin();};
    IPackageStockpile::const_iterator cend() const override {return q_.get()->cend();};
    IPackageStockpile::iterator begin() {return q_.get()->begin();};
    IPackageStockpile::iterator end() {return q_.get()->end();};
    IPackageStockpile::const_iterator begin() const override {return q_.get()->cbegin();};
    IPackageStockpile::const_iterator end() const override {return q_.get()->cend();};
    void do_work(Time t);
    Worker(Worker&&) =default;
    [[nodiscard]] Time get_package_processing_start_time() const{return start_;};
    [[nodiscard]] TimeOffset get_processing_duration() const{return pd_;}
    ElementID get_id() const override{return id_;}
    ReceiverType get_receiver_type() const override{return ReceiverType::WORKER;}
    void receive_package(Package &&p) override{q_->push(std::move(p));}

private:
    std::optional<Package> buffer_processing_;
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    Time start_ = 0;

};

class Storehouse: public IPackageReceiver{
public:
    explicit Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)):id_(id), d_(std::move(d)){}
    ElementID get_id() const override{return id_;}

    ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;}
    ReceiverType get_receiver_type() {return ReceiverType::STOREHOUSE;}
    void receive_package(Package &&p) override{d_->push(std::move(p));}
    IPackageStockpile::const_iterator cbegin() const override {return d_.get()->cbegin();};
    IPackageStockpile::const_iterator cend() const override {return d_.get()->cbegin();};
    IPackageStockpile::const_iterator cbegin()  {return d_.get()->cbegin();};
    IPackageStockpile::const_iterator cend()  {return d_.get()->cbegin();};
    IPackageStockpile::iterator begin() {return d_.get()->begin();};
    IPackageStockpile::iterator end() {return d_.get()->end();};
    IPackageStockpile::const_iterator begin() const override {return d_.get()->cbegin();};
    IPackageStockpile::const_iterator end() const override {return d_.get()->cbegin();};
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};


#endif //SIECI_NODES_HPP
