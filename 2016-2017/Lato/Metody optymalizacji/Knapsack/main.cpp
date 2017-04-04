#include <iostream>
#include "Solver.h"
#include "Input.h"

int main() {
    Input input;
    input.load_from_standard_input();
    Solver solver(input);

    std::cout << "----------NAIVE-------\n";
    solver.naive_approach().print_to_standard_output();
    std::cout << "-------------------\n";
    std::cout << "----------DP-------\n";
    solver.dp_approach().print_to_standard_output();
    std::cout << "-------------------\n";
    std::cout << "---------B&B--------\n";
    solver.bnb_approach().print_to_standard_output();

    return 0;
}