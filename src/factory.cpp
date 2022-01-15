//
// Created by Sebastian on 07.01.2022.
//
#include <stack>
#include <functional>
#include "nodes.hpp"
#include "factory.hpp"
#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <types.hpp>
#include <istream>
#include <string>
#include <sstream>

std::list<Ramp>::iterator NodeCollection<Ramp>::find_by_id(ElementID id) {
    for(auto it = begin(); it!= end(); it++){
        if(it->get_id() == id)return it;
    }
    return end();

}

std::list<Ramp>::const_iterator NodeCollection<Ramp>::find_by_id(ElementID id) const{
    for(auto it = cbegin(); it!= cend(); it++){
        if(it->get_id() == id)return it;
    }
    return cend();
}

std::list<Worker>::iterator NodeCollection<Worker>::find_by_id(ElementID id) {
    for(auto it = begin(); it!= end(); it++){
        if(it->get_id() == id)return it;
    }
    return end();

}

std::list<Worker>::const_iterator NodeCollection<Worker>::find_by_id(ElementID id) const{
    for(auto it = cbegin(); it!= cend(); it++){
        if(it->get_id() == id)return it;
    }
    return cend();
}

std::list<Storehouse>::iterator NodeCollection<Storehouse>::find_by_id(ElementID id) {
    for(auto it = begin(); it!= end(); it++){
        if(it->get_id() == id)return it;
    }
    return end();

}

std::list<Storehouse>::const_iterator NodeCollection<Storehouse>::find_by_id(ElementID id) const{
    for(auto it = cbegin(); it!= cend(); it++){
        if(it->get_id() == id)return it;
    }
    return cend();
}

std::size_t find_index(ElementID id, std::vector<ElementID>& map_work){
    for(std::size_t i=0;i < std::size(map_work);i++) {
        if (map_work[i] == id) {
            return i;
        }
    }
    return 0;
}
enum class kolor_wezla{NIEODWIEDZONY, ODWIEDZONY, ZWERYFIKOWANY};

bool czy_nadawca_posiada_osiagalny_magazyn(PackageSender* nadawca,std::map<PackageSender*, kolor_wezla>& kolor) {
    if(kolor[nadawca] == kolor_wezla::ZWERYFIKOWANY){
        return true;
    }
    kolor[nadawca] = kolor_wezla::ODWIEDZONY;
    if (nadawca->receiver_preferences_.empty()){
        throw std::invalid_argument("empty output");
    }
    bool czy_nadawca_ma_choc_jednego_odbiorce_innego_niz_siebie_samego = false;

    for(auto it2 = nadawca->receiver_preferences_.begin(); it2 != nadawca->receiver_preferences_.end(); it2 ++){
        if(it2->first->get_receiver_type() == ReceiverType::STOREHOUSE){
            czy_nadawca_ma_choc_jednego_odbiorce_innego_niz_siebie_samego = true;
        }else{
            IPackageReceiver* receiver_ptr = it2->first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(sendrecv_ptr == nadawca){
                continue;
            }
            czy_nadawca_ma_choc_jednego_odbiorce_innego_niz_siebie_samego = true;
            if(kolor[sendrecv_ptr]==kolor_wezla::NIEODWIEDZONY){
                czy_nadawca_posiada_osiagalny_magazyn(sendrecv_ptr,kolor);
            }
        }

    }
    kolor[nadawca] = kolor_wezla::ZWERYFIKOWANY;
    if(czy_nadawca_ma_choc_jednego_odbiorce_innego_niz_siebie_samego){
        return true;
    }else{
        throw std::invalid_argument("empty output");
    }
}

bool Factory::is_consistent() {
    std::map<PackageSender*, kolor_wezla> kolor;

    for(auto it = ramps_.begin(); it != ramps_.end(); it ++){
        kolor.insert(std::pair<PackageSender*, kolor_wezla>(&*it,kolor_wezla::NIEODWIEDZONY));
    }
    for(auto it = workers_.begin(); it != workers_.end(); it ++){
        kolor.insert(std::pair<PackageSender*, kolor_wezla>(&*it,kolor_wezla::NIEODWIEDZONY));
    }
    try{
        for(auto it = ramps_.begin(); it != ramps_.end(); it ++){
            czy_nadawca_posiada_osiagalny_magazyn(&*it,kolor);
        }
    }catch(...){
        return false;
    }
    return true;
}

void Factory::do_deliveries(Time t)  {
    for(auto it = ramps_.begin(); it != ramps_.end(); it ++) {
        it -> deliver_goods(t);
    };
}
void Factory::do_work(Time t) {
    for(auto it = workers_.begin(); it != workers_.end(); it ++){
      it -> do_work(t);
    };
}
void Factory::do_package_passing() {
   for(auto it = ramps_.begin(); it != ramps_.end(); it ++) {

       it -> send_package() ;
   };

  for(auto it = workers_.begin(); it != workers_.end(); it ++){

      it -> send_package() ;
  };
}


