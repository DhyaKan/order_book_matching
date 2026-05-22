#include <iostream>
#include "order.h"

int main() {
    Order demo = Order();
    std::cout << (demo.orderType == OrderType::LIMIT ? "LIMIT" : "MARKET") << "\n";
    return 0;
}