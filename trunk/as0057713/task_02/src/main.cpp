#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Константы модели
const double A = 0.9;
const double B = 0.1;
const double C = 0.5;
const double D = 0.2;
const int STEPS = 50;
const double INIT_TEMP = 20.0;

// Линейная модель: y(t+1) = a*y(t) + b*u(t)
double linearStep(double y, double u) {
    return A * y + B * u;
}

// Нелинейная модель: y(t+1) = a*y(t) - b*y(t-1)^2 + c*u(t) + d*sin(u(t-1))
double nonlinearStep(double y_curr, double y_prev, double u_curr, double u_prev) {
    return A * y_curr - B * y_prev * y_prev + C * u_curr + D * sin(u_prev);
}

// Моделирование линейной системы
std::vector<double> simulateLinear(const std::vector<double>& u) {
    std::vector<double> y(u.size() + 1);
    y[0] = INIT_TEMP;
    for (size_t t = 0; t < u.size(); t++) {
        y[t + 1] = linearStep(y[t], u[t]);
    }
    return y;
}

// Моделирование нелинейной системы
std::vector<double> simulateNonlinear(const std::vector<double>& u) {
    std::vector<double> y(u.size() + 1);
    y[0] = INIT_TEMP;
    y[1] = nonlinearStep(y[0], y[0], u[0], u[0]);
    for (size_t t = 1; t < u.size(); t++) {
        y[t + 1] = nonlinearStep(y[t], y[t - 1], u[t], u[t - 1]);
    }
    return y;
}

void printResults(const std::vector<double>& u, const std::vector<double>& y) {
    std::cout << "t\tu(t)\ty(t)" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    for (size_t t = 0; t < u.size(); t++) {
        std::cout << t << "\t" << u[t] << "\t" << y[t] << std::endl;
    }
    std::cout << std::endl;
}

// int main() {
//     std::vector<double> u(STEPS, 1.0);
// 
//     std::cout << "=== Linear Model ===" << std::endl;
//     auto y_linear = simulateLinear(u);
//     printResults(u, y_linear);
// 
//     std::cout << "=== Nonlinear Model ===" << std::endl;
//     auto y_nonlinear = simulateNonlinear(u);
//     printResults(u, y_nonlinear);
// 
//     std::cout << "Press Enter to exit..." << std::endl;
//     std::cin.get();
//     return 0;
// }