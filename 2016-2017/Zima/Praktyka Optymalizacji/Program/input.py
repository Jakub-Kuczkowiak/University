from machine import Machine


class Input:
    def __init__(self, number_of_jobs=None, number_of_machines=None, machines=None):
        self.number_of_jobs = number_of_jobs
        self.number_of_machines = number_of_machines
        self.machines = machines

    def load_from_file(self, file_name):
        with open(file_name, 'r') as input_file:
            lines = [line.replace('\r', '\n').rstrip('\n') for line in input_file]
            self.number_of_jobs = int(lines[0])
            self.number_of_machines = int(lines[1])
            matrix_of_times = map(lambda x: map(int, x.split(' ')), lines[2:])

        self.machines = []
        for machine_id in range(0, self.number_of_machines):
            machine = Machine(machine_id, self.number_of_jobs, matrix_of_times[machine_id])
            self.machines.append(machine)

    def __str__(self):
        result = "#jobs = {}, #machines = {}\n".format(self.number_of_jobs, self.number_of_machines)
        result += "\n".join([str(machine) for machine in self.machines])
        return result
