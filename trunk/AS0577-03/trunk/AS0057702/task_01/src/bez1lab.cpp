

#include "bez1lab.h"


#include <iostream>
#include <vector>
#include <cmath>
#include <random>


struct ModelParams {
    double a;    
    double b;    
    double c;    
    double d;    
    double Y0;   
    double C;   
    double RC;   
};


struct ObjectState {
    double y;    
    double y_prev; 
    double u_prev;
};

class TemperatureObject {
private:
    ModelParams params;
    ObjectState state;
    bool isLinear; 

public:
    
    TemperatureObject() : isLinear(true) {
        params.a = 0.8;
        params.b = 0.2;
        params.c = 0.15;
        params.d = 0.1;
        params.Y0 = 25.0; 
        params.C = 100.0;
        params.RC = 10.0;

        state.y = params.Y0;
        state.y_prev = params.Y0;
        state.u_prev = 0.0;
    }

   
    void setParams(const ModelParams& newParams) {
        params = newParams;
    }

   
    void setModelType(bool linear) {
        isLinear = linear;
    }

   
    void setInitialState(double y0) {
        state.y = y0;
        state.y_prev = y0;
        state.u_prev = 0.0;
    }

   
    double step(double u) {
        double y_next;

        if (isLinear) {
            
            y_next = params.a * state.y + params.b * u;
        }
        else {
           
            y_next = params.a * state.y -
                params.b * state.y_prev * state.y_prev +
                params.c * u +
                params.d * sin(state.u_prev);
        }

       
        state.y_prev = state.y;
        state.u_prev = u;
        state.y = y_next;

        return state.y;
    }

   
    std::vector<double> simulate(const std::vector<double>& u_sequence) {
        std::vector<double> y_sequence;
        y_sequence.reserve(u_sequence.size());

        for (double u : u_sequence) {
            double y = step(u);
            y_sequence.push_back(y);
        }

        return y_sequence;
    }

    
    ObjectState getState() const {
        return state;
    }

    
    ModelParams getParams() const {
        return params;
    }

    
    void printInfo() const {
        std::cout << "=== Controlled Object Model ===" << std::endl;
        std::cout << "Model type: " << (isLinear ? "Linear" : "Nonlinear") << std::endl;
        std::cout << "Parameters:" << std::endl;
        std::cout << "  a = " << params.a << std::endl;
        std::cout << "  b = " << params.b << std::endl;
        std::cout << "  c = " << params.c << std::endl;
        std::cout << "  d = " << params.d << std::endl;
        std::cout << "  Y0 = " << params.Y0 << " °C" << std::endl;
        std::cout << "Current temperature: " << state.y << " °C" << std::endl;
        std::cout << "================================" << std::endl;
    }
};


std::vector<double> generateTestSignal(int n, double amplitude = 50.0) {
    std::vector<double> u(n);

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-5.0, 5.0);

    for (int i = 0; i < n; ++i) {
     
        if (i < n / 4) {
            u[i] = 20.0 + dis(gen);
        }
        else if (i < n / 2) {
            u[i] = 50.0 + dis(gen);
        }
        else if (i < 3 * n / 4) {
            u[i] = 30.0 + dis(gen);
        }
        else {
            u[i] = 60.0 + dis(gen);
        }
    }

    return u;
}


void printResults(const std::vector<double>& time,
    const std::vector<double>& u,
    const std::vector<double>& y_linear,
    const std::vector<double>& y_nonlinear) {
    std::cout << "\n=== Simulation Results ===" << std::endl;
    std::cout << "Step\tControl\t\tLinear\t\tNonlinear" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (size_t i = 0; i < time.size(); ++i) {
        std::cout << i + 1 << "\t"
            << u[i] << "\t\t"
            << y_linear[i] << "\t\t"
            << y_nonlinear[i] << std::endl;
    }
}

int main() {

    const int N = 50; 

  
    TemperatureObject linearModel;
    linearModel.setModelType(true);

    TemperatureObject nonlinearModel;
    nonlinearModel.setModelType(false);

 
    ModelParams commonParams;
    commonParams.a = 0.85;
    commonParams.b = 0.15;
    commonParams.c = 0.12;
    commonParams.d = 0.08;
    commonParams.Y0 = 25.0;
    commonParams.C = 100.0;
    commonParams.RC = 10.0;

    linearModel.setParams(commonParams);
    nonlinearModel.setParams(commonParams);

   
    linearModel.setInitialState(commonParams.Y0);
    nonlinearModel.setInitialState(commonParams.Y0);


    linearModel.printInfo();
    nonlinearModel.printInfo();

 
    std::vector<double> u = generateTestSignal(N, 50.0);

    std::vector<double> y_linear = linearModel.simulate(u);
    std::vector<double> y_nonlinear = nonlinearModel.simulate(u);


    std::vector<double> time(N);
    for (int i = 0; i < N; ++i) {
        time[i] = i + 1;
    }

    printResults(time, u, y_linear, y_nonlinear);


    std::cout << "\n=== Model Comparison ===" << std::endl;
    double maxDiff = 0.0;
    double avgDiff = 0.0;
    for (size_t i = 0; i < N; ++i) {
        double diff = std::abs(y_linear[i] - y_nonlinear[i]);
        maxDiff = std::max(maxDiff, diff);
        avgDiff += diff;
    }
    avgDiff /= N;

    std::cout << "Maximum difference between models: " << maxDiff << " °C" << std::endl;
    std::cout << "Average difference: " << avgDiff << " °C" << std::endl;

 
    std::cout << "\n=== Differential Equation Verification ===" << std::endl;
    std::cout << "Differential equation parameters:" << std::endl;
    std::cout << "  C = " << commonParams.C << std::endl;
    std::cout << "  RC = " << commonParams.RC << std::endl;
    std::cout << "  Y0 = " << commonParams.Y0 << " °C" << std::endl;
    std::cout << "For discrete model: dt = 1 (conditional)" << std::endl;
    std::cout << "a = 1 - dt/(RC) = " << 1.0 - 1.0 / commonParams.RC << std::endl;
    std::cout << "b = dt/C = " << 1.0 / commonParams.C << std::endl;

    return 0;
}
