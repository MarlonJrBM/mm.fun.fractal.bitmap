#include "FractalCreator.hh"

#include <iostream>
#include <cassert>

#include "Mandelbrot.hh"

namespace BM {

FractalCreator::FractalCreator(int width_, int height_)
    : _width(width_),
      _height(height_),
      _total_iterations(0),
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

void FractalCreator::calculateTotalIterations() {
  for (int ii = 0; ii < BM::Mandelbrot::MaxIterations; ++ii) {
    _total_iterations += _histogram[ii];
  }
}

void FractalCreator::drawFractal() {
  calculateIterations();
  calculateTotalIterations();
  calculateRangeTotals();

  RGB start_color{0, 0, 0};
  RGB end_color{0, 0, 255};
  RGB color_diff = end_color - start_color;

  for (int ii = 0; ii < _height; ++ii) {
    for (int jj = 0; jj < _width; ++jj) {
      const int iterations = _fractal[(ii * _width) + jj];

      uint8_t red{0};
      uint8_t green{0};
      uint8_t blue{0};
      double hue{0};

      if (iterations != BM::Mandelbrot::MaxIterations) {
        for (int ii = 0; ii < iterations; ++ii) {
          hue += double(_histogram[ii]) / _total_iterations;
        }

        red = start_color.red + color_diff.red * hue;
        green = start_color.green + color_diff.green * hue;
        blue = start_color.blue + color_diff.blue * hue;
      }

      _bitmap.setPixel(ii, jj, red, green, blue);
    }
  }
}
void FractalCreator::addZoom(const Zoom& zoom_) { _zoom_list.add(zoom_); }

void FractalCreator::addRange(double range_end_, const RGB& rgb_) {
  _ranges.push_back(range_end_ * Mandelbrot::MaxIterations);
  _colors.push_back(rgb_);

  if (_got_first_range) {
    _range_totals.push_back(0);
  }

  _got_first_range = true;
}

int FractalCreator::getRange(int iterations) const {
  int range = 0;

  for (int ii=1; ii < _ranges.size(); ++ii) {
    range = ii;

    if (_ranges[ii] > iterations) {
      break;
    }

  }

  --range;

  assert(range > -1);
  assert(range < _ranges.size());

  return range;
}

void FractalCreator::calculateRangeTotals() {
  int range_index = 0;

  for (int ii = 0; ii < Mandelbrot::MaxIterations; ++ii) {
    int pixels = _histogram[ii];

    if (ii >= _ranges[range_index + 1]) {
      ++range_index;
    }

    _range_totals[range_index] += pixels;
  }
}

bool FractalCreator::writeBitmap(const std::string& file_name_) {
  if (!_bitmap.write(file_name_)) {
    return false;
  }
  return true;
}

}  // namespace BM