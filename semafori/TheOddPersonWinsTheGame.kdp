int vals[3];

int winner;
bool done = false;

sem door1 = 1, door2 = 0;
int count = 0;

void barrier() {
    wait(door1);
    count += 1;
    if (count < 3) {
        signal(door1);
    } else {
        signal(door2);
    }

    wait(door2);
    count -= 1;
    if (count > 0) {
        signal(door2);
    } else {
        signal(door1);
    }
}

void player(int id) {
    while (!done) {
        vals[id] = random() % 2;

        barrier();

        int total = vals[0] + vals[1] + vals[2];

        if ((total == 1 && vals[id] == 1) || (total == 2 && vals[id] == 0) {
            winner = id;
            done = true;
        }

        barrier();
    }
}
