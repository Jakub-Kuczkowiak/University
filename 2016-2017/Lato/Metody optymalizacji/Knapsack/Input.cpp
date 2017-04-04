#include "Input.h"

Input::Input(unsigned int capacity, size_t number_of_items, std::vector<unsigned int> weights, std::vector<unsigned int> profits) {
    this->number_of_items = number_of_items;
    this->weights = weights;
    this->profits = profits;
    this->capacity = capacity;
}

/*
 * Input format:
 * Capacity
 * Number of items
 * weight_1 weight_2 ... weight_n
 * profit_1 profit_2 ... profit_n
 */

void Input::load_from_file(const std::string file_name) {
    this->number_of_items = 0;
    this->profits.clear();
    this->weights.clear();

    std::ifstream input_file(file_name, std::ios::in);
    input_file.exceptions(std::ifstream::failbit | std::ifstream::badbit );

    if(input_file.is_open()) {
        input_file >> this->capacity;
        input_file >> this->number_of_items;
        this->profits.resize(this->number_of_items);
        this->weights.resize(this->number_of_items);

        for(size_t ith_weight = 0; ith_weight < this->number_of_items; ++ith_weight) {
            input_file >> this->weights[ith_weight];
        }

        for(size_t ith_profits = 0; ith_profits < this->number_of_items; ++ith_profits) {
            input_file >> this->profits[ith_profits];
        }
    }

    input_file.close();
}

void Input::load_from_standard_input() {
    this->number_of_items = 0;
    this->profits.clear();
    this->weights.clear();

    std::cin >> this->capacity;
    std::cin >> this->number_of_items;
    this->profits.resize(this->number_of_items);
    this->weights.resize(this->number_of_items);

    for(size_t ith_weight = 0; ith_weight < this->number_of_items; ++ith_weight) {
        std::cin >> this->weights[ith_weight];
    }

    for(size_t ith_profits = 0; ith_profits < this->number_of_items; ++ith_profits) {
        std::cin >> this->profits[ith_profits];
    }
}

std::vector<Item> Input::get_as_vector_of_item() {
    std::vector<Item> items;

    for(size_t item_number = 0; item_number < this->number_of_items; ++item_number ) {
        items.push_back(Item(item_number, this->weights[item_number], this->profits[item_number]));
    }

    return items;
}

void Input::print_to_file(const std::string file_name) {
    std::ofstream output_file(file_name, std::ios::out);
    output_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    if (output_file.is_open()) {
        output_file << this->number_of_items << "\n";

        for(size_t task_num = 0; task_num < this->number_of_items; ++task_num) {
            output_file << this->weights[task_num] << " ";
        }

        output_file << "\n";

        for(size_t task_num = 0; task_num < this->number_of_items; ++task_num) {
            output_file << this->profits[task_num] << " ";
        }

        output_file << "\n";
    }

    output_file.close();
}

unsigned int Input::get_capacity() {
    return capacity;
}

void Input::print_to_standard_output() {
    std::cout << this->number_of_items << "\n";

    for(size_t task_num = 0; task_num < this->number_of_items; ++task_num) {
        std::cout << this->weights[task_num] << " ";
    }

    std::cout << "\n";

    for(size_t task_num = 0; task_num < this->number_of_items; ++task_num) {
        std::cout << this->profits[task_num] << " ";
    }

    std::cout << "\n";
}
