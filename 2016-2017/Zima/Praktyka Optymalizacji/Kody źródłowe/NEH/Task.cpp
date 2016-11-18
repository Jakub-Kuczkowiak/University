//
// Created by Bartosz Bednarczyk on 03.11.2016.
//

#include "Task.h"

Task::Task(size_t required_time, size_t station_number)
{
  this->required_time = required_time;
  this->station_number = station_number;
}

size_t Task::get_required_time() {
  return this->required_time;
}

size_t Task::get_station_number() {
  return this->station_number;
}

