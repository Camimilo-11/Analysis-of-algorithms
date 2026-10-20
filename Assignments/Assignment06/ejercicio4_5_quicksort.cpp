#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cmath>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000};
    const int K = 10;

    std::cout << std::left << std::setw(12) << "Size (N)"
              << std::setw(16) << "Mean Time (ms)"
              << std::setw(16) << "Std Dev (ms)"
              << std::setw(20) << "N*log2(N) Ratio" << "\n";
    std::cout << "----------------------------------------------------------------\n";

    for (int N : sizes) {
        std::vector<double> times;
        std::mt19937 gen(1337);
        std::uniform_int_distribution<int> dis(1, 10000000);

        for (int k = 0; k < K; ++k) {
            std::vector<int> data(N);
            for (int i = 0; i < N; ++i) {
                data[i] = dis(gen);
            }

            auto start = std::chrono::high_resolution_clock::now();
            quickSort(data, 0, N - 1);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duration = end - start;
            times.push_back(duration.count());
        }

        double sum = 0.0;
        for (double t : times) sum += t;
        double mean = sum / K;

        double sq_sum = 0.0;
        for (double t : times) sq_sum += (t - mean) * (t - mean);
        double std_dev = std::sqrt(sq_sum / K);

        double n_log_n = N * (std::log2(N));
        double ratio = (mean / n_log_n) * 1e6;

        std::cout << std::left << std::setw(12) << N
                  << std::setw(16) << std::fixed << std::setprecision(4) << mean
                  << std::setw(16) << std::fixed << std::setprecision(4) << std_dev
                  << std::setw(20) << std::fixed << std::setprecision(4) << ratio << "\n";
    }

    return 0;
}
