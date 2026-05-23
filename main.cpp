#include <iostream>
#include <fstream>
#include <sstream>
#include "book.h"
#include <vector>

using namespace std;

vector<string> parseLine (const string& line) {
    vector<string> tokens;
    istringstream ss(line);
    string token {};
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    //support user order entry and also queued orders processing through .txt file
    string fileName = "queued_orders.txt";
    ifstream inputFile;
    inputFile.open(fileName);

    if (!inputFile.is_open()) {
        return 1;
    }
    OrderBook orderBook{};
    string line;
    while (getline(inputFile, line)) {
        if(line.empty()) continue;
        vector token = parseLine(line);
        orderBook.handleOrder(token);
    }
    return 0;
}