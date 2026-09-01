#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long moveCountRec = 0;

void hanoiRecursive(int n, int from, int to, int aux) {
    if (n == 0) return;
    hanoiRecursive(n - 1, from, aux, to);
    moveCountRec++;
    hanoiRecursive(n - 1, aux, to, from);
}

long long hanoiIterative(int n) {
    vector<stack<int>> peg(3);
    for (int i = n; i >= 1; i--) peg[0].push(i);
    long long totalMoves = (1LL << n) - 1;
    int smallest = 0;
    long long moveCount = 0;

    for (long long m = 1; m <= totalMoves; m++) {
        moveCount++;
        if (m % 2 == 1) {
            int next = (n % 2 == 0) ? (smallest + 1) % 3 : (smallest + 2) % 3;
            peg[next].push(peg[smallest].top());
            peg[smallest].pop();
            smallest = next;
        } else {
            int a = -1, b = -1;
            for (int i = 0; i < 3; i++) if (i != smallest) { if (a == -1) a = i; else b = i; }
            if (peg[a].empty()) swap(a, b);
            else if (!peg[b].empty() && peg[b].top() < peg[a].top()) swap(a, b);
            peg[b].push(peg[a].top());
            peg[a].pop();
        }
    }


    bool ok = false;
    int targetSize = (n % 2 == 0) ? 1 : 2; 
    for (int p = 0; p < 3; p++) {
        if ((int)peg[p].size() == n) {
            stack<int> tmp = peg[p];
            bool sorted = true;
            int prev = 0;
            vector<int> vals;
            while (!tmp.empty()) { vals.push_back(tmp.top()); tmp.pop(); }
            for (size_t i = 1; i < vals.size(); i++) if (vals[i] < vals[i-1]) sorted = false;
            if (sorted) { ok = true; break; }
        }
    }
    if (!ok) { cerr << "ERROR: iterative result incorrect for n=" << n << endl; }
    return moveCount;
}

int main() {
    cout << "n\trec_moves\titer_moves\t2^n-1\trec_time_ms\titer_time_ms\n";
    for (int n = 1; n <= 24; n++) {
        moveCountRec = 0;
        auto t1 = high_resolution_clock::now();
        hanoiRecursive(n, 0, 2, 1);
        auto t2 = high_resolution_clock::now();
        double recTime = duration<double, milli>(t2 - t1).count();

        auto t3 = high_resolution_clock::now();
        long long iterMoves = hanoiIterative(n);
        auto t4 = high_resolution_clock::now();
        double iterTime = duration<double, milli>(t4 - t3).count();

        long long expected = (1LL << n) - 1;
        cout << n << "\t" << moveCountRec << "\t\t" << iterMoves << "\t\t"
             << expected << "\t" << fixed << setprecision(4) << recTime
             << "\t\t" << iterTime << "\n";
    }
    return 0;
}
