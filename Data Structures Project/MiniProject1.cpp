#include <iostream>
#include <cstdlib>
using namespace std;

const int LENGTH = 20;

int randInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// ----------------- Base OrderedList -----------------
template <typename T>
class OrderedList {
protected:
    T* data[LENGTH];
    int currentSize;
public:
    OrderedList() : currentSize(0) {
        for (int i = 0; i < LENGTH; i++) data[i] = nullptr;
    }

    virtual void AddItem(const T& item) {
        T* newItem = new T(item);
    
        int i = 0;
        while (i < currentSize && *data[i] < item) i++;
    
        if (currentSize < LENGTH) {
            // Shift elements right to make space
            for (int j = currentSize; j > i; j--) data[j] = data[j - 1];
            data[i] = newItem;
            currentSize++;
        } else {
            // Full: delete largest and shift
            delete data[LENGTH - 1];
            for (int j = LENGTH - 1; j > i; j--) data[j] = data[j - 1];
            data[i] = newItem;
        }
    }
    

    virtual void RemoveItem(const T& item) {
        int i;
        for (i = 0; i < currentSize; i++) {
            if (data[i] != nullptr && *data[i] == item) break;
        }
        if (i == currentSize) return;

        delete data[i];
        for (int j = i; j < currentSize - 1; j++) data[j] = data[j + 1];
        data[currentSize - 1] = nullptr;
        currentSize--;
    }

    virtual void Display() const {
        for (int i = 0; i < currentSize; i++) cout << *data[i] << " ";
        cout << endl;
    }

    virtual ~OrderedList() {
        for (int i = 0; i < currentSize; i++) delete data[i];
    }
};

// ----------------- OrderedListEnd -----------------
template <typename T>
class OrderedListEnd : public OrderedList<T> {
public:
    void AddItem(const T& item) override {
        T* newItem = new T(item);

        // If full, remove smallest
        if (this->currentSize == LENGTH) {
            delete this->data[0];
            for (int j = 0; j < LENGTH - 1; j++) this->data[j] = this->data[j + 1];
            this->currentSize--;
        }

        int i = this->currentSize - 1;
        while (i >= 0 && *this->data[i] > item) {
            this->data[i + 1] = this->data[i];
            i--;
        }
        this->data[i + 1] = newItem;
        this->currentSize++;
    }

    void Display() const override {
        for (int i = this->currentSize - 1; i >= 0; i--) cout << *this->data[i] << " ";
        cout << endl;
    }
};

// ----------------- OrderedListMiddle -----------------
template <typename T>
class OrderedListMiddle : public OrderedList<T> {
public:
    void AddItem(const T& item) override {
        T* newItem = new T(item);

        // If full, remove largest
        if (this->currentSize == LENGTH) {
            delete this->data[LENGTH - 1];
            this->currentSize--;
        }

        int i = 0;
        while (i < this->currentSize && *this->data[i] < item) i++;

        for (int j = this->currentSize; j > i; j--) this->data[j] = this->data[j - 1];
        this->data[i] = newItem;
        this->currentSize++;
    }

    void RemoveItem(const T& item) override {
        int i;
        for (i = 0; i < this->currentSize; i++) {
            if (*this->data[i] == item) break;
        }
        if (i == this->currentSize) return;

        delete this->data[i];
        for (int j = i; j < this->currentSize - 1; j++) this->data[j] = this->data[j + 1];
        this->data[this->currentSize - 1] = nullptr;
        this->currentSize--;
    }

    void Display() const override {
        for (int i = 0; i < this->currentSize; i++) cout << *this->data[i] << " ";
        cout << endl;
    }
};

// ----------------- Main -----------------
int main() {
    const int NUM_INSERTS = 30;
    const int NUM_REMOVES = 25;

    OrderedList<int> list1;
    OrderedListEnd<int> list2;
    OrderedListMiddle<int> list3;

    int items[NUM_INSERTS];

    cout << "Adding items:\n";
    for (int i = 0; i < NUM_INSERTS; i++) {
        items[i] = randInt(0, 100);
        list1.AddItem(items[i]);
        list2.AddItem(items[i]);
        list3.AddItem(items[i]);
    }

    cout << "List1: "; list1.Display();
    cout << "List2: "; list2.Display();
    cout << "List3: "; list3.Display();

    cout << "\nRemoving items:\n";
    for (int i = 0; i < NUM_REMOVES; i++) {
        int idx = randInt(0, NUM_INSERTS - 1);
        list1.RemoveItem(items[idx]);
        list2.RemoveItem(items[idx]);
        list3.RemoveItem(items[idx]);
    }

    cout << "After removals:\n";
    cout << "List1: "; list1.Display();
    cout << "List2: "; list2.Display();
    cout << "List3: "; list3.Display();

    return 0;
}
