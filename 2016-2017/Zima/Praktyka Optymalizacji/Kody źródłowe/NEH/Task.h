//
// Created by Bartosz Bednarczyk on 03.11.2016.
//

#ifndef NEH_TASK_H
#define NEH_TASK_H


#include <stdatomic.h>

class Task {
  size_t required_time;
  size_t station_number;

  public:
    Task(size_t required_time, size_t station_number);
    size_t get_required_time();
    size_t get_station_number();
};


#endif //NEH_TASK_H
