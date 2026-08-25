#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    cout << "Front of queue: " << myList.front() << endl; // 10
    myList.pop_front(); // removes 10 
    cout << "After dequeue, front: " << myList.front() << endl; // 20
    myList.pop_front();
    myList.pop_front();
    cout << "Is empty? " << (myList.empty() ? "Yes" : "No") << endl;
    return 0;
}
