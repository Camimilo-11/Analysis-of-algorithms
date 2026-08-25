#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

class MyQueue {
private:
    list<int> data;

public:
    void enqueue(int value) {
        data.push_back(value);
    }

    void dequeue() {
        if (data.empty()) {
            throw runtime_error("Queue is empty, cannot dequeue");
        }
        data.pop_front();
    }

    int front() const {
        if (data.empty()) {
            throw runtime_error("Queue is empty, no front element");
        }
        return data.front();
    }

    bool isEmpty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

int main() {
    MyQueue myQueue;
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);
    cout << "Front: " << myQueue.front() << endl;// 10
    cout << "Size: " << myQueue.size() << endl;  // 3
    myQueue.dequeue();
    cout << "After dequeue, front: " << myQueue.front() << endl; // 20
    cout << "Is empty? " << (myQueue.isEmpty() ? "Yes" : "No") << endl;
    return 0;
}
