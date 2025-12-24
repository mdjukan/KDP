struct Request {
    RequestType type; // READ ili WRITE
    sem *s;
};

const int N;
sem enter = N;

sem mutex = 1;
list<Request> requests = {};

int readerCount = 0, writerCount = 0;

void SIGNAL() {
    wait(mutex);
    if (!requests.empty() && requests.front().type == READ) {
        if (writerCount == 0) {
            readerCount += 1;
            Request req = requests.front();
            req.pop_front();
            signal(*(req.s));
        }
    }

    if (!requests.empty() && requests.front().type == WRITE) {
        if (readerCount == 0 && writerCount == 0) {
            writerCount += 1;
            Request req = requests.front();
            req.pop_front();
            signal(*(req.s));
        }
    }

    signal(mutex);
}

void makeReadRequest() {
    sem s = 0;

    wait(enter);
    wait(mutex);
    requests.append(Request{READ, &s});
    signal(mutex);

    SIGNAL(); 
    wait(s);
    signal(enter);
    SIGNAL();
}

void readOver() {
    wait(mutex);
    readerCount -= 1;
    signal(mutex);

    SIGNAL();
}

void makeWriteRequest() {
    sem s = 0;

    wait(enter);
    wait(mutex);
    requests.append(Request{WRITE, &s});
    signal(mutex);

    SIGNAL();
    wait(s);
    signal(enter);
}

void writeOver() {
    wait(mutex);
    writerCount -= 1;
    signal(mutex);

    SIGNAL();
}

// makeReadRequest();
// ....
// readOver();
