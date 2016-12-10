class Machine:
    def __init__(self, machine_id, number_of_jobs, list_of_times):
        self.machine_id = machine_id
        self.number_of_jobs = number_of_jobs
        self.list_of_times = list_of_times

    def __str__(self):
        return "Machine id = {}, times = {}".format(self.machine_id, self.list_of_times)
