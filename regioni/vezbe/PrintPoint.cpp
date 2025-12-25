const int n;
pair<int,int> pt;
bool empty = true;

void write() {
    for (int i = 0; i < n; i++) {
        region (pt) {
            await(empty);
            pt.first = i;
            pt.second = i*i;
            empty = false;
        }
    }
}

void print() {
    for (int i = 0; i < n; i++) {
        region (pt) {
            await(!empty);
            cout << "(" << pt.first << ", ";
            cout << pt.second << ")" << endl;
            empty = true;
        }
    }
}
