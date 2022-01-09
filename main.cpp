#include <iostream>
#include "storage_types.hpp"
#include "factory.hpp"
#include <types.hpp>
#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>
#include <set>
#include <list>

int main() {
Factory fct;

auto q_up =std::make_unique<PackageQueue>(PackageQueueType::FIFO);
Package pcg = Package(3);
q_up->push(std::move(pcg));
Worker wr(PackageSender(), 32, 2, std::move(q_up));
fct.add_worker(std::move(wr));
fct.add_ramp(Ramp(PackageSender(),32,2));
std::cout <<fct.ramp_cbegin()->get_id() <<std::endl;
std::cout <<fct.is_consistent();

}
