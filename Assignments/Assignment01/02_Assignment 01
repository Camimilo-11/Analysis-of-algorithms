#include <vector>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isComposite(n + 1, false);
    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (!isComposite[p]) {
            primes.push_back(p);
            for (int multiple = p * p; multiple <= n; multiple += p) {
                isComposite[multiple] = true;
            }
        }
    }
    return primes;
}
