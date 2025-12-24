sem firstReadValue = 0, secondArrived = 0;
sem mutex = 1;
int buffer[2];
int k = 0;

int swap(int val) {
    wait(mutex);
    if (k == 0) {
        buffer[k++] = val;
        signal(mutex);
        wait(secondArrived);
        int retVal = buffer[1];
        signal(firstReadValue);
    } else {
        int retVal = buffer[0];
        buffer[k] = val;
        k = 0;
        signal(secondArrived);
        wait(firstReadValue);
        signal(mutex);
    }

    return retVal;
}
