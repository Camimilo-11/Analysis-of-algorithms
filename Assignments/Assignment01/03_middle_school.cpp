#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<int, int> primeFactorization(int n, const vector<int>& primes) {
    map<int, int> factors;
    for (int p : primes) {
        if (p * p > n) break;
        while (n % p == 0) {
            factors[p]++;
            n /= p;
        }
    }
    if (n > 1) factors[n]++; // el número tiene un factor primo mayor que sqrt original
    return factors;
}

int middleSchoolGCD(int m, int n) {
    int maxNum = max(m, n);
    vector<int> primes = sieveOfEratosthenes(maxNum);

    map<int, int> factorsM = primeFactorization(m, primes);
    map<int, int> factorsN = primeFactorization(n, primes);

    int gcd = 1;
    for (auto& [prime, expM] : factorsM) {
        if (factorsN.count(prime)) {
            int minExp = min(expM, factorsN[prime]);
            for (int i = 0; i < minExp; i++) gcd *= prime;
        }
    }
    return gcd;
}

int main() {
    int a = 60, b = 24;
    cout << "MCD(" << a << ", " << b << ") = " << middleSchoolGCD(a, b) << endl;
    return 0;
}
