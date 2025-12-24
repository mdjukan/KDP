const int N;

list<sem*> enterRequests[N] = [<empty-list>, ...];
list<sem*> exitRequests[N] = [<empty-list>, ...];
sem enterMutex = 1;
sem exitMutex = 1;
sem elevatorSem = 0;


void user(int enterFloor, int exitFloor) {
    sem s = 0;
    wait(enterMutex);
    enterRequests[enterFloor].append(&s);
    signal(enterMutex);

    wait(s);

    wait(exitMutex);
    exitRequests[exitFloor].append(&s);
    signal(exitMutex);

    signal(elevatorSem);

    wait(s);
    signal(elevatorSem);
}

enum Direction {
    UP, DOWN
};

void elevator() {
    int floor = 0;
    Direction dir = UP;
                       //
    while (true) {
        wait(enterMutex);
        for (sem *s : enterRequests[floor]) {
            signal(*s);
            wait(elevatorSem);
        }
        enterRequests[floor].clear(); //prazni listu
        signal(enterMutex);

        wait(exitMutex);
        for (sem *s : exitRequests[floor]) {
            signal(*s);
            wait(elevatorSem);
        }
        exitRequests[floor].clear();
        signal(exitMutex);

        if (dir == UP) {
            floor += 1;
            if (floor == N-1) {
                dir = DOWN;
            }
        } else {
            floor -= 1;
            if (floor == 0) {
                dir = UP;
            }
        }
    }
}
