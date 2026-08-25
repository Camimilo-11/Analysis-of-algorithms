#include <iostream>
#include <list>
#include <stdexcept>
using namespace std;

class MyStack {
private:
    list<int> data;

public:
    void push(int value) {
        data.push_back(value);
    }

    void pop() {
        if (data.empty()) {
            throw runtime_error("Stack is empty, cannot pop");
        }
        data.pop_back();
    }

    int top() const {
        if (data.empty()) {
            throw runtime_error("Stack is empty, no top element");
        }
        return data.back();
    }

    bool isEmpty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

int main() {
    MyStack myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    cout << "Top: " << myStack.top() << endl;        // 30
    cout << "Size: " << myStack.size() << endl;       // 3

    myStack.pop();
    cout << "After pop, top: " << myStack.top() << endl; // 20

    cout << "Is empty? " << (myStack.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
