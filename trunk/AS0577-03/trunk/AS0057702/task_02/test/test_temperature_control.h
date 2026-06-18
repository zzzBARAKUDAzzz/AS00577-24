#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

class TemperatureController {
private:
    double a;
    double b;
    double c;
    double d;
    double T0;
    double dt;
    
    std::vector<double> temperatures;
    std::vector<double> inputs;
    int currentStep;

public:
    TemperatureController(double a_, double b_, double c_, double d_,
                         double room_temp = 20.0, double time_step = 0.1);
    
    ~TemperatureController() = default;
    
    double simulateLinearStep(double current_temp, double input_power);
    
    double simulateNonlinearStep(double current_temp, double previous_temp, 
                                 double input_power);
    
    std::vector<double> runLinearSimulation(int steps, double input_power, 
                                           bool verbose = true);
    
    std::vector<double> runNonlinearSimulation(int steps, double input_power, 
                                              bool verbose = true);
    
    std::vector<double> simulateWithSequence(int steps, 
                                            const std::vector<double>& input_sequence,
                                            const std::string& model_type = "linear");
    
    void setInitialTemperature(double temp);
    
    void setParameters(double a_, double b_, double c_, double d_);
    
    void setRoomTemperature(double temp);
    
    double getCurrentTemperature() const;
    
    std::vector<double> getTemperatureHistory() const;
    
    std::vector<double> getInputHistory() const;
    
    int getCurrentStep() const;
    
    double getSteadyStateTemp(double input_power) const;
    
    void reset();
    
    void printModelInfo() const;
    
    void displayResults(const std::vector<double>& temps, 
                       const std::string& title) const;
    
    static double calculateDerivative(double temp, double input, 
                                     double room_temp, double tau, double k);
};

#endif