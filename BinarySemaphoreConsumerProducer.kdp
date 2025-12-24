const int N;


sem mutex_consumer = 1; // stiti ridx
sem mutex_producer = 1; // stiti widx
Item buffer[N];
int item_count = 0;
int ridx = 0, widx = 0;

sem buffer_has_items = 0; // 1 kada u baferu postoji bar jedan item
sem buffer_has_free_slot = 1; // 1 kada u baferu postoji bar jedno prazno mesto

void consumer() {
    while (true) {
        wait(buffer_has_items);
        Item item = buffer[ridx];
        ridx = (ridx + 1) % N;

        if (item_count == N) {
            signal(buffer_has_free_slot);
        }

        item_count -= 1;

        if (item_count > 0) {
            signal(buffer_has_items);
        }
    }
}

void producer() {
    while (true) {
        wait(buffer_has_free_slot);
        buffer[widx] = producteItem();
        widx = (widx + 1) % N;

        if (item_count == 0) {
            signal(buffer_has_items);
        }

        item_count += 1;

        if (item_count < N) {
            signal(buffer_has_free_slot);
        }
    }
}
