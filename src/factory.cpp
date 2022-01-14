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


//    std::vector<bool> storage_access;
//    std::vector<ElementID> ramp_id;
//    std::vector<ElementID> map_workers;
//
//    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
//        map_workers.push_back(it->get_id());
//
//    };
//    std::vector<std::vector<bool>> workers_connection;
//
//    for(auto it = ramp_cbegin(); it != ramp_cend(); it ++){
//        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++) {
//            if (it2->first->get_receiver_type() == ReceiverType::WORKER) {
//                ramp_id.push_back(it2->first->get_id());
//            };
//        };
//    };
//    bool pom = false;
//    for(auto it = workers_.begin(); it != workers_.end(); it ++){
//        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++) {
//            if(it2->first->get_receiver_type() == ReceiverType::STOREHOUSE){
//                pom = true;
//            };
//        };
//        storage_access.push_back(pom);
//        pom = false;
//    };
//
//    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
//        workers_connection.emplace_back(std::vector<bool>(std::size(map_workers)));
//    };
//
//
//    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
//
//        std::size_t index = find_index(it->get_id(),map_workers);
//
//        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cend();it2++){
//            if (it2->first->get_receiver_type() == ReceiverType::WORKER) {
//                workers_connection[it2->first->get_id()][index] = true;
//            };
//        };
//    };
//
//    for(auto it = ramp_cbegin(); it != ramp_cend(); it ++){
//        if(it -> receiver_preferences_.empty()) {
//            throw std::invalid_argument("Ramp without reciver");
//        };
//
//    };
//    bool is_any_not_itself = false;
//    for(auto it = worker_cbegin(); it != worker_cend(); it ++){
//        if(it -> receiver_preferences_.empty()) {
//            throw std::invalid_argument("Worker without reciver");
//        };
//        is_any_not_itself = false;
//        for(auto it2 = it->receiver_preferences_.cbegin(); it2 != it->receiver_preferences_.cbegin(); it2 ++){
//            if(it2->first->get_id()!=it->get_id()){
//                is_any_not_itself = true;
//            }
//        }
//        if(!is_any_not_itself){
//            throw std::invalid_argument("Worker without other reciver than itself");
//        }
//
//    }
//
//
//
//
//    std::function<void(std::vector<std::vector<bool>>&,std::size_t,std::vector<bool>&)> dfs_algorithm_function = [](std::vector<std::vector<bool>>& graph,std::size_t index, std::vector<bool>& visited){
//
//        std::vector<bool> is_checked;
//        for(auto i : graph){
//            is_checked.push_back(false);
//        }
//        std::stack<int> stack;
//        stack.push(index);
//
//
//        int top = stack.top();
//        while(!stack.empty()){
//            top = stack.top();
//            stack.pop();
//            is_checked[top] = true;
//            for(auto i : graph[top]){
//                if(!is_checked[i]){
//                    stack.push(i);
//                }
//            }
//        }
//        for(std::size_t i =0 ;std::size(is_checked) < i; i++){
//            if(is_checked[i]){visited[i] = true;}
//        };
//    };
//
//
//    std::vector<bool> if_ever_visited;
//    for(std::size_t i = 0; i < std::size(storage_access);i++){
//        if_ever_visited.push_back(false);
//    }
//
//    for(std::size_t i = 0; i < std::size(storage_access);i++){
//        /////
//        std::vector<bool> is_checked;
//        for(auto i : workers_connection){
//            is_checked.push_back(false);
//        }
//        std::stack<int> stack;
//        stack.push(i);
//        int top = stack.top();
//        while(!stack.empty()){
//            top = stack.top();
//            stack.pop();
//            is_checked[top] = true;
//            for(auto i : workers_connection[top]){
//                if(!is_checked[i]){
//                    stack.push(i);
//                }
//            }
//        }
//        for(std::size_t i =0 ;std::size(is_checked) < i; i++){
//            if(is_checked[i]){visited[i] = true;}
//        };
//        /////
//        //dfs_algorithm_function(workers_connection, i, if_ever_visited);
//    };
//    for(std::size_t i = 0; i < std::size(if_ever_visited);i++){
//        if(!if_ever_visited[i]){throw std::invalid_argument("Inconsistent network");}
//
//    };
//
//    for(auto it = ramp_cbegin(); it != ramp_cend(); it ++) {
//        if(std::distance(it->receiver_preferences_.cbegin(),it->receiver_preferences_.cend()) == 0){return  false;};
//    };
//    return true;
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
void Factory::remove_Storehouse(ElementID id){
    if(Storehouses_.find_by_id(id) != Storehouses_.end()){
        Storehouse* usuwany = &*Storehouses_.find_by_id(id);
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