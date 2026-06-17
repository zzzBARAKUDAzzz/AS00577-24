#include <gtest/gtest.h>
#include "../src/model.h"
#include <cmath>

TEST(LinearModelTest, CalculatesCorrectValue) {
    double result = linearModel(20.0, 0.1, 0.8, 0.001);
    EXPECT_NEAR(result, 16.0001, 0.0001);
}

TEST(LinearModelTest, ZeroInput) {
    double result = linearModel(10.0, 0.0, 0.5, 0.1);
    EXPECT_NEAR(result, 5.0, 0.0001);
}

TEST(LinearModelTest, ZeroTemperature) {
    double result = linearModel(0.0, 10.0, 0.8, 0.2);
    EXPECT_NEAR(result, 2.0, 0.0001);
}

TEST(NonlinearModelTest, CalculatesCorrectValue) {
    double result = nonlinearModel(20.0, 20.0, 0.1, 0.1, 0.8, 0.001, 0.12, 0.05);
    double expected = 0.8 * 20.0 - 0.001 * 20.0 * 20.0 + 0.12 * 0.1 + 0.05 * std::sin(0.1);

    EXPECT_NEAR(result, expected, 0.0001);
}

TEST(NonlinearModelTest, ZeroPreviousTemperature) {
    double result = nonlinearModel(10.0, 0.0, 1.0, 0.0, 0.5, 0.1, 0.2, 0.3);
    EXPECT_NEAR(result, 5.2, 0.0001);
}

TEST(NonlinearModelTest, ZeroInput) {
    double result = nonlinearModel(10.0, 2.0, 0.0, 0.0, 0.5, 0.1, 0.2, 0.3);
    EXPECT_NEAR(result, 4.6, 0.0001);
}