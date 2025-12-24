int raindearCount = 0;
sem raindear[9] = {0};

sem gnome[10] = {0};
sem enterGnome = 3;
int gnome_ids[3] = {-1};
int gnomeCount = 0;

sem mutex = 1;
bool santaActive = false;

void SIGNAL() {
    wait(mutex);
    if (!santaActive) {
        if (ranidearCount == 9) {
            santaActive = true;
            signal(raindearSem[0]);
            signal(sleep);
        } else if (!gnomeBatch.empty()) {
            int firstGnomeId = gnomeBatch.front();
            gnomeBatch.pop_foront();
            santaActive = true;
            signal(gnomeSem[firstGnomeId]);
            signal(sleep);
        }
    } 
    signal(mutex);
}

list<int> gnomeBatch = {}; // id vodeceg
sem door1 = 1, door2 = 0;
void gnome(int id) {
    wait(door1);
    gnome_ids[gnomeCount ++] = id;
    if (gnomeCount == 3) {
        signal(door2);
    } else {
        signal(door1);
    }

    wait(door2);
    int id0 = gnome_ids[0];
    int id1 = gnome_ids[1];
    int id2 = gnome_ids[2];

    if (id == id0) { 
        gnomeBatch.append(id);
    }

    gnomeCount --;
    if (gnomeCount == 0) {
        signal(door1);
    } else {
        signal(door2);
    }

    SIGNAL();

    if (id == id0) {
        wait(gnomeSem[id]);
        wait(enter);
        signal(gnomeSem[id1]);
    } else (id == id1) {
        wait(gnomeSem[id]);
        signal(gnomeSem[id2]);
    } else {
        wait(id2);
        signal(confirm);
    }

    ///////////// JOINED SANTA /////////////
    if (id == id0) {
        wait(exit);
        signal(gnomeSem[id1]);
    } else (id == id1) {
        wait(gnomeSem[id]);
        signal(gnomeSem[id2]);
    } else {
        wait(id2);
        wait(mutex);
        santaActive = false;
        signal(mutex);
        SIGNAL();
    }
}

void ranidear(int id) {
    wait(mutex);
    raindearCount += 1;
    signal(mutex);

    SINGAL();

    if (id == 0) {
        wait(rainderSem[0]);
        wait(enter);
        signal(raindearSem[1]);
    } else if (id < 8) {
        wait(raindearSem[id]);
        signal(raindearSem[id+1]);
    } else {
        wait(raindearSem[id]);
        signal(confirm);
    }

    /////////////// JOINED SANTA //////////////

    if (id == 0) {
        wait(exit);
        signal(raindearSem[1]);
    } else if (id < 8) {
        wait(raindearSem[id]);
        signal(raindearSem[id+1]);
    } else {
        wait(raindearSem[id]);
        wait(mutex);
        santaActive = false;
        ranidearCount = 0;
        signal(mutex);
        SIGNAL();
    }
}

void santa() {
    while (true) {
        wait(sleep);
        signal(enter);
        wait(confirm);
        if (indication == 0) {
            ride();
        } else {
            talk();
        }
        signal(exit);
    }
}
