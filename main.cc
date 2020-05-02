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

  fractal_creator.addRange(0.0, BM::RGB{0, 0, 0});
  fractal_creator.addRange(0.3, BM::RGB{255, 0, 0});
  fractal_creator.addRange(0.5, BM::RGB{255, 255, 0});
  fractal_creator.addRange(10, BM::RGB{255, 255, 255});

  fractal_creator.addZoom(BM::Zoom{146, 202, 0.1});
  fractal_creator.addZoom(BM::Zoom{175, 330, 0.1});

  fractal_creator.drawFractal();

  if (!fractal_creator.writeBitmap("test.bmp")) {
    std::cout << "Something went wrong when creating file" << std::endl;
    return 1;
  }

  return 0;
}
