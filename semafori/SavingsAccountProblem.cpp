struct Item {
    int amount;
    sem *s;
};

struct Account {
    sem mutex = 1;
    int balance = ...;
    list<Item> waiting = {};
};

const int N;
Account accound[N];

void deposit(int amount, int acc_id) {
    Account &acc = accounts[acc_id];
    wait(acc.mutex);
    acc.balance += amount;

    while (!acc.waiting.empty() && (acc.waiting.front().amount <= acc.balance) {
         acc.balance -= acc.waiting.front().amount;
         signal(*(acc.waiting.front().s));
         acc.waiting.pop_front();
    }

    signal(mutex);
}

void withdraw(int amount, int acc_id) {
    Account &acc = accounts[acc_id];
    wait(acc.mutex);

    if (acc.amount > acc.balance) {
        sem s = 0;
        acc.waiting.append(Item{amount, &s});
        signal(acc.mutex);
        wait(s);
    } else {
        acc.balance -= acc.amount;
        signal(mutex);
    }
}
