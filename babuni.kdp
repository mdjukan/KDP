const int K;

struct Request {
    RequestType type; // L ili R
    sem *s;
};

sem mutex = 1;
list<Request> requests = {}; // L - left, R - right
int leftCount = 0, rightCount = 0;

void crossTheBridge(int side) { // L ili R
    sem s = 0;

    wait(mutex);
    if (requests.empty()) {
        signal(s);
    } else {
        requests.append(Request{side, &s});
    }
    signal(mutex);
    wait(s);
    SIGNAL();

    corossingTheBridge();

    wait(mutex);
    if (side == L) {
        leftCount -= 1;
    } else {
        rightCount -= 1;
    }
    signal(mutex);

    SIGNAL();
}

void SIGNAL() {
    wait(mutex);
    if (!requests.empty() && requests.front().type == L) {
        if (leftCount < K && rightCount == 0) {
            sem *s = requests.front().s;
            requests.pop_front();
            leftCount += 1;
            signal(*s);
        }
    }

    if (!requests.empty() && requests.front().type == R) {
        if (leftCount == 0 && rightCount < K) {
            sem *s = requests.front().s;
            requests.pop_front();
            rightCount += 1;
            signal(*s);
        }
    }

    signal(mutex);
}


