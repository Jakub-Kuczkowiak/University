#include "Item.h"

Item::Item(size_t item_id, unsigned int weight, unsigned int profit) {
    this->item_id = item_id;
    this->weight = weight;
    this->profit = profit;
}

unsigned int Item::get_weight() {
    return this->weight;
}

size_t Item::get_item_id() {
    return this->item_id;
}

unsigned int Item::get_profit() {
    return this->profit;
}
