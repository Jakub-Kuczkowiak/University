#include "Backpack.h"

Backpack::Backpack(unsigned int maximal_capacity, std::vector<Item> items) {
    this->items = items;
    this->maximal_capacity = maximal_capacity;
    this->current_weight = 0;
    this->current_profit = 0;

    for(Item &item : items) {
        this->current_weight += item.get_weight();
        this->current_profit += item.get_profit();
    }
}

size_t Backpack::get_number_of_items() {
    return this->items.size();
}

Item Backpack::get_ith_item(const size_t item_number) {
    if (item_number >= this->items.size()) {
        throw std::out_of_range("Illegal number of an item!");
    }
    return this->items[item_number];
}

void Backpack::add_item(Item item) {
    this->items.push_back(item);
    this->current_profit += item.get_profit();
    this->current_weight += item.get_weight();
}

void Backpack::print_to_standard_output() {
    std::cout << "The total number of assigned items is " << this->items.size() << "\n";
    std::cout << "The total weight is " << this->current_weight << "\n";
    std::cout << "The total profit is " << this->current_profit << "\n";
    std::cout << "Assigned items : ";

    for(Item &item : items) {
        std::cout << "Task id = " << item.get_item_id() << " ";
    }

    std::cout << "\n";
}

void Backpack::print_to_file(const std::string file_name) {
    std::ofstream output_file(file_name, std::ios::out);
    output_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    if (output_file.is_open()) {
        output_file << "The total number of assigned items is " << this->items.size() << "\n";
        output_file << "The total weight is " << this->current_weight << "\n";
        output_file << "The total profit is " << this->current_profit << "\n";
        output_file << "Assigned items : ";

        for(Item &item : items) {
            output_file << "Task id = " << item.get_item_id() << " ";
        }

        output_file << "\n";
    }
    output_file.close();

}

unsigned int Backpack::get_current_weight() {
    return this->current_weight;
}

unsigned int Backpack::get_current_profit() {
    return this->current_profit;
}

unsigned int Backpack::get_maximal_capacity() {
    return this->maximal_capacity;
}
