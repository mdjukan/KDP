////////////////////// TRIK ////////////////////

int reader_count = 0;
sem enter = 1;
sem mutexR = 1;
sem RW = 1;

void read() {
    wait(enter);
    wait(mutexR);
    reader_count += 1;
    if (reader_count == 1) {
        wait(RW);
    }
    signal(mutexR);
    signal(enter);

    READ();

    wait(mutexR);
    reader_count -= 1;
    if (reader_count == 0) {
        signal(RW);
    }
    signal(mutexR);
}

void write() {
    wait(enter);
    wait(RW);
    signal(enter);
    WRITE();
    signal(RW);
}


//////////////////// SABLON  /////////////////////////////

int reader_count = 0;
int writer_count = 0;

sem readAccess = 0;
sem writeAccess = 0;

sem mutex = 1;
list<char> requests = {};

void read() {
    wait(mutex);
    requests.append('R');
    signal(mutex);

    SINGAL();

    wait(readAccess);

    READ();

    wait(mutex);
    reader_count -= 1;
    signal(mutex);

    SIGNAL();
}

void write() {
    wait(mutex);
    requests.append('W');
    signal(mutex);

    SINGAL();

    wait(writeAccess);

    WRITE();

    wait(mutex);
    writer_count -= 1;
    signal(mutex);

    SIGNAL();
}

void SIGNAL() {
    wait(mutex);
    if (requests.empty()) {
        signal(mutex);
        return;
    }

    if (requests.front() == 'R') {
        if (writer_count == 0) {
            signal(readAccess);
            reader_count += 1;
        }
    }

    if (requests.front() == 'W') {
        if (writer_count == 0 && reader_count == 0) {
            signal(writeAccess);
            writer_count += 1;
        }
    }

    signal(mutex);
}

//////////////////// SABLON - bez list  ///////////////////
int reader_count = 0;
int writer_count = 0;

sem readAccess = 0;
sem writeAccess = 0;

sem mutex = 1;
int waiting_to_read = 0;
int waiting_to_write = 0;

void read() {
    wait(mutex);
    waiting_to_read += 1;
    signal(mutex);

    SINGAL();

    wait(readAccess);

    READ();

    wait(mutex);
    reader_count -= 1;
    signal(mutex);

    SIGNAL();
}

void write() {
    wait(mutex);
    waiting_to_write += 1;
    signal(mutex);

    SINGAL();

    wait(writeAccess);

    WRITE();

    wait(mutex);
    writer_count -= 1;
    signal(mutex);

    SIGNAL();
}

void SIGNAL() {
    wait(mutex);
    if (waiting_to_read + waiting_to_write == 0) {
        signal(mutex);
    }

    if (waiting_to_write > 0) {
        if (writer_count == 0 && reader_count == 0) {
            signal(writeAccess);
            writer_count += 1;
            waiting_to_write -= 1;
        }
    } else if (waiting_to_read > 0) {
        if (writer_count == 0) {
            signal(readAccess);
            reader_count += 1;
            waiting_to_read -= 1;
        }
    }

    signal(mutex);
}
