const int N;

sem arrive[2 * N] = {{0}};
sem cont[2 * N] = {{0}};

sem coordArrive[2] = {0, 0};

//0, 1, ..., 2*N-1
//
//
//signal(arrive1)
//wait(arrive2)

void process(int id) {
    barrier(id);
    //....
}

void barrier(int id) {
    signal(arrive[id]);
    wait(cont[id]);
}

void coordinator(int id) { // 0 ili 1
    int base = id == 0 ? 0 : N;
    for (int i = 0; i < N; i++) {
        wait(arrive[base + i]);
    }

    int other = 1 - id;
    signal(coordArrive[id]);
    wait(coordArrive[other]);

    for (int i = 0; i < N; i++) {
        signal(cont[base + i]);
    }
}
