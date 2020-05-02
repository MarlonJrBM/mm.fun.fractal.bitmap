#pragma once

#include <Bitmap.hh>
#include <string>
#include <vector>

#include "RGB.hh"
#include "Zoom.hh"

namespace BM {

class FractalCreator {
 public:
  FractalCreator(int width_, int height_);
  ~FractalCreator();

  void drawFractal();
  void addZoom(const BM::Zoom&);
  bool writeBitmap(const std::string& name);
  void addRange(double range_end_, const RGB& rgb_);
  int getRange(int iterations) const;

 private:
  int _width;
  int _height;
  int _total_iterations;
  std::unique_ptr<int[]> _histogram;
  std::unique_ptr<int[]> _fractal;
  BM::Bitmap _bitmap;
  BM::ZoomList _zoom_list;

  std::vector<int> _ranges;
  std::vector<int> _range_totals;
  std::vector<RGB> _colors;

  bool _got_first_range{false};

  void calculateIterations();
  void calculateTotalIterations();

  void calculateRangeTotals();
};
}  // namespace BM