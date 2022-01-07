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
    std::cout << "Hello, World!" << std::endl;

    NodeCollection<int> proba;

    auto it = proba.cbegin();

    std::cout << std::string(typeid(it)) ;

    return 0;

}
