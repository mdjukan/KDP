// 0, 1
//
// ///////////////// FIFO QUEUE /////////////////////

sem mutex = 1;
bool free[2] = {true, true};
int free_count = 2; // 0, 1, 2

list<sem*> requests;

int request() { // vraca id semafora
    sem s = 0;
    wait(mutex);
    if (requests.empty() && free_count > 0) {
        signal(s);
        free_count -= 1;
    } else {
        requests.append(&s);
    }
    signal(mutex);

    wait(s);

    wait(mutex);
    int printer_id = -1;
    if (free[0]) {
        printer_id = 0;
        free[0] = false;
    } else {
        printer_id = 1;
        free[1] = false;
    }
    signal(mutex);

    return printer_id;
}


void realease(int printer_id) {
    wait(mutex);
    free[printer_id] = true;
    if (requests.empty()) {
        free_count += 1;
    } else {
        sem *s = requests.front();
        requests.pop_front();
        signal(*s);
    }
    signal(mutex);
}


/////////////////// PRIORITY QUEUE ////////////////
// 0, 1

sem mutex = 1;
bool free[2] = {true, true};
int free_count = 2; // 0, 1, 2

vector<pair<sem*, int>> requests;
// (sem, prior.)

int request(int priority) { // vraca id semafora
    sem s = 0;
    wait(mutex);
    if (requests.empty() && free_count > 0) {
        signal(s);
        free_count -= 1;
    } else {
        requests.push_back({&s, priority});
    }
    signal(mutex);

    wait(s);

    wait(mutex);
    int printer_id = -1;
    if (free[0]) {
        printer_id = 0;
        free[0] = false;
    } else {
        printer_id = 1;
        free[1] = false;
    }
    signal(mutex);

    return printer_id;
}


void realease(int printer_id) {
    wait(mutex);
    free[printer_id] = true;
    if (requests.empty()) {
        free_count += 1;
    } else {
        int max_priority_index = 0;
        for (int i = 1; i < requests.size(); i++) {
            if (requests[i].second > 
            requests[max_priority_index].second) {
                max_priority_index = i;
            }
        }

        sem *s = requests[max_priority_index].first;
        requests.erase(requests.begin() + max_priority_index);
        signal(*s);
    }
    signal(mutex);
}
