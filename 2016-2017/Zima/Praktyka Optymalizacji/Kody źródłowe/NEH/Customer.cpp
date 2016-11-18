//
// Created by Bartosz Bednarczyk on 03.11.2016.
//

#include "Customer.h"

Customer::Customer(std::vector<Task> tasks, size_t id) {
  this->id = id;
  this->tasks = tasks;
  this->overall_required_time = 0;
  for (auto &&task : tasks) {
    this->overall_required_time += task.get_required_time();
  }
}

std::vector<Task> Customer::get_tasks() {
  return this->tasks;
}

size_t Customer::get_overall_required_time() {
  return this->overall_required_time;
}

size_t Customer::get_id() {
  return this->id;
}
