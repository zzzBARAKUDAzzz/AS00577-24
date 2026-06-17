
#include "model.h"
#include <cmath>

double linearModel(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinearModel(double y, double yPrevious, double u, double uPrevious,
                      double a, double b, double c, double d) {
    return a * y - b * yPrevious * yPrevious + c * u + d * std::sin(uPrevious);
}