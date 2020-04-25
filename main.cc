#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

#include "Bitmap.hh"
#include "FractalCreator.hh"
#include "Mandelbrot.hh"
#include "Zoom.hh"

constexpr size_t Width = 800;
constexpr size_t Height = 600;
constexpr double Initial_Min = 999999;
constexpr double Initial_Max = -999999;

int main() {
  BM::Bitmap bitmap(Width, Height);

  double min = Initial_Min;
  double max = Initial_Max;

  BM::ZoomList zoom_list{Width, Height};

  zoom_list.add(BM::Zoom{Width / 2, Height / 2, 2.0 / Height});
  zoom_list.add(BM::Zoom{500, Height - 102, 0.1});

  std::unique_ptr<int[]> histogram(std::make_unique<int[]>(BM::Mandelbrot::MaxIterations));
  std::unique_ptr<int[]> fractal(std::make_unique<int[]>(Width * Height));

  for (size_t ii = 0; ii < Height; ++ii) {
    for (size_t jj = 0; jj < Width; ++jj) {
      auto [x_fractal, y_fractal] = zoom_list.doZoom(ii, jj);

      int iterations = BM::Mandelbrot::getIterations(x_fractal, y_fractal);
      fractal[(ii * Width) + jj] = iterations;

      if (iterations != BM::Mandelbrot::MaxIterations) {
        ++histogram[iterations];
      }
    }
  }

  int total = 0;
  for (int ii = 0; ii < BM::Mandelbrot::MaxIterations; ++ii) {
    total += histogram[ii];
  }

  for (size_t ii = 0; ii < Height; ++ii) {
    for (size_t jj = 0; jj < Width; ++jj) {
      const int iterations = fractal[(ii * Width) + jj];

      uint8_t red{0};
      uint8_t green{0};
      uint8_t blue{0};
      double hue{0};

      if (iterations != BM::Mandelbrot::MaxIterations) {
        for (int ii = 0; ii < iterations; ++ii) {
          hue += double(histogram[ii]) / total;
        }

        green = pow(255, hue);
      }

      bitmap.setPixel(ii, jj, red, green, blue);
    }
  }

  if (!bitmap.write("test.bmp")) {
    std::cout << "Something went wrong when creating file" << std::endl;
    return 1;
  }

  return 0;
}
