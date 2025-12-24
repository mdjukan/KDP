const int N;


/* arrive1, arrive2 */

/* signal(arrive1);              signal(arrive2); */
/* wait(arrive2);                wait(arrive1); */


sem vehicles = 0;


sem mutex = 1;
list<pair<sem*, sem*>> waitingVehicles = {};

void vehicle() {
    sem vehicleArrived = 0, touristArrived = 0;
    while (true) {
        wait(mutex);
        waitingVehicles.emplace_back(&vehicleArrived, &touristArrived);
        signal(mutex);

        signal(vehicles);

        signal(vehicleArrived);
        wait(touristArrived);
    }
}

void tourist() {
    while (true) {
        wait(vehicles);
        wait(mutex);
        auto [vehicleArrived, touristArrived] = waitingVehicles.front();
        waitingVehicles.pop_front();
        signal(mutex);

        signal(*touristArrived);
        wait(*vehicleArrived);
    }
}
