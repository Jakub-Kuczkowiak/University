#ifndef KNAPSACK_BACKPACK_H
#define KNAPSACK_BACKPACK_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Item.h"

class Backpack {
private:
    std::vector<Item> items;
    unsigned int maximal_capacity;
    unsigned int current_weight;
    unsigned int current_profit;

public:
    Backpack(unsigned int maximal_capacity = 0, std::vector<Item> items = {});
    size_t get_number_of_items();
    Item get_ith_item(const size_t task_number);
    void add_item(Item item);
    void print_to_standard_output();
    void print_to_file(const std::string file_name);
    unsigned int get_current_weight();
    unsigned int get_current_profit();
    unsigned int get_maximal_capacity();
};


#endif //KNAPSACK_BACKPACK_H
