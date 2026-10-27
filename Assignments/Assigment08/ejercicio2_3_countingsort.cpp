#include <iostream>
#include <vector>

void comparisonCountingSort(const std::vector<int>& A, std::vector<int>& S) {
    int n = A.size();
    std::vector<int> Count(n, 0);
    S.resize(n);

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (A[i] < A[j]) {
                Count[j]++;
            } else {
                Count[i]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        S[Count[i]] = A[i];
    }
}

void distributionCountingSort(const std::vector<int>& A, std::vector<int>& S, int l, int u) {
    int n = A.size();
    int k = u - l + 1;
    std::vector<int> D(k, 0);
    S.resize(n);

    for (int i = 0; i < n; ++i) {
        D[A[i] - l]++;
    }

    for (int j = 1; j < k; ++j) {
        D[j] += D[j - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        int j = A[i] - l;
        S[D[j] - 1] = A[i];
        D[j]--;
    }
}

int main() {
    std::vector<int> A = {13, 11, 12, 13, 12, 10, 11};
    std::vector<int> S_comp, S_dist;

    comparisonCountingSort(A, S_comp);
    distributionCountingSort(A, S_dist, 10, 13);

    std::cout << "Original: ";
    for (int x : A) std::cout << x << " ";
    std::cout << "\nComparisonCountingSort: ";
    for (int x : S_comp) std::cout << x << " ";
    std::cout << "\nDistributionCountingSort: ";
    for (int x : S_dist) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
