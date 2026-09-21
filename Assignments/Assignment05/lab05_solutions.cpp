/*
 *Camilo Vasquez
 * Problem 1 -Insertion Sort for Characters)
 * Problem 2 -Binary Search vs Interpolation Search with 10M elements
 */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <iomanip>

// PROBLEM 1: Insertion Sort for Alphabetic Characters

void insertionSort(std::vector<char>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        char key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void runProblem1() {
    std::cout << "PROBLEM 1: Insertion Sort for Alphabetic Characters\n";
    const int N = 20;
    std::vector<char> characters(N);
    
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::uniform_int_distribution<> dis(0, 51);
    
    for (int i = 0; i < N; ++i) {
        int r = dis(gen);
        characters[i] = (r < 26) ? ('A' + r) : ('a' + (r - 26));
    }
    
    std::cout << "Original Random Array (N = 20):\n";
    for (char c : characters) std::cout << c << " ";
    std::cout << "\n\n";
    
    insertionSort(characters);
    
    std::cout << "Sorted Array (Insertion Sort):\n";
    for (char c : characters) std::cout << c << " ";
    std::cout << "\n\n";
}

// PROBLEM 2: Binary Search vs Interpolation Search 10,000,000 elements

int binarySearch(const std::vector<int>& arr, int key) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == key) return m;
        if (key < arr[m]) r = m - 1;
        else l = m + 1;
    }
    return -1;
}

int interpolationSearch(const std::vector<int>& arr, int key) {
    int l = 0, r = arr.size() - 1;
    while (l <= r && key >= arr[l] && key <= arr[r]) {
        if (l == r) return (arr[l] == key) ? l : -1;
        
        int pos = l + static_cast<long long>(key - arr[l]) * (r - l) / (arr[r] - arr[l]);
        
        if (arr[pos] == key) return pos;
        if (arr[pos] < key) l = pos + 1;
        else r = pos - 1;
    }
    return -1;
}

void runProblem2() {
    std::cout << "PROBLEM 2: Binary Search vs Interpolation Search\n";
    
    const int N = 10000000; // 10 million elements
    std::cout << "Generating " << N << " random integers...\n";
    
    std::vector<int> data(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dis(1, 100000000);
    
    for (int i = 0; i < N; ++i) {
        data[i] = dis(gen);
    }
    
    std::cout << "Sorting array (required precondition)...\n";
    std::sort(data.begin(), data.end());
    
    int targetKey = data[N / 2]; // Target key in the middle
    
    // Benchmark Binary Search
    auto startBS = std::chrono::high_resolution_clock::now();
    int idxBS = binarySearch(data, targetKey);
    auto endBS = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationBS = endBS - startBS;
    
    // Benchmark Interpolation Search
    auto startIS = std::chrono::high_resolution_clock::now();
    int idxIS = interpolationSearch(data, targetKey);
    auto endIS = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationIS = endIS - startIS;
    
    std::cout << "\nA BENCHMARK RESULTS \n";
    std::cout << "Binary Search:        Index = " << idxBS 
              << " | Time: " << durationBS.count() << " ns\n";
    std::cout << "Interpolation Search: Index = " << idxIS 
              << " | Time: " << durationIS.count() << " ns\n\n";
}

int main() {
    runProblem1();
    runProblem2();
    return 0;
}
