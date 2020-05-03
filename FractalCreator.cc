#include "FractalCreator.hh"

#include <cassert>
#include <iostream>

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
  for (int ii = 0; ii < _height; ++ii) {
    for (int jj = 0; jj < _width; ++jj) {
      const int iterations = _fractal[(ii * _width) + jj];

      int range = getRange(iterations);
      int range_total = _range_totals[range];
      int range_start = _ranges[range];

      const RGB& start_color = _colors[range];
      const RGB& end_color = _colors[range + 1];
      RGB color_diff = end_color - start_color;

      uint8_t red{0};
      uint8_t green{0};
      uint8_t blue{0};

      if (iterations != BM::Mandelbrot::MaxIterations) {

        int total_pixels = 0;

        for (int ii = range_start; ii < iterations; ++ii) {
          total_pixels += _histogram[ii];
        }

        red = start_color.red + color_diff.red * double(total_pixels)/range_total;
        green = start_color.green + color_diff.green * double(total_pixels)/range_total;
        blue = start_color.blue + color_diff.blue * double(total_pixels)/range_total;
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

  for (size_t ii = 1; ii < _ranges.size(); ++ii) {
    range = ii;

    if (_ranges[ii] > iterations) {
      break;
    }
  }

  --range;

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