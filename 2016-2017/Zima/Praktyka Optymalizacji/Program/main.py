from input import Input
from solver import Solver
import time


# example: plot_graph([1,2,3], [ [1,2,3] ], "X", "Y", legend = ["y=x"], "Simple title", "graph.png")
def plot_graph(x_values, y_values, ox_label, oy_label, legend, title, output_file_name):
    import matplotlib.pyplot as plt
    # plt.yscale('log', nonposy='clip')
    plt.xlabel(ox_label)
    plt.ylabel(oy_label)
    plt.title(title)

    for y in y_values:
        plt.plot(x_values, y)

    plt.legend(legend, loc='lower left')
    plt.savefig(output_file_name)


def test_taillard_20_wyniki():
    x = range(1, 11, 1)
    y = []
    ox_label = "Nr testu [1..10]"
    oy_label = "Czas zakonczenia ostatniego zadania na ostatniej maszynie [s]"
    legend = ["Taillard", "NEH", "Random100", "Tabu100", "NEHTabu100"]
    title = "Taillard 20 jobs 10 machines - porownanie wynikow"

    naive = [1582, 1659, 1496, 1378, 1419, 1397, 1484, 1538, 1593, 1591]
    neh = []
    random100 = []
    tabu100 = []
    nehtabu100 = []

    for test_number in range(1, 11):
        print "test = {}".format(test_number)
        user_input = Input()
        user_input.load_from_file("testy/Taillard_20jobs_10machines_{}.txt".format(test_number))
        solver = Solver(user_input)

        # naive_sol = solver.naive_approach()[1]
        neh_sol = solver.neh_algorithm()[1]
        random100_sol = 0
        tabu100_sol = 0
        nehtabu100_sol = 0

        for iteration in range(0, 5):
            random100_sol += solver.random_search_approach(100)[1]
            tabu100_sol += solver.tabu_search_approach(100, 5, 3)[1]
            nehtabu100_sol += solver.tabu_search_with_neh(100, 5, 3)[1]

        # naive.append(naive_sol)
        neh.append(neh_sol)
        random100.append(random100_sol / 5.0)
        tabu100.append(tabu100_sol / 5.0)
        nehtabu100.append(nehtabu100_sol / 5.0)

    y = [naive, neh, random100, tabu100, nehtabu100]
    plot_graph(x, y, ox_label, oy_label, legend, title, "test_taillard_20_wyniki.png")


def test_taillard_20_czasy():
    x = range(1, 11, 1)
    ox_label = "Nr testu [1..10]"
    oy_label = "Czas wykonania danego algorytmu [s]"
    legend = ["Cuckoo", "NEH", "Random100", "Tabu100", "NEHTabu100"]
    title = "Taillard 20 jobs 10 machines - porownanie wynikow"

    naive = [1.55, 1.44, 1.64, 1.66, 1.29, 1.27, 1.18, 1.34, 1.37, 1.28]
    neh = []
    random100 = []
    tabu100 = []
    nehtabu100 = []

    for test_number in range(1, 11):
        print "test = {}".format(test_number)
        user_input = Input()
        user_input.load_from_file("testy/Taillard_20jobs_10machines_{}.txt".format(test_number))
        solver = Solver(user_input)

        start = time.time()
        a = solver.neh_algorithm()[1]
        end = time.time()
        neh.append(end - start)

        start = time.time()
        for iteration in range(0, 5):
            a = solver.random_search_approach(100)[1]
        end = time.time()

        random100.append((end - start) / 5.0)

        start = time.time()
        for iteration in range(0, 5):
            a = solver.tabu_search_approach(100, 5, 3)[1]
        end = time.time()

        tabu100.append((end - start) / 5.0)

        start = time.time()
        for iteration in range(0, 5):
            a = solver.tabu_search_with_neh(100, 5, 3)[1]
        end = time.time()

        nehtabu100.append((end - start) / 5.0)

    y = [naive, neh, random100, tabu100, nehtabu100]
    plot_graph(x, y, ox_label, oy_label, legend, title, "test_taillard_20_czasy.png")


def main():
    user_input = Input()
    user_input.load_from_file("testy/Taillard_50jobs_10machines_4.txt")
    solver = Solver(user_input)
    print solver.tabu_search_with_neh(1000, 5, 3)[1]


test_taillard_20_czasy()
