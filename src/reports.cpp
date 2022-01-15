//
// Created by nikos on 15.01.2022.
//
#include "reports.hpp"
void generate_structure_report(const Factory& f, std::ostream& os){
    os<<"== LOADING RAMP ==\n";
    for(auto i = f.ramp_cbegin();i!= f.ramp_cend();i++){
        os<<"LOADING RAMP #"<<std::to_string(i->get_id())<<"\n  Delivery interval: "<<std::to_string(i->get_delivery_interval())<<"\n  Receivers:";
        for(auto it = i->receiver_preferences_.cbegin(); it != i->receiver_preferences_.cend();it++){

        }
    }
}
