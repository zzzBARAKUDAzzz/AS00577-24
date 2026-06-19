#include <gtest/gtest.h>
#include "../src/models.hpp"

// === ТЕСТЫ ЛИНЕЙНОЙ МОДЕЛИ ===

// Тест 1: Проверка линейной модели (умножение на 2, без тепла)
TEST(LinearModelTest, DoublingWithoutInput) {
    std::vector<double> u = {0.0, 0.0, 0.0};
    auto res = simulateLinear(3, 2.0, 0.0, 10.0, u);
    
    ASSERT_EQ(res.size(), 3);
    EXPECT_NEAR(res[0], 20.0, 1e-4);
    EXPECT_NEAR(res[1], 40.0, 1e-4);
    EXPECT_NEAR(res[2], 80.0, 1e-4);
}

// Тест 2: Проверка линейной модели (стационарный режим при а=1, b=1)
TEST(LinearModelTest, SteadyStateWithInput) {
    std::vector<double> u = {5.0, 5.0};
    auto res = simulateLinear(2, 1.0, 1.0, 0.0, u);
    
    ASSERT_EQ(res.size(), 2);
    EXPECT_NEAR(res[0], 5.0, 1e-4);  // 1*0 + 1*5 = 5
    EXPECT_NEAR(res[1], 10.0, 1e-4); // 1*5 + 1*5 = 10
}

// === ТЕСТЫ НЕЛИНЕЙНОЙ МОДЕЛИ ===

// Тест 3: Проверка нелинейной модели (прямой перенос тепла при c=1)
TEST(NonlinearModelTest, DirectTransfer) {
    std::vector<double> u = {5.5, 12.3};
    auto res = simulateNonlinear(2, 0.0, 0.0, 1.0, 0.0, 0.0, u);
    
    ASSERT_EQ(res.size(), 2);
    EXPECT_NEAR(res[0], 5.5, 1e-4);
    EXPECT_NEAR(res[1], 12.3, 1e-4);
}

// Тест 4: Проверка нелинейной модели (нулевые параметры дают нули)
TEST(NonlinearModelTest, ZeroParametersYieldsZero) {
    std::vector<double> u = {10.0, 20.0};
    auto res = simulateNonlinear(2, 0.0, 0.0, 0.0, 0.0, 0.0, u);
    
    ASSERT_EQ(res.size(), 2);
    EXPECT_NEAR(res[0], 0.0, 1e-4);
    EXPECT_NEAR(res[1], 0.0, 1e-4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}