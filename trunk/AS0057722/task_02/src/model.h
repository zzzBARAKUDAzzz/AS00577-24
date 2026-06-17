#pragma once

double linearModel(double y, double u, double a, double b);

double nonlinearModel(double y, double yPrevious, double u, double uPrevious,
                      double a, double b, double c, double d);