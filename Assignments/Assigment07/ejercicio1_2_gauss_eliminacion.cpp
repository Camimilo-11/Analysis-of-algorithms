#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void forwardElimination(std::vector<std::vector<double>>& A, std::vector<double>& b, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        if (maxRow != i) {
            std::swap(A[i], A[maxRow]);
            std::swap(b[i], b[maxRow]);
        }

        for (int j = i + 1; j < n; ++j) {
            if (std::abs(A[i][i]) < 1e-12) continue;
            double factor = A[j][i] / A[i][i];
            A[j][i] = 0.0;
            for (int k = i + 1; k < n; ++k) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }
}

std::vector<double> backSubstitution(const std::vector<std::vector<double>>& U, 
                                     const std::vector<double>& b, 
                                     int n, 
                                     long long& opCount) {
    std::vector<double> x(n, 0.0);
    opCount = 0;
    for (int j = n - 1; j >= 0; --j) {
        double t = 0.0;
        for (int k = j + 1; k < n; ++k) {
            t += U[j][k] * x[k];
            opCount += 2;
        }
        x[j] = (b[j] - t) / U[j][j];
        opCount += 2;
    }
    return x;
}

int main() {
    int n = 3;
    std::vector<std::vector<double>> A = {
        {2.0, -4.0,  1.0},
        {3.0, -1.0,  1.0},
        {1.0,  1.0, -1.0}
    };
    std::vector<double> b = {6.0, 11.0, -3.0};

    std::cout << "Original System A * x = b:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "  [ ";
        for (int j = 0; j < n; ++j) std::cout << std::setw(6) << A[i][j] << " ";
        std::cout << "] [ x" << i + 1 << " ] = [ " << std::setw(6) << b[i] << " ]\n";
    }

    forwardElimination(A, b, n);

    std::cout << "\nAfter Forward Elimination:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "  [ ";
        for (int j = 0; j < n; ++j) std::cout << std::setw(6) << A[i][j] << " ";
        std::cout << "] [ x" << i + 1 << " ] = [ " << std::setw(6) << b[i] << " ]\n";
    }

    long long opCount = 0;
    std::vector<double> x = backSubstitution(A, b, n, opCount);

    std::cout << "\nSolution Vector x:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "  x" << i + 1 << " = " << x[i] << "\n";
    }
    std::cout << "Operations Count: " << opCount << "\n";

    return 0;
}
