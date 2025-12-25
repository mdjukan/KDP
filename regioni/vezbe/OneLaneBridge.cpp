
struct Bridge {
    int north_count;
    int south_count;
};

Bridge B = {0, 0};

void north() {
    region (B) {
        await(B.south_count == 0);
        B.north_count += 1;
    }

    CrossTheBridge();

    region (B) {
        B.north_count -= 1;
    }
}

void south() {
    region (B) {
        await(B.north_count == 0);
        B.south_count += 1;
    }

    CrossTheBridge();

    region (B) {
        B.south_count -= 1;
    }
}

/////////////////////// WITH LIMIT /////////////////////////////////

const int L = 10; // limit

struct Bridge {
    int north_crossing; // koliko ih ne mostu
    int south_crossing;

    int north_crossed;
    int south_crossed;

    int north_waiting;
    int south_waiting;
};

Bridge B = {0, 0};

void north() {
    region (B) {
        B.north_waiting += 1;
        await(B.south_crossing == 0 && B.north_crossed < L);

        B.north_waiting -= 1;
        B.north_crossing += 1;
        if (B.south_waiting > 0) {
            B.north_crossed += 1;
        }
    }

    CrossTheBridge();

    region (B) {
        B.north_crossing -= 1;
        if (B.north_crossing == 0) {
            B.south_crossed = 0;
        }
    }
}

void south() {
    region (B) {
        B.south_waiting += 1;
        await(B.north_crossing == 0 && B.south_crossed < L);

        B.south_waiting -= 1;
        B.south_crossing += 1;
        if (B.north_waiting > 0) {
            B.south_crossed += 1;
        }
    }

    CrossTheBridge();

    region (B) {
        B.south_crossing -= 1;
        if (B.south_crossing == 0) {
            B.north_crossed = 0;
        }
    }
}

/// N . . .. 
/// S . .. . . .
/// [N]
/// N_crossed 1, 2, ..., L -> 0
/////////// izgladnjinje jednih ili drugih /////////////
/// S_crossed 1, 2, ..., L
