#ifndef KNAPSACK_SOLVER_H
#define KNAPSACK_SOLVER_H

#include "Input.h"
#include "Backpack.h"

class Solver {
private:
    Input input;
public:
    Solver(Input input) : input(input){ }
    Backpack dp_approach();
    Backpack bnb_approach();
    Backpack naive_approach();
};

#endif //KNAPSACK_SOLVER_H
