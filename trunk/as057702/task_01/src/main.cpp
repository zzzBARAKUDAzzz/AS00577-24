#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Константы для моделей
const double a = 0.9;
const double b = 0.1;
const double c = 0.5;
const double d = 0.2;

// Параметры симуляции
const int n = 50;  // количество шагов
const double init_temp = 20.0;  // начальная температура (комнатная)

// Линейная модель (2)
void linearModel() {
    std::cout << "=== Linear Model: y(t+1) = a*y(t) + b*u(t) ===" << std::endl;
    
    std::vector<double> y(n + 1);
    std::vector<double> u(n + 1, 1.0);  // входное воздействие (тепло) = 1
    
    y[0] = init_temp;
    
    std::cout << "t\tu(t)\ty(t)" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    
    for (int t = 0; t < n; t++) {
        std::cout << t << "\t" << u[t] << "\t" << y[t] << std::endl;
        y[t + 1] = a * y[t] + b * u[t];
    }
    std::cout << std::endl;
}

// Нелинейная модель (3)
void nonlinearModel() {
    std::cout << "=== Nonlinear Model: y(t+1) = a*y(t) - b*y(t-1)^2 + c*u(t) + d*sin(u(t-1)) ===" << std::endl;
    
    std::vector<double> y(n + 1);
    std::vector<double> u(n + 1, 1.0);  // входное воздействие = 1
    
    y[0] = init_temp;
    y[1] = init_temp;  // для t=1 нужно начальное значение y[-1], примем равным init_temp
    
    std::cout << "t\tu(t)\ty(t)" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    
    std::cout << 0 << "\t" << u[0] << "\t" << y[0] << std::endl;
    
    y[1] = a * y[0] - b * y[0] * y[0] + c * u[0] + d * sin(u[0]);
    std::cout << 1 << "\t" << u[1] << "\t" << y[1] << std::endl;
    
    for (int t = 2; t <= n; t++) {
        y[t] = a * y[t - 1] - b * y[t - 2] * y[t - 2] + c * u[t] + d * sin(u[t - 1]);
        std::cout << t << "\t" << u[t] << "\t" << y[t] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    linearModel();
    nonlinearModel();
    
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    
    return 0;
}