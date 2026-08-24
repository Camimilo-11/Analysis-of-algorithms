#include <iostream>
using namespace std;

int euclidGCD(int m, int n) {
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int main() {
    int a = 60, b = 24;
    cout << "MCD(" << a << ", " << b << ") = " << euclidGCD(a, b) << endl;
    return 0;
}
