#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double a = 0.8;
const double b = 0.3;
const double c = 0.4;
const double d = 0.1;
const int N = 20;

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double y_prev, double u, double u_prev) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

int main() {
    double y0 = 20.0;
    double u0 = 5.0;

    vector<double> y_lin(N + 1), y_nonlin(N + 1), u(N + 1);
    y_lin[0] = y0;
    y_nonlin[0] = y0;
    u[0] = u0;

    for (int tau = 1; tau <= N; ++tau) {
        u[tau] = (tau < 10) ? 5.0 : 10.0;
    }

    cout << "=========================================================" << endl;
    cout << "tau\ty_linear\ty_nonlinear\tu" << endl;
    cout << "=========================================================" << endl;

    for (int tau = 1; tau <= N; ++tau) {
        y_lin[tau] = linearModel(y_lin[tau - 1], u[tau - 1]);

        if (tau == 1) {
            y_nonlin[tau] = nonlinearModel(y_nonlin[tau - 1], y0, u[tau - 1], u0);
        } else {
            y_nonlin[tau] = nonlinearModel(y_nonlin[tau - 1], y_nonlin[tau - 2], u[tau - 1], u[tau - 2]);
        }

        cout << setw(3) << tau
             << setw(12) << fixed << setprecision(2) << y_lin[tau]
             << setw(16) << y_nonlin[tau]
             << setw(10) << u[tau - 1] << endl;
    }

    cout << "=========================================================" << endl;
    cout << "Конечная температура (линейная): " << y_lin[N] << endl;
    cout << "Конечная температура (нелинейная): " << y_nonlin[N] << endl;

    return 0;
}