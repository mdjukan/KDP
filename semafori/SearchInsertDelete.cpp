// search
// insert
// delete

int serach_count = 0;
int insert_count = 0;
int delete_count = 0;

sem serachAccess = 0;
sem insertAccess = 0;
sem deleteAccess = 0;

sem mutex = 1;
list<char> requests = {};

void search() {
    wait(mutex);
    requests.append('S');
    signal(mutex);

    SIGNAL();

    wait(searchAccess);

    searchList();

    wait(mutex);
    search_count -= 1;
    signal(mutex);

    SIGNAL();
}

void insert() {
    wait(mutex);
    requests.append('I');
    signal(mutex);

    SIGNAL();

    wait(insertAccess);

    insertIntoList();

    wait(mutex);
    insert_count -= 1;
    signal(mutex);

    SIGNAL();
}

void delete() {
    wait(mutex);
    requests.append('D');
    signal(mutex);

    SIGNAL();

    wait(delteAccess);

    deleteFromList();

    wait(mutex);
    delete_count -= 1;
    signal(mutex);

    SIGNAL();
}

void SIGNAL() {
    wait(mutex);
    if (requests.empty()) {
        signal(mutex);
        return;
    }

    if (requests.front() == 'S') {
        if (delete_count == 0) {
            signal(serachAccess);
            serach_count += 1;
        }
    }

    if (requests.front() == 'I') {
        if (delete_count == 0 && insert_count == 0) {
            signal(insertAccess);
            insert_count += 1;
        }
    }

    if (requests.front() == 'D') {
        if (delete_count == 0 && insert_count == 0 &&
        serach_count == 0) {
            signal(deleteAccess);
            delete_count += 1;
        }
    }

    signal(mutex);
}


/////////////////////////// NO LIST //////////////////////

// search
// insert
// delete

int serach_count = 0;
int insert_count = 0;
int delete_count = 0;

sem serachAccess = 0;
sem insertAccess = 0;
sem deleteAccess = 0;

sem mutex = 1;
int waiting_to_search = 0;
int waiting_to_insert = 0;
int waiting_to_delete = 0;

void search() {
    wait(mutex);
    waiting_to_search += 1;
    signal(mutex);

    SIGNAL();

    wait(searchAccess);

    searchList();

    wait(mutex);
    search_count -= 1;
    signal(mutex);

    SIGNAL();
}

void insert() {
    wait(mutex);
    waiting_to_insert += 1;
    signal(mutex);

    SIGNAL();

    wait(insertAccess);

    insertIntoList();

    wait(mutex);
    insert_count -= 1;
    signal(mutex);

    SIGNAL();
}

void delete() {
    wait(mutex);
    waiting_to_delete += 1;
    signal(mutex);

    SIGNAL();

    wait(delteAccess);

    deleteFromList();

    wait(mutex);
    delete_count -= 1;
    signal(mutex);

    SIGNAL();
}

void SIGNAL() {
    wait(mutex);
    if (waiting_to_search + waiting_to_insert + waiting_to_delete == 0) {
        signal(mutex);
        return;
    }

    if (waiting_to_delete > 0) {
        if (delete_count == 0 && insert_count == 0 &&
        serach_count == 0) {
            signal(deleteAccess);
            delete_count += 1;
            waiting_to_delete -= 1;
        }
    } else {
        if (waiting_to_search > 0) {
            if (delete_count == 0) {
                signal(serachAccess);
                serach_count += 1;
                waiting_to_search -= 1;
            }
        }

        if (waiting_to_insert > 0 && insert_count == 0) {
            signal(insertAccess);
            insert_count += 1;
            waiting_to_insert -= 1;
        }
    }

    signal(mutex);
}