void Factory::remove_worker(ElementID id) {
    if(workers_.find_by_id(id) != workers_.end()){
        Worker* usuwany = &*workers_.find_by_id(id);
        for(auto it = workers_.begin(); it != workers_.end(); it ++){
            it->receiver_preferences_.remove_receiver(usuwany);
        };
        for(auto it = ramps_.begin(); it != ramps_.end(); it ++){
            it->receiver_preferences_.remove_receiver(usuwany);
        };

    }

}
void Factory::remove_storehouse(ElementID id){
    if(storehouses_.find_by_id(id) != storehouses_.end()){
        Storehouse* usuwany = &*storehouses_.find_by_id(id);
        for(auto it = workers_.begin(); it != workers_.end(); it ++){
            it->receiver_preferences_.remove_receiver(usuwany);
        };
        for(auto it = ramps_.begin(); it != ramps_.end(); it ++){
            it->receiver_preferences_.remove_receiver(usuwany);
        };

    }

}
template<typename T>
void Factory::remove_receiver(NodeCollection<T>& lst,ElementID id){
    if(lst.find_by_id(id) != lst.end()){
        T* usuwany = &*lst.find_by_id(id);
        for(auto it = workers_.begin(); it != workers_.end(); it ++){
            it->receiver_preferences_.remove_receiver(usuwany);
        };
        for(auto it = ramps_.begin(); it != ramps_.end(); it ++){
            it->receiver_preferences_.remove_receiver(usuwany);
        };

    }
}
enum class ElementType{
    RAMP,WORKER,STOREHOUSE,LINK
};
struct ParsedLineData{
    ElementType element_type;
    std::map<std::string, std::string> parameters;
};

std::vector<std::string> split(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

ParsedLineData parse_line(std::string line) {
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);
    char delimiter = ' ';

    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    std::map<std::string, std::string> tag_map;
    std::vector<std::string> key_val;
    for(std::size_t i =1; i< std::size(tokens) ; i++){
        key_val = split(tokens[i],'=');
        tag_map.insert(std::pair<std::string,std::string>(key_val[0],key_val[1]));
    }
    ParsedLineData p;
    p.parameters = std::move(tag_map);
    if(tokens[0] == "LOADING_RAMP"){
        p.element_type = ElementType::RAMP;
    }else if(tokens[0] == "WORKER"){
        p.element_type = ElementType::WORKER;
    }else if(tokens[0] == "STOREHOUSE"){
        p.element_type = ElementType::STOREHOUSE;
    }else if(tokens[0] == "LINK"){
        p.element_type = ElementType::LINK;
    }

    return p;
}

Factory load_factory_structure(std::istream& is){
    Factory factory;
    std::string line;
    ParsedLineData p;
    std::list<Ramp>::iterator ramp;
    std::list<Worker>::iterator worker_in;
    std::list<Storehouse>::iterator store;
    std::list<Worker>::iterator worker_out;
    std::vector<std::string> key_val;
    while (std::getline(is, line)) {
        if(*line.data() != ';' and line != ""){
            p = parse_line(line);
            switch(p.element_type){
                case ElementType::RAMP:{
                    factory.add_ramp(Ramp(std::stoi(p.parameters["id"]),std::stoi(p.parameters["delivery-interval"])));
                    break;
                }
                case ElementType::WORKER:{
                    if(p.parameters["queue-type"] == "LIFO"){
                        factory.add_worker(Worker(std::stoi(p.parameters["id"]),std::stoi(p.parameters["processing-time"]),std::make_unique<PackageQueue>(PackageQueueType::LIFO)));
                    }else{
                        factory.add_worker(Worker(std::stoi(p.parameters["id"]),std::stoi(p.parameters["processing-time"]),std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
                    }
                    break;
                }
                case ElementType::STOREHOUSE:{
                    factory.add_Storehouse(Storehouse(std::stoi(p.parameters["id"])));
                    break;
                }
                case ElementType::LINK:{

                    key_val = split(p.parameters["src"],'-');
                    if(key_val[0] == "ramp"){
                        ramp = factory.find_ramp_by_id(std::stoi(key_val[1]));

                        key_val = split(p.parameters["dest"],'-');
                        if(key_val[0] == "store"){
                            store = factory.find_Storehouse_by_id(std::stoi(key_val[1]));
                            ramp->receiver_preferences_.add_receiver(&*store);
                        }else if(key_val[0] == "worker"){
                            worker_out = factory.find_worker_by_id(std::stoi(key_val[1]));
                            ramp->receiver_preferences_.add_receiver(&*worker_out);
                        }
                    }else if(key_val[0] == "worker"){
                        worker_in = factory.find_worker_by_id(std::stoi(key_val[1]));
                        key_val = split(p.parameters["dest"],'-');
                        if(key_val[0] == "store"){
                            store = factory.find_Storehouse_by_id(std::stoi(key_val[1]));
                            worker_in->receiver_preferences_.add_receiver(&*store);
                        }else if(key_val[0] == "worker"){
                            worker_out = factory.find_worker_by_id(std::stoi(key_val[1]));
                            worker_in->receiver_preferences_.add_receiver(&*worker_out);
                        }
                    }


                    break;
                }
            }
        }
    }

    return factory;

}
//void save_factory_structure( Factory& factory, std::ostream& os);