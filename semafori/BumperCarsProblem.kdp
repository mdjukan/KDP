const int N;
const int M;

sem personSems[N] = {0};
sem carSems[M] = {0};

sem mutex = 1;
list<int> waitingPersons = {};
list<int> waitingCars = {};

int pairedWithCar;

void car(int id) {
    while (true) {
        wait(mutex);
        if (waitingPersons.empty()) {
            waitingCars.append(id);
            signal(mutex);
            wait(carSems[id]);
        } else {
            int personId = waitingPersons.front();
            waitingPerosns.pop_front();
            pairedWithCar = id;
            signal(personSems[personId]);
            wait(carSems[id]);
        }

        driveAround();

        wait(carSems[id]);
    }
}

void person(int id) {
    int carId;
    while (true) {
        wait(mutex);
        if (!waitingCars.empty()) {
            carId = waitingCars.front();
            waitingCars.pop_front();
        } else {
            waitingPersons.append(id);
            signal(mutex);
            wait(personSems[id]);
            carId = pariedWithCar;
        }

        signal(carSems[carId]);
        signal(mutex);

        driveAround();

        signal(carSems[carId]);
    }
}
