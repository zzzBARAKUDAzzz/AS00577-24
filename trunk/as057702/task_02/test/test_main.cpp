#include <gtest/gtest.h>
#include <cmath>

// Подключаем тестируемые функции
extern double linearStep(double y, double u);
extern double nonlinearStep(double y_curr, double y_prev, double u_curr, double u_prev);
extern std::vector<double> simulateLinear(const std::vector<double>& u);
extern std::vector<double> simulateNonlinear(const std::vector<double>& u);

// Тесты linearStep
TEST(LinearStepTest, BasicCalculation) {
    EXPECT_DOUBLE_EQ(linearStep(20.0, 1.0), 18.1);  // 0.9*20 + 0.1*1
}

TEST(LinearStepTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearStep(10.0, 0.0), 9.0);   // 0.9*10
}

TEST(LinearStepTest, ZeroTemp) {
    EXPECT_DOUBLE_EQ(linearStep(0.0, 5.0), 0.5);    // 0.1*5
}

// Тесты nonlinearStep
TEST(NonlinearStepTest, BasicCalculation) {
    double result = nonlinearStep(20.0, 20.0, 1.0, 1.0);
    double expected = 0.9 * 20.0 - 0.1 * 400.0 + 0.5 * 1.0 + 0.2 * sin(1.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearStepTest, ZeroValues) {
    double result = nonlinearStep(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Тесты simulateLinear
TEST(SimulateLinearTest, CorrectSize) {
    std::vector<double> u(10, 1.0);
    auto y = simulateLinear(u);
    EXPECT_EQ(y.size(), u.size() + 1);
}

TEST(SimulateLinearTest, InitialTemperature) {
    std::vector<double> u(5, 1.0);
    auto y = simulateLinear(u);
    EXPECT_DOUBLE_EQ(y[0], 20.0);
}

TEST(SimulateLinearTest, ConstantInput) {
    std::vector<double> u(3, 1.0);
    auto y = simulateLinear(u);
    EXPECT_DOUBLE_EQ(y[1], linearStep(20.0, 1.0));
    EXPECT_DOUBLE_EQ(y[2], linearStep(y[1], 1.0));
}

// Тесты simulateNonlinear
TEST(SimulateNonlinearTest, CorrectSize) {
    std::vector<double> u(10, 1.0);
    auto y = simulateNonlinear(u);
    EXPECT_EQ(y.size(), u.size() + 1);
}

TEST(SimulateNonlinearTest, InitialTemperature) {
    std::vector<double> u(5, 1.0);
    auto y = simulateNonlinear(u);
    EXPECT_DOUBLE_EQ(y[0], 20.0);
}