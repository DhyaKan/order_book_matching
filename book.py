"""
#problem statement
Simulate a two-sided order book. Process a list of orders and return either
    # 1. total shared traded per stock
    # 2. sum of all transaction prices
    # 3. all unmactched orders remaining after processing

#Book rules

Bids : goal is to fidn the cheapeast seller
Ask : goal is find a better deal, meaning, customer willing to pay higher
match happens when BestSell <= BuyPrice (for Buy) and BestBid >= SellPrice (for Sell)

#Assumptions:

No routing obligations
Partial fills are supported
print BestBid and BestAsk on every order processing
When two orders are at same price level, the order came in first takes the priority
Unmatched shares are added to the book 
"""
