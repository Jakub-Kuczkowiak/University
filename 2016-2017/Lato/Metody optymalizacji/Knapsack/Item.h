#ifndef KNAPSACK_ITEM_H
#define KNAPSACK_ITEM_H

#include <cstdlib>

class Item {
private:
    size_t item_id;
    unsigned int weight;
    unsigned int profit;

public:
    Item(size_t item_id, unsigned int weight, unsigned int profit);
    unsigned int get_weight();
    size_t get_item_id();
    unsigned int get_profit();
};


#endif //KNAPSACK_ITEM_H
