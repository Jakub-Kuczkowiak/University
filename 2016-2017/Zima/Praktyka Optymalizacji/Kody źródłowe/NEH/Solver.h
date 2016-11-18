//
// Created by Bartosz Bednarczyk on 03.11.2016.
//

#ifndef NEH_SOLVER_H
#define NEH_SOLVER_H


#include <vector>
#include "Customer.h"

class Solver {
   std::vector<Customer> customers;

  public:
    Solver(std::vector<Customer> customers);
    std::vector<Customer> solve();
};


#endif //NEH_SOLVER_H
