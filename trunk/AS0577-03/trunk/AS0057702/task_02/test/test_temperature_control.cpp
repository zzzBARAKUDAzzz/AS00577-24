
#include <gtest/gtest.h>
#include "../src/bez1lab.h"
#include <cmath>


class TemperatureObjectTest : public ::testing::Test {
protected:
    void SetUp() override {

        obj.setModelType(true);
        obj.setParams(0.85, 0.15, 0.12, 0.08, 25.0, 100.0, 10.0);
        obj.setInitialState(25.0);
    }

    TemperatureObject obj;
};


TEST_F(TemperatureObjectTest, DefaultConstructor) {
    TemperatureObject defaultObj;
    EXPECT_EQ(defaultObj.getA(), 0.8);
    EXPECT_EQ(defaultObj.getB(), 0.2);
    EXPECT_EQ(defaultObj.getC(), 0.15);
    EXPECT_EQ(defaultObj.getD(), 0.1);
    EXPECT_EQ(defaultObj.getY0(), 25.0);
    EXPECT_EQ(defaultObj.getCParam(), 100.0);
    EXPECT_EQ(defaultObj.getRC(), 10.0);
    EXPECT_TRUE(defaultObj.getModelType());
    EXPECT_DOUBLE_EQ(defaultObj.getCurrentTemperature(), 25.0);
}

TEST_F(TemperatureObjectTest, SetParams) {
    obj.setParams(0.9, 0.1, 0.2, 0.05, 30.0, 200.0, 15.0);
    EXPECT_EQ(obj.getA(), 0.9);
    EXPECT_EQ(obj.getB(), 0.1);
    EXPECT_EQ(obj.getC(), 0.2);
    EXPECT_EQ(obj.getD(), 0.05);
    EXPECT_EQ(obj.getY0(), 30.0);
    EXPECT_EQ(obj.getCParam(), 200.0);
    EXPECT_EQ(obj.getRC(), 15.0);
}


TEST_F(TemperatureObjectTest, LinearStep) {
    double u = 50.0;
    double expected = 0.85 * 25.0 + 0.15 * 50.0; 
    double result = obj.step(u);
    EXPECT_DOUBLE_EQ(result, expected);
    EXPECT_DOUBLE_EQ(obj.getCurrentTemperature(), expected);
    EXPECT_DOUBLE_EQ(obj.getPreviousTemperature(), 25.0);
    EXPECT_DOUBLE_EQ(obj.getPreviousControl(), 50.0);
}


TEST_F(TemperatureObjectTest, LinearMultipleSteps) {
    std::vector<double> u = {50.0, 40.0, 30.0};
    std::vector<double> y = obj.simulate(u);

    double y0 = 25.0;
    double y1 = 0.85 * y0 + 0.15 * 50.0;
    double y2 = 0.85 * y1 + 0.15 * 40.0;
    double y3 = 0.85 * y2 + 0.15 * 30.0;
    
    EXPECT_EQ(y.size(), 3);
    EXPECT_DOUBLE_EQ(y[0], y1);
    EXPECT_DOUBLE_EQ(y[1], y2);
    EXPECT_DOUBLE_EQ(y[2], y3);
}


TEST_F(TemperatureObjectTest, NonlinearStep) {
    obj.setModelType(false);
    obj.setInitialState(25.0);
    

    double u1 = 50.0;
    double expected1 = 0.85 * 25.0 - 0.15 * 25.0 * 25.0 + 0.12 * 50.0 + 0.08 * sin(0.0);
    double result1 = obj.step(u1);
    EXPECT_DOUBLE_EQ(result1, expected1);
    EXPECT_DOUBLE_EQ(obj.getPreviousControl(), 50.0);
    

    double u2 = 40.0;
    double expected2 = 0.85 * result1 - 0.15 * 25.0 * 25.0 + 0.12 * 40.0 + 0.08 * sin(50.0);
    double result2 = obj.step(u2);
    EXPECT_DOUBLE_EQ(result2, expected2);
}


TEST_F(TemperatureObjectTest, ModelTypeSwitching) {
    EXPECT_TRUE(obj.getModelType());
    obj.setModelType(false);
    EXPECT_FALSE(obj.getModelType());
    obj.setModelType(true);
    EXPECT_TRUE(obj.getModelType());
}


TEST_F(TemperatureObjectTest, SetInitialState) {
    obj.setInitialState(100.0);
    EXPECT_DOUBLE_EQ(obj.getCurrentTemperature(), 100.0);
    EXPECT_DOUBLE_EQ(obj.getPreviousTemperature(), 100.0);
    EXPECT_DOUBLE_EQ(obj.getPreviousControl(), 0.0);
}


