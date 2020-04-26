#include "FractalCreator.hh"

#include <iostream>

#include "Mandelbrot.hh"

namespace BM {

FractalCreator::FractalCreator(int width_, int height_)
    : _width(width_),
      _height(height_),
      _histogram(std::make_unique<int[]>(BM::Mandelbrot::MaxIterations)),
      _fractal(std::make_unique<int[]>(width_ * height_)),
      _bitmap(width_, height_),
      _zoom_list(width_, height_) {
  addZoom(BM::Zoom{_width / 2, _height / 2, 2.0 / _height});
}
FractalCreator::~FractalCreator() {}

void FractalCreator::calculateIterations() {
  for (int jj = 0; jj < _height; ++jj) {
    for (int ii = 0; ii < _width; ++ii) {
      auto [x_fractal, y_fractal] = _zoom_list.doZoom(ii, jj);

      int iterations = BM::Mandelbrot::getIterations(x_fractal, y_fractal);
      _fractal[(jj * _width) + ii] = iterations;

      if (iterations != BM::Mandelbrot::MaxIterations) {
        ++_histogram[iterations];
      }
    }
  }
}
void FractalCreator::drawFractal() {

  calculateIterations();

  int total = 0;
  for (int ii = 0; ii < BM::Mandelbrot::MaxIterations; ++ii) {
    total += _histogram[ii];
  }

  RGB start_color{};
  RGB end_color{0, 255, 0};

  for (int ii = 0; ii < _height; ++ii) {
    for (int jj = 0; jj < _width; ++jj) {
      const int iterations = _fractal[(ii * _width) + jj];

      uint8_t red{0};
      uint8_t green{0};
      uint8_t blue{0};
      double hue{0};

      if (iterations != BM::Mandelbrot::MaxIterations) {
        for (int ii = 0; ii < iterations; ++ii) {
          hue += double(_histogram[ii]) / total;
        }

        green = hue * 255;
      }

      _bitmap.setPixel(ii, jj, red, green, blue);
    }
  }
}
void FractalCreator::addZoom(const Zoom& zoom_) { _zoom_list.add(zoom_); }
bool FractalCreator::writeBitmap(const std::string& file_name_) {
  if (!_bitmap.write(file_name_)) {
    return false;
  }
  return true;
}

}  // namespace BM