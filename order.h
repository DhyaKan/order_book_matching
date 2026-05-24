#include <iostream>
#include <string>
#include <ctime>
#include "enums_collection.h"

using str = std::string;

struct Order {
    str orderId;
    std::time_t transactionTime = -1;
    Side side = Side::NONE;
    OrderType orderType = OrderType::NONE;  
    uint64_t price = 0;
    int quantity = 0;
    bool active = true;

    void printOrder() {
        std::cout << orderId << "\t"
                    << transactionTime << "\t"
                   // << side << "\t"
                 //   << orderType << "\t"
                    << price << "\t"
                    << quantity << std::endl;
    }
};