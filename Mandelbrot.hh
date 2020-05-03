#pragma once

namespace BM
{
class Mandelbrot
{
public:
    static constexpr int MaxIterations = 20000;
    static int getIterations(double x_, double y_);
};
} // namespace BM