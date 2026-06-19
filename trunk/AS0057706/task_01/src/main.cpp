#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Функция для симуляции линейной модели (2)
void simulateLinear(int n, double a, double b, double y0, const std::vector<double>& u) {
    std::vector<double> y(n + 1);
    y[0] = y0; // Начальная температура

    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }

    std::cout << "\n--- Linear Model Results ---\n";
    std::cout << std::setw(5) << "Step" << std::setw(15) << "u(t)" << std::setw(15) << "y(t+1)" << "\n";
    for (int t = 0; t < n; ++t) {
        std::cout << std::setw(5) << t << std::setw(15) << u[t] << std::setw(15) << y[t + 1] << "\n";
    }
}

// Функция для симуляции нелинейной модели (3)
void simulateNonlinear(int n, double a, double b, double c, double d, double y0, const std::vector<double>& u) {
    std::vector<double> y(n + 1);
    y[0] = y0; // y(0)
    
    // Предыдущие значения до начала симуляции (t=0) принимаем за y0 и 0.0
    for (int t = 0; t < n; ++t) {
        double prev_y = (t == 0) ? y0 : y[t - 1];
        double prev_u = (t == 0) ? 0.0 : u[t - 1];
        
        y[t + 1] = a * y[t] - b * (prev_y * prev_y) + c * u[t] + d * std::sin(prev_u);
    }

    std::cout << "\n--- Nonlinear Model Results ---\n";
    std::cout << std::setw(5) << "Step" << std::setw(15) << "u(t)" << std::setw(15) << "y(t+1)" << "\n";
    for (int t = 0; t < n; ++t) {
        std::cout << std::setw(5) << t << std::setw(15) << u[t] << std::setw(15) << y[t + 1] << "\n";
    }
}

int main() {
    // Настройка вывода чисел с плавающей запятой (4 знака после точки)
    std::cout << std::fixed << std::setprecision(4);

    int n;
    double a, b, c, d, y0;

    std::cout << "Enter the number of simulation steps (n): ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "Error: number of steps must be greater than 0.\n";
        return 1;
    }

    std::cout << "Enter the initial temperature (y0): ";
    std::cin >> y0;

    std::cout << "Enter parameters (a b c d) separated by space: ";
    std::cin >> a >> b >> c >> d;

    // Массив входного тепла u(t) для каждого шага
    std::vector<double> u(n);
    std::cout << "Enter " << n << " values for u(t):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "u[" << i << "]: ";
        std::cin >> u[i];
    }

    // Запуск симуляций для обеих моделей
    simulateLinear(n, a, b, y0, u);
    simulateNonlinear(n, a, b, c, d, y0, u);

    return 0;
}