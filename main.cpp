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
for(int i=0;i<10;i++){
    auto pcg = Package();
    q_up->push(std::move(pcg));
}
auto pgg = q_up->pop();
std::cout << &pgg;
}
