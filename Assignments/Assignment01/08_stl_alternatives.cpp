#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main() {
    stack<int> myStack;
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    cout << "std::stack top: " << myStack.top() << endl; // 30
    myStack.pop();
    cout << "After pop, top: " << myStack.top() << endl; // 20
    cout << "Stack size: " << myStack.size() << endl;
    cout << "-----" << endl;
    queue<int> myQueue;
    myQueue.push(10);
    myQueue.push(20);
    myQueue.push(30);
    cout << "std::queue front: " << myQueue.front() << endl; // 10
    cout << "std::queue back: " << myQueue.back() << endl;   // 30
    myQueue.pop();
    cout << "After pop, front: " << myQueue.front() << endl; // 20
    cout << "Queue size: " << myQueue.size() << endl;
    return 0;
}
