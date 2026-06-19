#pragma once
#include <vector>
#include <cmath>

// Реализация линейной модели
inline std::vector<double> simulateLinear(int n, double a, double b, double y0, const std::vector<double>& u) {
    std::vector<double> y(n + 1);
    y[0] = y0;
    std::vector<double> results;
    
    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
        results.push_back(y[t + 1]);
    }
    return results;
}

// Реализация нелинейной модели
inline std::vector<double> simulateNonlinear(int n, double a, double b, double c, double d, double y0, const std::vector<double>& u) {
    std::vector<double> y(n + 1);
    y[0] = y0;
    std::vector<double> results;
    
    for (int t = 0; t < n; ++t) {
        double prev_y = (t == 0) ? y0 : y[t - 1];
        double prev_u = (t == 0) ? 0.0 : u[t - 1];
        
        y[t + 1] = a * y[t] - b * (prev_y * prev_y) + c * u[t] + d * std::sin(prev_u);
        results.push_back(y[t + 1]);
    }
    return results;
}