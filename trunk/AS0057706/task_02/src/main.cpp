#include <iostream>
#include <iomanip>
#include "models.hpp"

int main() {
    std::cout << std::fixed << std::setprecision(4);
    int n;
    double a, b, c, d, y0;

    std::cout << "Enter the number of simulation steps (n): ";
    if (!(std::cin >> n) || n <= 0) return 1;

    std::cout << "Enter the initial temperature (y0): ";
    std::cin >> y0;

    std::cout << "Enter parameters (a b c d) separated by space: ";
    std::cin >> a >> b >> c >> d;

    std::vector<double> u(n);
    std::cout << "Enter " << n << " values for u(t):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "u[" << i << "]: ";
        std::cin >> u[i];
    }

    auto res_lin = simulateLinear(n, a, b, y0, u);
    auto res_nonlin = simulateNonlinear(n, a, b, c, d, y0, u);

    std::cout << "\n--- Linear Model Results ---\n";
    std::cout << "Step          u(t)        y(t+1)\n";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(5) << i << std::setw(14) << u[i] << std::setw(15) << res_lin[i] << "\n";
    }

    std::cout << "\n--- Nonlinear Model Results ---\n";
    std::cout << "Step          u(t)        y(t+1)\n";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(5) << i << std::setw(14) << u[i] << std::setw(15) << res_nonlin[i] << "\n";
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}