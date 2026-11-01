class MyHashSet {
    vector<list<int>> buckets;
    int size = 1009;

public:
    MyHashSet() {
        buckets.resize(size);
    }

    void add(int key) {
        int idx = key % size;

        for (int x : buckets[idx]) {
            if (x == key) return;
        }

        buckets[idx].push_back(key);
    }

    void remove(int key) {
        int idx = key % size;
        buckets[idx].remove(key);
    }

    bool contains(int key) {
        int idx = key % size;

        for (int x : buckets[idx]) {
            if (x == key) return true;
        }

        return false;
    }
};