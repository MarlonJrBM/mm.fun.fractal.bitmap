#pragma once

namespace BM {
class Mandelbrot {
public:
    static constexpr int MaxIterations = 1000;
    static int getIterations(double x_, double y_);
};
}