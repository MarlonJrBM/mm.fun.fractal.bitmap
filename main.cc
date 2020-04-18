#include <iostream>

#include "Bitmap.hh"

constexpr size_t Width = 800;
constexpr size_t Height = 600;
constexpr double Initial_Min = 999999;
constexpr double Initial_Max = -999999;

int main() {
  BM::Bitmap bitmap(Width, Height);

  double min = Initial_Min;
  double max = Initial_Max;

  for (size_t ii = 0; ii < Height; ++ii) {
    for (size_t jj = 0; jj < Width; ++jj) {
      bitmap.setPixel(ii, jj, 255, 0, 0); // sets everything to red
      double x_fractal{(jj - Width / 2.) * 2. / Width};
      double y_fractal{(ii - Height / 2.) * 2. / Height};

      if (x_fractal < min) min = x_fractal;
      if (x_fractal > max) max = x_fractal;
    }
  }

  if (!bitmap.write("test.bmp")) {
    std::cout << "Something went wrong when creating file" << std::endl;
    return 1;
  }

  std::cout << min << ", " << max << std::endl;

  return 0;
}
