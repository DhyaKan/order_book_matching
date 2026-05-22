#problem statement
Simulate a two-sided order book. Process a list of orders and return the order book view with key metrics like,
    # 1. top 10 traded stock (with price and executed qty) info
    # 2. BestBid and BestAsk of each stock
    # 3. all unmactched orders remaining after processing (quantity of shares)

#Book rules

Bids : goal is to find the cheapeast seller
Ask : goal is find a better deal, meaning, customer willing to pay higher
match happens when BestSell <= BuyPrice (for Buy) and BestBid >= SellPrice (for Sell)

#Assumptions:

No routing obligations
Partial fills are supported
When two orders are at same price level, the order came in first takes the priority
Unmatched shares are added to the book 
multi-symbol order book
support market order and limit orders

future projects 
1️⃣ Market data feed parser

2️⃣ Lock-free queue

3️⃣ Async low-latency logger

4️⃣ Mini trading system