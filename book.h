#include "order.h"
#include <unordered_map>
#include <deque>
#include <memory>
#include <map>
#include <iomanip>
using namespace std;
struct TopOfBook {
    using tobShared = std::shared_ptr<TopOfBook> ;
    int bestBid = 0;
    int bestBidSize = 0; 
    int bestAsk = 0;
    int bestAskSize = 0;
};

class priorityBook {
    using Bids = std::map< uint64_t, std::deque<std::shared_ptr<Order>>, std::greater<uint64_t>>;
    using Asks = std::map< uint64_t, std::deque<std::shared_ptr<Order>>, std::less<uint64_t>>;
    using OrderIdentifier = std::unordered_map< std::string, std::shared_ptr<Order>>;
    private:
        Bids bids_;
        Asks asks_;
        TopOfBook::tobShared topOfBook_;
        OrderIdentifier orderLookup_; 
        template<typename T>
        void print_leg(map<uint64_t, deque<shared_ptr<Order>>, T>& hashmap, Side side);
    public:
        Bids getBuyBook();
        Asks getAskBook();
        void addPriceLevel (const std::shared_ptr<Order> order);
        void updatePriceLevel (std::string orderId, uint64_t newPrice, int newSize, std::time_t newTime);
        void print(const string symbol);
};

class OrderBook {
    using SymbolBook = std::unordered_map<std::string, std::shared_ptr<priorityBook>>;
    public:
        int handleOrder (const std::vector<std::string>& inputString);
    private:
        void addOrder (const std::vector<std::string>& inputString);
        void modifyOrder (const std::vector<std::string>& inputString);
        void canceOrder (const std::vector<std::string>& inputString);
        void fillOrder (const std::vector<std::string>& inputString);
    SymbolBook symbolBook;
};

inline priorityBook::Bids priorityBook::getBuyBook() {
    return (bids_);
}
inline priorityBook::Asks priorityBook::getAskBook() {
    return (asks_);
}
inline void priorityBook::addPriceLevel (const std::shared_ptr<Order> order) {
    if (order->side == Side::BUY) {
        bids_[order->price].push_back(order);
        orderLookup_[order->orderId] = order;
    }
    else {
        asks_[order->price].push_back(order);
        orderLookup_[order->orderId] = order;
    }    
}


inline void priorityBook::updatePriceLevel (std::string orderId, uint64_t newPrice, int newSize, std::time_t newTime) {
    auto & order = orderLookup_[orderId];
    if (newSize == 0) {
        order->quantity = newSize;
    }
    else if (order->price == newPrice) {
        order->active = false;
    }
    else {
        order->active = false;
        std::shared_ptr<Order> newOrder = std::make_shared<Order>();
        newOrder->orderId = order->orderId;
        newOrder->transactionTime = newTime;
        newOrder->side = order->side;
        newOrder->orderType = order->orderType;
        newOrder->price = newPrice;
        newOrder->quantity = newSize;
        addPriceLevel(newOrder);
    }
}

template<typename T>
inline void priorityBook::print_leg(map<uint64_t, deque<shared_ptr<Order>>, T>& hashmap, Side side) {
    if (side == Side::SELL) {
        for (auto it = hashmap.rbegin(); it != hashmap.rend(); ++it) { // iterate over price levels
            int size_sum = 0;
            for (auto& order : it->second) {
                if (order->active) size_sum += order->quantity;
            }
            if (size_sum >0) {
                double price = it->first / 10000.0;
                string color = "31"; // red for asks
                cout << "\t\033[1;" << color << "m" << "$" << setw(6) << fixed << setprecision(2)
                    << price << setw(5) << size_sum << "\033[0m ";
                for (int i = 0; i < size_sum / 10; i++) {
                    cout << "█";
                }
                cout << "\n";
            }
        }
    } 
    else if (side == Side::BUY) {
        for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
            int size_sum = 0;
            for (auto& order : it->second) {
                if (order->active) size_sum += order->quantity;
            }
            if (size_sum >0) {
                double price = it->first / 10000.0;
                string color = "32"; // green for bids
                cout << "\t\033[1;" << color << "m" << "$" << setw(6) << fixed << setprecision(2)
                << price << setw(5) << size_sum << "\033[0m ";
                for (int i = 0; i < size_sum / 10; i++) {
                    cout << "█";
                }
                cout << "\n";
            }
        }
    }
}

inline void priorityBook::print(const string symbol) {
    cout << "---------- BOOK VIEW "<<"["<< symbol << "] " << "---------" << "\n";
    print_leg(asks_, Side::SELL);

    print_leg(bids_, Side::BUY);
    cout << "------------------------------------\n\n\n";
}