TEST_F(TemperatureObjectTest, LinearStability) {
    obj.setParams(0.5, 0.5, 0.0, 0.0, 25.0, 100.0, 10.0);
    obj.setInitialState(0.0);
    
    std::vector<double> u(10, 100.0); 
    std::vector<double> y = obj.simulate(u);
    
 
    double steadyState = 100.0; 
    double tolerance = 0.01;
    EXPECT_NEAR(y.back(), steadyState, tolerance);
}


TEST_F(TemperatureObjectTest, NonlinearWithDifferentParams) {
    obj.setModelType(false);
    obj.setParams(0.9, 0.01, 0.1, 0.05, 25.0, 100.0, 10.0);
    obj.setInitialState(25.0);
    
    std::vector<double> u = {10.0, 20.0, 30.0};
    std::vector<double> y = obj.simulate(u);
    
    EXPECT_EQ(y.size(), 3);
 
    for (double val : y) {
        EXPECT_TRUE(std::isfinite(val));
        EXPECT_GT(val, -1000.0);
        EXPECT_LT(val, 1000.0);
    }
}


TEST(TemperatureObjectTest, GenerateTestSignal) {
    int n = 100;
    std::vector<double> u = generateTestSignal(n);
    
    EXPECT_EQ(u.size(), n);
    for (double val : u) {
        EXPECT_GT(val, 0.0);
        EXPECT_LT(val, 100.0);
    }
    

    EXPECT_GE(u[0], 15.0);
    EXPECT_LE(u[0], 25.0);
    EXPECT_GE(u[n/4], 45.0);
    EXPECT_LE(u[n/4], 55.0);
}


TEST(TemperatureObjectTest, CalculateMaxDifference) {
    std::vector<double> y1 = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y2 = {1.5, 2.5, 3.5, 4.5, 5.5};
    
    double maxDiff = calculateMaxDifference(y1, y2);
    EXPECT_DOUBLE_EQ(maxDiff, 0.5);
}


TEST(TemperatureObjectTest, CalculateAverageDifference) {
    std::vector<double> y1 = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y2 = {1.5, 2.5, 3.5, 4.5, 5.5};
    
    double avgDiff = calculateAverageDifference(y1, y2);
    EXPECT_DOUBLE_EQ(avgDiff, 0.5);
}


TEST(TemperatureObjectTest, EmptyVectors) {
    std::vector<double> empty1;
    std::vector<double> empty2;
    std::vector<double> y1 = {1.0, 2.0};
    std::vector<double> y2 = {1.0};
    
    EXPECT_DOUBLE_EQ(calculateMaxDifference(empty1, empty2), -1.0);
    EXPECT_DOUBLE_EQ(calculateAverageDifference(empty1, empty2), -1.0);
    EXPECT_DOUBLE_EQ(calculateMaxDifference(y1, y2), -1.0);
    EXPECT_DOUBLE_EQ(calculateAverageDifference(y1, y2), -1.0);
}


TEST_F(TemperatureObjectTest, LinearVsNonlinear) {

    TemperatureObject linear;
    linear.setModelType(true);
    linear.setParams(0.85, 0.15, 0.12, 0.08, 25.0, 100.0, 10.0);
    linear.setInitialState(25.0);
    

    TemperatureObject nonlinear;
    nonlinear.setModelType(false);
    nonlinear.setParams(0.85, 0.15, 0.12, 0.08, 25.0, 100.0, 10.0);
    nonlinear.setInitialState(25.0);
    
    std::vector<double> u = generateTestSignal(20);
    std::vector<double> y_linear = linear.simulate(u);
    std::vector<double> y_nonlinear = nonlinear.simulate(u);
    

    double diff = calculateMaxDifference(y_linear, y_nonlinear);
    EXPECT_GT(diff, 0.0);
}


TEST_F(TemperatureObjectTest, PreviousValuesStorage) {
    obj.setInitialState(25.0);
    
    double u1 = 50.0;
    obj.step(u1);
    
    EXPECT_DOUBLE_EQ(obj.getPreviousTemperature(), 25.0);
    EXPECT_DOUBLE_EQ(obj.getPreviousControl(), 50.0);
    
    double u2 = 40.0;
    double y2 = obj.step(u2);
    
    EXPECT_DOUBLE_EQ(obj.getPreviousTemperature(), y2);
    EXPECT_DOUBLE_EQ(obj.getPreviousControl(), 40.0);
}