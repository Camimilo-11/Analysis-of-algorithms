#include <iostream>

void swapArithmetic(int& u, int& v) {
    u = u + v;
    v = u - v;
    u = u - v;
}

int main() {
    int u = 15, v = 42;
    std::cout << "Antes: u = " << u << ", v = " << v << "\n";
    swapArithmetic(u, v);
    std::cout << "Despues: u = " << u << ", v = " << v << "\n";
    return 0;
}
