#include "Mandelbrot.hh"

#include <complex>

namespace BM {
int Mandelbrot::getIterations(double x_, double y_) {
  std::complex<double> zz = 0;
  std::complex<double> cc(x_, y_);

  int iterations{0};

  while (iterations < MaxIterations) {
    zz = zz * zz + cc;

    if (std::abs(zz) > 2) {
      break;
    }
    ++iterations;
  }

  return iterations;
}
}  // namespace BM