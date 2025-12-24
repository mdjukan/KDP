void person() {
    getFood();
    sitAtTable();
    eat();
    leaveTable();
    walkAway();
}

const int N;
sem mutex = 1;
int readyToEat = 0; // uzeo hranu nise seo za sto
int readyToLeave = 0; // zavrsio eat nije otisao
int eating = 0; // izvrsava eat

sem enter = 0;

void sitAtTable() {
    wait(mutex);
    readyToEat += 1;

    if (eating == 0) {
        if (readyToEat == 2) {
            signal(enter);
            signal(enter);
            readyToEat = 0;
            eating = 2;
        }
    } else if (eating == 2 && waitingToLeave == 1) {
        signal(enter);
        readyToEat -= 1;
        signal(exit);
        waitingToLeave = 0;
    } else if (eating < N) {
        signal(enter);
        readyToEat -= 1;
        eating += 1;
    }


    //......... 2, 1 ->

    signal(mutex);

    wait(enter);
}

void leaveTable() {
    wait(mutex);
    eating -= 1;
    waitingToLeave += 1;

    if (eating == N-1 && readyToEat > 0) {
        signal(enter);
        signal(exit);
        waitingToLeave -= 1;
    } else if (eating > 1) {
        signal(exit);
        waitingToLeave -= 1;
    } else if (eating == 0) {
        signal(exit);
        signal(exit);
        waitingToLeave = 0;
    }

    signal(mutex);

    wait(exit);
}
