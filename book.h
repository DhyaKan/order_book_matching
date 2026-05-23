#include "order.h"
#include <unordered_map>
#include <deque>
#include <memory>
#include <map>

struct TopOfBook {
    using tobShared = std::shared_ptr<TopOfBook> ;
    int bestBid = 0;
    int bestBidSize = 0; 
    int bestAsk = 0;
    int bestAskSize = 0;
};

class priorityBook {
    private:
        std::map< int, std::deque<std::shared_ptr<Order>>, std::greater<int>> bids;
        std::map<int, std::deque<std::shared_ptr<Order>>, std::less<int>> asks;
        TopOfBook::tobShared topOfBook;
};

class OrderBook {
    using SymbolBook = std::unordered_map<std::string, std::shared_ptr<priorityBook>>;
    public:
        void handleOrder (const std::vector<std::string>& inputString);
    private:
        void addOrder (const std::vector<std::string>& inputString);
        void modifyOrder (const std::vector<std::string>& inputString);
        void canceOrder (const std::vector<std::string>& inputString);
        void fillOrder (const std::vector<std::string>& inputString);
    SymbolBook symbolBook;
};