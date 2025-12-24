sem sems[2*N + 1];

sem &mutex = sems[2*N];

int headEnter = 0, tailEnter = 0;

//headEnter = (headEnter + 1) % N // oslobadjenje 
//tailEnter = (tailEnter + 1) % N // alokacija

int headLeave = N, tailLeave = N;

//headLeave = N + (headLeave + 1) % N;
//tailLeave = N + (tailLeave + 1) % N;

int emptySpace = N;
int waitingToEnter = 0;
int waitingToExit = 0;

void requestEnter() {
    wait(mutex);
    if (emptySpace + waitingToExit - (waitingToEnter+1) < 0) {
        signal(mutex);
        return false;
    }

    waitingToEnter += 1;
    if (waitingToEnter == 1 && waitingToExit == 0) {
        signal(mutex);
        return true;
    }

    sem &s = sems[tailEnter];
    tailEnter = (tailEnter + 1) % N;
    signal(mutex);
    wait(s);
    return false;
}

void enter() {
    wait(mutex);
    waitingToEnter -= 1;
    emptySpace -= 1;
    signal(mutex);

    SIGNAL();
}


const int K;

//// za koga brojim --> da li brojim za one koji izlaze/ulaze
bool enterHasPriority = true;
int consecutivePass = 0;

void SIGNAL() {
    // da li imam slobodno mesto <-- tada mogu da odblokiram nekog ko
    // zeli da udje
    wait(mutex);

    bool signalEnter = (emtpySpace > 0) && (waitingToEnter > 0)
    bool signalExit = (waitingToExit > 0);

    if ((signalEnter && !signalExit) 
    || (signalEnter && signalExit && enterHasPriority)) {
        sem &s = sems[headEnter];
        headEnter = (1 + headEnter) % N;
        enterFirst = !enterFirst;

        // odradjen je enter
        if (enterHasPriority) {
            consecutivePass += 1;
            if (consecutivePass == K) {
                enterHasPriority = false;
                consecutivePass = 0;
            }
        } else {
            enterHasPriority = true;
            consecutivePass = 1;
        }

        signal(s);
    } else if (signalExit) {
        sem &s = sems[headExit];
        headExit = N + (headExist + 1) % N;
        enterFirst = !enterFirst;

        if (enterHasPriority) {
            enterHasPriority = false;
            consecutivePass = 1;
        } else {
            consecutivePass += 1;
            if (consecutivePass == K) {
                consecutivePass = 0;
                enterHasPriority = true;
            }
        }

        signal(s);
    }

    signal(mutex);
}

void requestExit() {
    wait(mutex);
    waitingToExit += 1;
    if (waitingToEnter == 0 && waitingToExit == 1) {
        signal(mutex);
    } else {
        sem &s = sems[tailExit];
        tailExit = N + (tailExit + 1) % N;
        signal(mutex);
        sem(s);
    }
}

void exit() {
    wait(mutex);
    waitingToExit -= 1;
    emptySpace += 1;
    signal(mutex);

    SINGAL();
}

void car() {
    while (true) {
        if (requestEnter()) {
            enter();
            /////////
            requestExit();
            exit();
        }
    }
}
