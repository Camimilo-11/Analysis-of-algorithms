#include <iostream>
#include <vector>
#include <string>

struct Element {
    int key;
    std::string label;
    int original_index;
};

void merge(std::vector<Element>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Element> L(n1);
    std::vector<Element> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].key <= R[j].key) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Element>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<Element> arr = {
        {5, "A1", 0},
        {2, "B1", 1},
        {5, "A2", 2},
        {1, "C1", 3},
        {5, "A3", 4},
        {2, "B2", 5}
    };

    std::cout << "Original Array:\n";
    for (const auto& elem : arr) {
        std::cout << "[" << elem.key << ", " << elem.label << ", Idx:" << elem.original_index << "] ";
    }
    std::cout << "\n\n";

    mergeSort(arr, 0, static_cast<int>(arr.size()) - 1);

    std::cout << "Sorted Array (Merge Sort):\n";
    for (const auto& elem : arr) {
        std::cout << "[" << elem.key << ", " << elem.label << ", Idx:" << elem.original_index << "] ";
    }
    std::cout << "\n";

    return 0;
}
