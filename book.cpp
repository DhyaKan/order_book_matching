#include "book.h"
#include  <cassert>
#include <stdexcept>

using namespace std;

int EVENT_POS = 0;
int TIME_POS = 1;
int ORDER_ID_POS = 2;
int SYMBOL_POS_POS = 3;
int SIDE_POS = 4;
int ORDER_TYPE_POS = 5;
int PRICE_POS = 6;
int QTY_POS = 7;
int MOD_PRICE_POS = 4;
int MOD_QTY_POS = 5;

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

static uint64_t convertPrice (std::string price) {
    double priceConverted = std::stod(price);
    return (static_cast<uint64_t>(priceConverted*10000));
}

static shared_ptr<Order> constructOrder (const std::vector<std::string>& token) {
    shared_ptr<Order> order = make_shared<Order>();
    order->transactionTime = std::stol(token[TIME_POS]);
    order->orderId = token[ORDER_ID_POS];
    string sideStr = token[SIDE_POS];
    if (sideStr == "BUY") order->side = Side::BUY;
    else order->side = Side::SELL;
    string orderType = token[ORDER_TYPE_POS];
    if (orderType == "LIMIT") {
        order->orderType = OrderType::LIMIT;
    }
    else if (orderType == "MARKET") {
        order->orderType = OrderType::MARKET;
    }
    else {
        order->orderType = OrderType::NONE;
    }
    order->price = convertPrice(token[6]);
    order->quantity = std::stoi(token[7]);
    return order;
}

int OrderBook::handleOrder (const std::vector<std::string>& inputString) {
    try {
        if (inputString.empty()) {
            throw::runtime_error("Input is empty");
        }
        std::string event = inputString[0];
        Event eventInput = getEventFromInput(event);

        switch (eventInput){
            case Event::ADD:
                addOrder (inputString);   
                break;
            case Event::MODIFY:
                modifyOrder (inputString);  
                break;
            case Event::CANCEL:
                canceOrder (inputString);  
                break;
            default:
                cout << "NONE" << endl;
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught Error : " << e.what() << endl;
        return 0;
    }
    return 1;
}

void OrderBook::addOrder (const std::vector<std::string>& inputString) {
    assert (inputString.size() == 8);
    const string symbol = inputString[SYMBOL_POS_POS];
    auto iterToSymbolBook = symbolBook.find(symbol);
    if ( iterToSymbolBook != symbolBook.end()) {
        const shared_ptr<Order> order = constructOrder(inputString);
        iterToSymbolBook->second->addPriceLevel(order);     
        iterToSymbolBook->second->print(symbol);  
    }
    else {
        auto [iterToSymbolBook, ifInserted] = symbolBook.try_emplace (symbol, std::make_shared<priorityBook>());
        if (ifInserted) {
            const shared_ptr<Order> order = constructOrder(inputString);
            iterToSymbolBook->second->addPriceLevel(order);
            iterToSymbolBook->second->print(symbol);
        }
    }
    
}

void OrderBook::modifyOrder (const std::vector<std::string>& inputString) {
    const string symbol = inputString[SYMBOL_POS_POS];
    const string orderId = inputString[ORDER_ID_POS];
    auto iterToSymbolBook = symbolBook.find(symbol);
    assert (iterToSymbolBook != symbolBook.end());
    const uint64_t newPrice = convertPrice(inputString[MOD_PRICE_POS]);
    const int newSize = std::stoi(inputString [MOD_QTY_POS]); 
    const int newTransactionTime = std::stol(inputString[TIME_POS]);
    iterToSymbolBook->second->updatePriceLevel(orderId, newPrice, newSize, newTransactionTime);
    iterToSymbolBook->second->print(symbol);
}

void OrderBook::canceOrder (const std::vector<std::string>& inputString) {
    const string symbol = inputString[SYMBOL_POS_POS];
    const string orderId = inputString[ORDER_ID_POS];
    auto iterToSymbolBook = symbolBook.find(symbol);
    assert (iterToSymbolBook != symbolBook.end());
    const uint64_t newPrice = 0;
    const int newSize = 0; 
    const int newTransactionTime = std::stol(inputString[TIME_POS]);
    iterToSymbolBook->second->updatePriceLevel(orderId, newPrice, newSize, newTransactionTime);
    iterToSymbolBook->second->print(symbol);
}

void OrderBook::fillOrder (const std::vector<std::string>& inputString) {
    //to be filled
}



