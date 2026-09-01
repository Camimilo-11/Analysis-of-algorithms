#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

void generateLCG(long long n, unsigned long long m, unsigned long long seed,
                  unsigned long long a, unsigned long long b, vector<unsigned long long>& out) {
    unsigned long long r = seed;
    out.resize(n);
    for (long long i = 0; i < n; i++) {
        r = (a * r + b) % m;
        out[i] = r;
    }
}

int main() {
    unsigned long long m = 1ULL << 31; 
    unsigned long long a = (unsigned long long)(0.5 * m) | 1; 
    unsigned long long b = 1;
    unsigned long long seed = 123456789ULL;

    cout << "n\ttime_ms\n";
    vector<long long> sizes = {100000, 200000, 400000, 800000, 1600000, 3200000,
                                6400000, 12800000, 25600000, 51200000, 102400000};
    vector<double> times;
    for (long long n : sizes) {
        vector<unsigned long long> out;
        auto t1 = high_resolution_clock::now();
        generateLCG(n, m, seed, a, b, out);
        auto t2 = high_resolution_clock::now();
        double ms = duration<double, milli>(t2 - t1).count();
        times.push_back(ms);
        cout << n << "\t" << fixed << setprecision(4) << ms << "\n";
    }

    cout << "\nn\tratio t(2n)/t(n)\n";
    for (size_t i = 1; i < times.size(); i++) {
        cout << sizes[i] << "\t" << fixed << setprecision(3) << times[i] / times[i-1] << "\n";
    }
    return 0;
}
