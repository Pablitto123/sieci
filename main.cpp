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
PackageQueue q = PackageQueue(PackageQueueType::FIFO);
std::unique_ptr<IPackageQueue> q_up = std::make_unique<PackageQueue>(q);

Worker wr(PackageSender(), 0, 2, std::move(q_up));
fct.add_worker(std::move(wr));

}
