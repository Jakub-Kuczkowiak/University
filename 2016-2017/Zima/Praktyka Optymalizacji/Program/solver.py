from heapq import *
from itertools import permutations
from copy import deepcopy
import random


def solution_overall_time(machines):
    number_of_machines = len(machines)
    number_of_jobs = len(machines[0].list_of_times)
    tab = [[machines[i].list_of_times[j] for j in range(number_of_jobs)] for i in range(number_of_machines)]
    visited = [[False for j in range(number_of_jobs)] for i in range(number_of_machines)]

    min_heap = []  # (finish_task_time, (machine_num, job_num))
    global_time = 0
    heappush(min_heap, (global_time + tab[0][0], (0, 0)))

    while min_heap:
        current_elem = heappop(min_heap)
        machine_number = current_elem[1][0]
        job_number = current_elem[1][1]
        current_time = current_elem[0]

        visited[machine_number][job_number] = True
        global_time = max(global_time, current_time)

        # na prawo
        if (job_number + 1) < number_of_jobs and (machine_number == 0 or (visited[machine_number - 1][job_number + 1])):
            new_elem = (current_time + tab[machine_number][job_number + 1], (machine_number, job_number + 1))
            heappush(min_heap, new_elem)

        # w dol dla zerowej kolumny
        if job_number == 0 and (machine_number + 1) < number_of_machines:
            new_elem = (current_time + tab[machine_number + 1][job_number], (machine_number + 1, job_number))
            heappush(min_heap, new_elem)

        # w dol jesli nie jest w zerowej kolumnie i sciagnelismy z kolejki ten na lewy dolny skos od niego
        if machine_number + 1 < number_of_machines and job_number > 0 and visited[machine_number + 1][job_number - 1]:
            new_elem = (current_time + tab[machine_number + 1][job_number], (machine_number + 1, job_number))
            heappush(min_heap, new_elem)

    return global_time


def swap_with_copy(old_list, a, b):
    new_list = deepcopy(old_list)
    new_list[a], new_list[b] = new_list[b], new_list[a]
    return new_list


class Solver:
    def __init__(self, user_input):
        self.user_input = user_input

    def naive_approach(self):
        best_solution = deepcopy(self.user_input.machines)
        best_solution_time = solution_overall_time(best_solution)

        for perm in permutations(self.user_input.machines):
            current_solution_time = solution_overall_time(perm)
            if current_solution_time < best_solution_time:
                best_solution = perm
                best_solution_time = current_solution_time
        return best_solution, best_solution_time

    def neh_algorithm(self):
        machines = sorted(self.user_input.machines, key=lambda x: sum(x.list_of_times))
        best_solution = machines
        best_solution_time = solution_overall_time(best_solution)

        for i in range(1, len(machines)):
            current_solution = deepcopy(best_solution)
            for j in range(i, 0, -1):
                current_solution_time = solution_overall_time(current_solution)
                if current_solution_time < best_solution_time:
                    best_solution = current_solution
                    best_solution_time = current_solution_time
                current_solution[j], current_solution[j - 1] = current_solution[j - 1], current_solution[j]

        return best_solution, best_solution_time

    def random_search_approach(self, number_of_iterations):
        starting_solution = deepcopy(self.user_input.machines)
        random.shuffle(starting_solution)
        return self.generic_tabu_search_approach(number_of_iterations, 0, 0, starting_solution)

    def tabu_search_approach(self, number_of_iterations, max_tabu_length, expiry_time):
        starting_solution = deepcopy(self.user_input.machines)
        random.shuffle(starting_solution)
        return self.generic_tabu_search_approach(number_of_iterations, max_tabu_length, expiry_time, starting_solution)

    def tabu_search_with_neh(self, number_of_iterations, max_tabu_length, expiry_time):
        starting_solution = self.neh_algorithm()[0]
        return self.generic_tabu_search_approach(number_of_iterations, max_tabu_length, expiry_time, starting_solution)

    def generic_tabu_search_approach(self, number_of_iterations, max_tabu_length, expiry_time, starting_solution):
        best_solution = starting_solution
        best_solution_time = solution_overall_time(best_solution)
        next_solution = deepcopy(best_solution)
        next_solution_time = best_solution_time

        tabu_list = []

        while number_of_iterations > 0:
            neighbours = [
                (random.randrange(self.user_input.number_of_machines),
                 random.randrange(self.user_input.number_of_machines))
                for i in range(self.user_input.number_of_machines)]

            tabu_without_expiry_time = set([x[1] for x in tabu_list])
            neighbours = list(set(neighbours) - set(tabu_without_expiry_time))

            best_move = None

            for i in range(0, len(neighbours)):
                current_solution = swap_with_copy(next_solution, neighbours[i][0], neighbours[i][1])
                current_solution_time = solution_overall_time(current_solution)

                if current_solution_time < next_solution_time:
                    next_solution_time = current_solution_time
                    next_solution = current_solution
                    best_move = (neighbours[i][0], neighbours[i][1])

                if next_solution_time < best_solution_time:
                    best_solution_time = next_solution_time
                    best_solution = deepcopy(next_solution)

            tabu_list.append((expiry_time, best_move))
            tabu_list = [(x[0] - 1, x[1]) for x in tabu_list if x[0] > 0]

            if len(tabu_list) > max_tabu_length:
                tabu_list = tabu_list[1:]

            number_of_iterations -= 1
        return best_solution, best_solution_time
