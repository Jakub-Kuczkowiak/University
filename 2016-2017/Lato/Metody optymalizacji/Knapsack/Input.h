#ifndef KNAPSACK_INPUT_H
#define KNAPSACK_INPUT_H

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Item.h"

class Input {
private:
    unsigned int capacity;
    size_t number_of_items;
    std::vector<unsigned int> profits;
    std::vector<unsigned int> weights;
public:
    Input(unsigned int capacity = 0, size_t number_of_items = 0, std::vector<unsigned int> weights = {}, std::vector<unsigned int> profits = {});
    void load_from_file(const std::string file_name);
    void load_from_standard_input();
    void print_to_file(const std::string file_name);
    void print_to_standard_output();
    std::vector<Item> get_as_vector_of_item();
    unsigned int get_capacity();
};

#endif //KNAPSACK_INPUT_H
