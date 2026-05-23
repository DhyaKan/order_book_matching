#include <iostream>
#include <string>
#include <ctime>
#include "enums_collection.h"

using str = std::string;

struct Order {
    str orderId {};
    std::time_t transactionTime = -1;
    str symbol {};
    str side {};
    OrderType orderType = OrderType::NONE;  
    uint64_t price = 0;
    int quantity = 0;
};