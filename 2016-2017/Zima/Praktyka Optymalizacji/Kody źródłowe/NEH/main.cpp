#include <iostream>
#include <random>
#include "Customer.h"
#include "Solver.h"

int main() {

  std::vector<Customer> customers;
  const size_t number_of_customers = 10;
  const size_t number_of_stations = 20;
  const size_t min_time = 2;
  const size_t max_time = 10;

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> time_distr(min_time, max_time); // define the range


  for(size_t customer_num = 0; customer_num < number_of_customers; ++customer_num) {
    std::vector<Task> tasks;

    for(size_t station_num = 0; station_num < number_of_stations; ++station_num) {
      Task task(time_distr(eng), station_num);
      tasks.push_back(task);
    }

    Customer customer(tasks, customer_num);
    customers.push_back(customer);
  }


  Solver solver(customers);
  auto solution = solver.solve();

  std::cout << "\nSolution : ";

  for(size_t customer_num = 0; customer_num < solution.size(); ++customer_num) {
    std::cout << solution[customer_num].get_id() << " ";
  }

  std::cout << "\n";

  return 0;
}