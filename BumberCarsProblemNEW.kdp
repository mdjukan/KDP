const int N; // broj autica
const int M; // broj osoba

int usingCar[M] = {-1};
// usingCar[x] = y -- osoba x trenutno koristi auto y

sem personSem[M] = {0};
sem carSem[N] = {0};

//svaki autic ima barieru
sem door1[N] = {1};
sem door2[N] = {0};
int count[N] = {0};

list<int> personQueue = {};
list<int> carQueue = {};

sem mutex = 1;

void person(int id) {
    while (true) {
        wait(mutex);
        if (carQueue.empty()) {
            personQueue.push(id);
            signal(mutex);
            wait(personSem[id]);
        } else {
            int carId = carQueue.front();
            carQueue.pop();
            usingCar[id] = carId;
            signal(carSem[carId]);
            signal(mutex);
        }

        driveAround();

        int carId = usingCar[id];

        wait(door1[carId]);
        count[carId] += 1;
        if (count[carId] == 0) {
            signal(door1[carId]);
        } else {
            signal(door2[carId]);
        }

        wait(door2[carId]);

        count[carId] -= 1;
        if (count[carId] == 1) {
            signal(door2[carId]);
        } else {
            signal(door1[carId]);
        }

        // barrier za dva proces
        // njega i carId
    }
}

void car(int id) {
    while (true) {
        wait(mutex);
        if (personQueue.empty()) {
            carQeueu.push(id);
            signal(mutex);
            waint(carSem[id]);
        } else {
            int personId = personQueue.front();
            personQueue.pop();
            usingCar[personId] = id;
            signal(personSem[personId]);
            signal(mutex);
        }

        driveAround();

        wait(door1[id]);
        count[id] += 1;
        if (count[id] == 0) {
            signal(door1[id]);
        } else {
            signal(door2[id]);
        }

        wait(door2[id]);

        count[id] -= 1;
        if (count[id] == 1) {
            signal(door2[id]);
        } else {
            signal(door1[id]);
        }
    }
}
