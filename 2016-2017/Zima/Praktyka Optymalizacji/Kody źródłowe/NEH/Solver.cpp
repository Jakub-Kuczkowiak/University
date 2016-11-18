//
// Created by Bartosz Bednarczyk on 03.11.2016.
//

#include <functional>
#include <queue>
#include "Solver.h"

Solver::Solver(std::vector<Customer> customers) {
  this->customers = customers;
}


// calculating total cost for a given ordered vector of customers
size_t overall_time(std::vector<Customer> customers) {
  std::vector<std::vector<size_t>> tab; // tab[i][j] = the required time to finish i-th task on j-th station
  tab.resize(customers.size());
  for (size_t i = 0; i < tab.size(); ++i) {
    tab[i].resize(
      customers[i].get_tasks().size()); // we will assume that every customer has the same number of tasks inside
  }

  for (size_t i = 0; i < tab.size(); ++i) {
    for (size_t j = 0; j < tab[i].size(); ++j) {
      tab[i][j] = customers[i].get_tasks()[j].get_required_time();
    }
  }

  std::vector<std::vector<bool>> visited; // visited[i][j] = 1 iff we finished i-th job on j-th machine
  visited.resize(tab.size());
  for (size_t i = 0; i < visited.size(); ++i) {
    visited[i].resize(tab[i].size(), false);
  }

  typedef std::pair<size_t, std::pair<size_t, size_t>> triple; // (finish_task_time, (machine num, required_time))
  std::priority_queue<triple, std::vector<triple>, std::greater<triple> > min_heap;

  size_t global_time = 0;
  min_heap.push({global_time + tab[0][0], {0, 0}});

  while (!min_heap.empty()) {
    auto current_task = min_heap.top();
    size_t customer_number = current_task.second.first;
    size_t station_number = current_task.second.second;
    size_t current_time = current_task.first;
    visited[customer_number][station_number] = true;
    global_time = std::max(global_time, current_time);
    min_heap.pop();

    if ((customer_number < customers.size() && station_number < tab[customer_number].size()) &&
        (customer_number == 0 || visited[customer_number - 1][station_number + 1])) {
        min_heap.push({current_time + tab[customer_number][station_number + 1], {customer_number, station_number + 1}});
    }
  }

  return global_time;
}


// An example implementation of NEH (Nawaz, Enscore, Ham) algorithm
std::vector<Customer> Solver::solve() {

  // Step 1.
  sort(this->customers.begin(), this->customers.end(),
       [](Customer a, Customer b) { return a.get_overall_required_time() < b.get_overall_required_time(); });

  std::vector<Customer> solution = this->customers;

  // Step 2&3.

  for(size_t i = 1; i < customers.size(); ++i) {
    std::vector<Customer> current_solution = solution;

    for(size_t j = i; j >= 1; j--) {
      if(overall_time(current_solution) < overall_time(solution)) solution = current_solution;
      std::swap(current_solution[i], current_solution[i-1]);
    }
  }

  return solution;
}

