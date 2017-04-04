#include <queue>
#include <algorithm>
#include <climits>
#include "Solver.h"

Backpack Solver::naive_approach() {
    std::vector<Item> items = input.get_as_vector_of_item();
    size_t number_of_tasks = items.size();
    unsigned int maximum_capacity = input.get_capacity();

    std::queue<std::pair<Backpack, size_t> > Q;
    Backpack root(maximum_capacity);
    Q.push({root, -1});

    Backpack best_backpack = root;

    while (!Q.empty()) {
        std::pair<Backpack, size_t> front;
        front = Q.front();
        Backpack current_backpack = front.first;
        size_t last_tried_item = front.second;
        Q.pop();

        if (current_backpack.get_current_profit() > best_backpack.get_current_profit()) {
            best_backpack = current_backpack;
        }

        if (last_tried_item != (number_of_tasks - 1)) {

            if (current_backpack.get_current_weight() + items[last_tried_item + 1].get_weight() <= maximum_capacity) {
                Backpack next_proc_to_try = current_backpack;
                next_proc_to_try.add_item(items[last_tried_item + 1]);
                Q.push({next_proc_to_try, last_tried_item + 1});
            }

            Q.push({current_backpack, last_tried_item + 1});
        }
    }

    return best_backpack;
}

Backpack Solver::dp_approach() {
    std::vector<Item> items = input.get_as_vector_of_item();
    size_t number_of_tasks = items.size();
    unsigned int maximum_capacity = input.get_capacity();

    const int minus_infinity = INT32_MIN;
    std::vector<std::pair<int, std::vector<Item>>> dp(maximum_capacity + 1, {minus_infinity, {}});

    dp[0] = {0, {}};

    for (int i = 0; i < number_of_tasks; i++) {
        for (int j = maximum_capacity; j >= items[i].get_weight(); j--) {

            size_t new_index = j - items[i].get_weight();

            if (dp[new_index].first != minus_infinity) {
                int new_value = dp[new_index].first + items[i].get_profit();
                if (dp[j].first < dp[new_index].first) {
                    dp[j] = dp[new_index];
                    dp[j].first += items[i].get_profit();
                    dp[j].second.push_back(items[i]);
                }
            }
        }
    }

    Backpack result;

    for (int answer = maximum_capacity; answer >= 0; answer--) {
        if (dp[answer].first != minus_infinity) {
            result = Backpack(maximum_capacity, dp[answer].second);
            break;
        }

    }

    return result;
}

Backpack Solver::bnb_approach() {
    std::vector<Item> items = input.get_as_vector_of_item();
    size_t number_of_tasks = items.size();
    unsigned int maximum_capacity = input.get_capacity();

    std::queue<std::pair<Backpack, size_t> > Q;
    Backpack root(maximum_capacity);
    Q.push({root, -1});

    Backpack best_backpack = root;

    while (!Q.empty()) {
        std::pair<Backpack, size_t> front;
        front = Q.front();
        Backpack current_backpack = front.first;
        size_t last_tried_item = front.second;
        Q.pop();

        if (current_backpack.get_current_profit() > best_backpack.get_current_profit()) {
            best_backpack = current_backpack;
        }

        if(last_tried_item != (number_of_tasks - 1)) {

            if(current_backpack.get_current_weight() + items[last_tried_item+1].get_weight() <= maximum_capacity) {
                Backpack next_backpack_to_try = current_backpack;
                next_backpack_to_try.add_item(items[last_tried_item+1]);

                // compute bound
                unsigned int expected_profit = next_backpack_to_try.get_current_profit();
                unsigned int expected_weight = next_backpack_to_try.get_current_weight();
                size_t level = last_tried_item + 2;

                while ((level < number_of_tasks) && (expected_weight + items[level].get_weight() <= maximum_capacity))
                {
                    expected_profit += items[level].get_profit();
                    expected_weight += items[level].get_weight();
                    ++level;
                }

                if(level < number_of_tasks) {
                    expected_profit += (maximum_capacity - expected_weight);
                }

                if(expected_profit >= best_backpack.get_current_profit()) {
                    Q.push({next_backpack_to_try, last_tried_item+1});
                }

            }

            // compute bound for proc without last_tried_item+1
            unsigned int expected_profit = current_backpack.get_current_profit();
            unsigned int expected_weight = current_backpack.get_current_profit();
            size_t level = last_tried_item + 2;

            while ((level < number_of_tasks) && (expected_weight + items[level].get_weight() <= maximum_capacity))
            {
                expected_profit += items[level].get_profit();
                expected_weight += items[level].get_weight();
                ++level;
            }

            if(level < number_of_tasks) {
                expected_profit += (maximum_capacity - expected_weight);
            }

            if(expected_profit >= best_backpack.get_current_profit()) {
                Q.push({current_backpack, last_tried_item+1});
            }
        }
    }

    return best_backpack;
}
