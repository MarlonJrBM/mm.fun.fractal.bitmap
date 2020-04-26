#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

#include "Bitmap.hh"
#include "FractalCreator.hh"
#include "Mandelbrot.hh"
#include "Zoom.hh"

constexpr int Width = 800;
constexpr int Height = 600;

int main() {
  BM::FractalCreator fractal_creator(Width, Height);

  fractal_creator.drawFractal();

  if (!fractal_creator.writeBitmap("test.bmp")) {
    std::cout << "Something went wrong when creating file" << std::endl;
    return 1;
  }

  return 0;
}
