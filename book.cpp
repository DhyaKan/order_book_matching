#include "book.h"

using namespace std;

static Event getEventFromInput (const std::string& eventInput) {
    if (eventInput == "ADD") {
        return (Event::ADD);
    }
    else if (eventInput == "MODIFY") {
        return (Event::MODIFY);
    }
    else if (eventInput == "CANCEL") {
        return (Event::CANCEL);
    }
    else {
        return (Event::NONE);
    }
}

void OrderBook::handleOrder (const std::vector<std::string>& inputString) {
    std::string event = inputString[0];
    Event eventInput = getEventFromInput(event);
    //std::shared_ptr<Order> order = std::make_shared<Order>();

    switch (eventInput){
        case Event::ADD:
            addOrder (inputString);   
        case Event::MODIFY:
            modifyOrder (inputString);  
        case Event::CANCEL:
            canceOrder (inputString);  
        default:
            std::cout << "No event";

    }
}

void OrderBook::addOrder (const std::vector<std::string>& inputString) {
    //to be filled
    std::cout << "Event is ADD " ;
}

void OrderBook::modifyOrder (const std::vector<std::string>& inputString) {
    //to be filled
    std::cout << "Event is modify " ;
}

void OrderBook::canceOrder (const std::vector<std::string>& inputString) {
     //to be filled
    std::cout << "Event is cancel " ;
}

void OrderBook::fillOrder (const std::vector<std::string>& inputString) {
    //to be filled
    std::cout << "Event is fill " ;
}



/*
    order->transactionTime = std::stol(token[1]);
    order->orderId = token[2];
    order->symbol = token[3];
    order->side = token[4];
    string orderType = token[5];
    if (orderType == "LIMIT") {
        order->orderType = OrderType::LIMIT;
    }
    else if (orderType == "MARKET") {
        order->orderType = OrderType::MARKET;
    }
    else {
        order->orderType = OrderType::NONE;
    }
    order->price = static_cast<uint64_t>(std::stod(token[6])*10000);
    order->quantity = std::stoi(token[7]);
            vector token = parseLine(line);
        for (const auto& toke : token) {
            std::cout << toke << endl;
        }
        std::string event = token[0];
        std::shared_ptr<Order> order = std::make_shared<Order>();
        order->transactionTime = std::stol(token[1]);
        order->orderId = token[2];
        order->symbol = token[3];
        order->side = token[4];
        string orderType = token[5];
        if (orderType == "LIMIT") {
            order->orderType = OrderType::LIMIT;
        }
        else if (orderType == "MARKET") {
            order->orderType = OrderType::MARKET;
        }
        else {
            order->orderType = OrderType::NONE;
        }
        order->price = static_cast<uint64_t>(std::stod(token[6])*10000);
        order->quantity = std::stoi(token[7]);


*/