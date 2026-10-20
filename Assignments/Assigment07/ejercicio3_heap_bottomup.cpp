#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeapBottomUp(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
}

int main() {
    std::vector<int> smallArr = {2, 9, 7, 6, 5, 8};
    std::cout << "Original Array: ";
    for (int v : smallArr) std::cout << v << " ";
    std::cout << "\n";

    buildHeapBottomUp(smallArr);

    std::cout << "Max-Heap Array: ";
    for (int v : smallArr) std::cout << v << " ";
    std::cout << "\n\n";

    const int K = 10;
    std::vector<int> sizes = {1000, 10000, 100000, 1000000, 5000000};
    
    std::cout << std::left << std::setw(12) << "Size (N)"
              << std::setw(18) << "Mean Time (ms)"
              << std::setw(18) << "Std Dev (ms)"
              << std::setw(18) << "Time/N Ratio" << "\n";
    std::cout << "----------------------------------------------------------------\n";

    std::mt19937 gen(42);
    for (int N : sizes) {
        std::vector<double> trialTimes(K);
        for (int k = 0; k < K; ++k) {
            std::vector<int> arr(N);
            std::uniform_int_distribution<int> dis(1, 10000000);
            for (int i = 0; i < N; ++i) arr[i] = dis(gen);

            auto start = std::chrono::high_resolution_clock::now();
            buildHeapBottomUp(arr);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> elapsed = end - start;
            trialTimes[k] = elapsed.count();
        }

        double sum = 0.0;
        for (double t : trialTimes) sum += t;
        double mean = sum / K;

        double sqDiffSum = 0.0;
        for (double t : trialTimes) sqDiffSum += (t - mean) * (t - mean);
        double stdDev = std::sqrt(sqDiffSum / K);

        double ratio = mean / N;

        std::cout << std::left << std::setw(12) << N
                  << std::setw(18) << std::fixed << std::setprecision(4) << mean
                  << std::setw(18) << std::fixed << std::setprecision(4) << stdDev
                  << std::setw(18) << std::scientific << std::setprecision(4) << ratio << "\n";
    }

    return 0;
}
