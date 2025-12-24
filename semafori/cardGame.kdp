struct Card {
    int number;
    Color color;
};

array<stack<Card>> piles = ...;
array<sem> mutex = {1, 1, 1, 1}; // za svaku gomilu
array<sem> cards = {2, 2, 2, 2}

// 0, 1, 2, 3
// gomila 0 je izmedju igraca 3 i 0
// igrac 1 -> 0, 1
// igrac 2 -> 1, 2
// igrac 3 -> 2, 3
// igrac 4 -> 3, 0
// 0 -> 1 -> 2 -> 3
//
// ostavlja kartu na levu, uzmia kartu sa desne

sem winnerMutex = 1;

int winner = -1;
bool gameOver = false;

void entryProtocol(int leftPileIndex, int rightPileIndex) {
    if (leftPileIndex < rightPileIndex) {
        wait(mutex[leftPileIndex]);
        wait(mutex[rightPileIndex]);
        wait(card[rightPileIndex]);
    } else {
        wait(mutex[rightPileIndex]);
        wait(card[rightPileIndex]);
        wait(mutex[leftPileIndex]);
    }
}

void exitProtocol(int leftPileIndex, int rightPileIndex) {
    signal(cards[leftPileIndex]);
    signal(mutex[rightPileIndex]);
    signal(mtuex[leftPileIndex]);
}

void player(int id) {
    //0, 1, 2, 3

    array<Card> hand = getInitialHand();
    int leftPileIndex = (id + 1) % 4;
    int rightPileIndex = id;

    while (!gameOver) {
        entryProtocol(leftPileIndex, rightPileIndex);

        hand.append(takeCard(piles[rightPileIndex]));
        piles[leftPileIndex].push(removeCard(hand));

        wait(winnerMutex);
        if (hasWinningHand(hand) && !gameOver) {
            winner = id;
            gameOver = true;
        }
        signal(winnerMutex);

        exitProtocol(leftPileIndex, rightPileIndex);
    }
}
