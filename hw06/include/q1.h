#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1
{
    const double delta = 1e-3;
    const double epsilon = 1e-8;
    
    inline double derivative(double x,
                            const std::function<double(double)>& func)
    {
        return (func(x + delta) - func(x)) / delta;
    }

    inline double gradient_descent(double init, double step,
                            std::function<double(double)> func) 
    {
        double next = init;
        double d = derivative(init, func);
        while (d > epsilon || d < -epsilon) {
            next = next - step * d;
            d = derivative(next, func);
        }
        return next;
    }

    template <typename T, typename F>
    T gradient_descent(T init, T step)
    {
        return gradient_descent(init, step, F());
    }
}

#endif //Q1_H
