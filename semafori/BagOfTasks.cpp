struct Task {
    bool finnished = false;
    //.....
};


struct BagOfTasks {
    array<Task> tasks;
    sem available;
    sem mutex = 1;
    int next;
    int finnished = 0;

    int getTask() {
        wait(available);
        wait(mutex);
        int returnVal = next;
        next += 1;
        signal(mutex);
        return returnVal;
    }

    int taskFinnished(int idx) {
        wait(mutex);
        finnished += 1;
        if (finnished == tasks.size()) {
            collector.collectResults(tasks);
            tasks = collector.getNewTasks();
            for (int i = 0; i < tasks.size(); i++) {
                signal(available);
            }
            next = 0;
        }
        signal(mutex);
    }
};

BagOfTasks bag;
bag.tasks = collector.getNewTasks();

void worker(int id) {
    while (true) {
        int idx = bag.getTask();
        bag.task[idx].perform();
        bag.taskFinnished(idx);
    }
}

// n niti sa worker -

