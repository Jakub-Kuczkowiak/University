//
// Created by Bartosz Bednarczyk on 03.11.2016.
//

#ifndef NEH_CUSTOMER_H
#define NEH_CUSTOMER_H


#include <vector>
#include "Task.h"

class Customer {
  std::vector<Task> tasks;
  size_t overall_required_time;
  size_t id;

  public:
    Customer(std::vector<Task> tasks, size_t id);
    std::vector<Task> get_tasks();
    size_t get_overall_required_time();
    size_t get_id();
};


#endif //NEH_CUSTOMER_H
