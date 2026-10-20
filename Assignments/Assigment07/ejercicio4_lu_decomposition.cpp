#include <iostream>
#include <vector>
#include <iomanip>

void luDecomposition(const std::vector<std::vector<double>>& A,
                     std::vector<std::vector<double>>& L,
                     std::vector<std::vector<double>>& U,
                     int n) {
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    U = A;

    for (int i = 0; i < n; ++i) L[i][i] = 1.0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double factor = U[j][i] / U[i][i];
            L[j][i] = factor;
            U[j][i] = 0.0;
            for (int k = i + 1; k < n; ++k) {
                U[j][k] -= factor * U[i][k];
            }
        }
    }
}

std::vector<double> forwardSubstitution(const std::vector<std::vector<double>>& L,
                                        const std::vector<double>& b,
                                        int n) {
    std::vector<double> y(n, 0.0);
    for (int i = 0; i < n; ++i) {
        double t = 0.0;
        for (int j = 0; j < i; ++j) {
            t += L[i][j] * y[j];
        }
        y[i] = (b[i] - t) / L[i][i];
    }
    return y;
}

std::vector<double> backSubstitution(const std::vector<std::vector<double>>& U, 
                                     const std::vector<double>& b, 
                                     int n) {
    std::vector<double> x(n, 0.0);
    for (int j = n - 1; j >= 0; --j) {
        double t = 0.0;
        for (int k = j + 1; k < n; ++k) {
            t += U[j][k] * x[k];
        }
        x[j] = (b[j] - t) / U[j][j];
    }
    return x;
}

int main() {
    int n = 3;
    std::vector<std::vector<double>> A = {
        {2.0,  1.0,  1.0},
        {4.0,  3.0,  3.0},
        {8.0,  7.0,  9.0}
    };
    std::vector<double> b = {4.0, 10.0, 24.0};

    std::vector<std::vector<double>> L, U;
    luDecomposition(A, L, U, n);

    std::cout << "Matrix L (Lower Triangular):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "  [ ";
        for (int j = 0; j < n; ++j) std::cout << std::setw(8) << L[i][j] << " ";
        std::cout << "]\n";
    }

    std::cout << "\nMatrix U (Upper Triangular):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "  [ ";
        for (int j = 0; j < n; ++j) std::cout << std::setw(8) << U[i][j] << " ";
        std::cout << "]\n";
    }

    std::vector<double> y = forwardSubstitution(L, b, n);
    std::vector<double> x = backSubstitution(U, y, n);

    std::cout << "\nSolution Vector x:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "  x" << i + 1 << " = " << x[i] << "\n";
    }

    std::cout << "\nVerification (A * x):\n";
    for (int i = 0; i < n; ++i) {
        double calc = 0.0;
        for (int j = 0; j < n; ++j) calc += A[i][j] * x[j];
        std::cout << "  Row " << i + 1 << ": " << calc << " (Expected: " << b[i] << ")\n";
    }

    return 0;
}
