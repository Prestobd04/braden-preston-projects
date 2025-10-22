#include <iostream>
using namespace std;

const int LENGTH = 20;

template <typename Template>
class OrderedList {
    private:
    Template* data[LENGTH];
    int currentSize;
    public:
    OrderedList() : currentSize(0) {}

    void AddItem(const Template& item) {
        if (currentSize >= 20) {  
            throw "Cannot add item: list is full.";
        }

        Template* newItem = new Template(item);

        int i = 0;
        while (i < currentSize && item > *data[i]) {
            i++;
        }

        for (int j = currentSize; j > i; j--) {
            data[j] = data[j - 1];
        }
        data[i] = newItem;

        currentSize++;
    }

    void RemoveItem(const Template& item) {
        int i;
        for (i = 0; i < currentSize; i++) {
            if (*data[i] == item) break;
        }
        if (i == currentSize) throw "Item not found";

        delete data[i];
        for (int j = i; j < currentSize - 1; j++) data[j] = data[j + 1];
        currentSize--;
    }

    bool IsEmpty() {
        for(int i = 0; i < currentSize; i++){
            if(data[i] != nullptr) return false;
        }
        return true;
    }

    bool IsFull() {
        for(int i = 0; i < LENGTH; i++){
            if(data[i] == nullptr) return false;
        }
        return true;
    }

    void MakeEmpty() {
        for (int i = 0; i < currentSize; i++) {
            delete data[i];
            data[i] = nullptr;
        }
        currentSize = 0;
    }

    void Display() const {
        for (int i = 0; i < currentSize; i++) cout << *data[i] << " ";
        cout << endl;
    }

    ~OrderedList() {
        for (int i = 0; i < currentSize; i++) {
            delete data[i];
        }
    }
};

int main() {
    OrderedList<int> list;

    cout << "Test 1: Empty list check" << endl;
    cout << "IsEmpty() = " << boolalpha << list.IsEmpty() << endl; // true
    cout << "IsFull() = " << boolalpha << list.IsFull() << endl;   // false
    cout << "Display: ";
    list.Display();
    cout << endl;

    cout << "Test 2: Adding items" << endl;
    list.AddItem(5);
    list.AddItem(2);
    list.AddItem(8);
    list.AddItem(3);

    cout << "List contents (should be 2 3 5 8): ";
    list.Display();
    cout << "IsEmpty() = " << list.IsEmpty() << endl;
    cout << "IsFull() = " << list.IsFull() << endl;
    cout << endl;

    cout << "Test 3: MakeEmpty()" << endl;
    list.MakeEmpty();
    cout << "List after MakeEmpty(): ";
    list.Display(); // should show empty
    cout << "IsEmpty() = " << list.IsEmpty() << endl;
    cout << endl;

    cout << "Test 4: Fill to capacity" << endl;
    for (int i = 0; i < LENGTH; i++) {
        list.AddItem(i);
    }
    cout << "IsFull() = " << list.IsFull() << endl; // should be true
    cout << "List contents: ";
    list.Display();
    cout << endl;

    cout << "Test 5: Try adding when full" << endl;
    try {
        list.AddItem(100);
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << endl << "All tests completed successfully!" << endl;
    return 0;
}