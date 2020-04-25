#pragma once

#include <vector>

namespace BM {

struct Zoom {
  int x{0};
  int y{0};
  double scale{0.0};
};

class ZoomList {
 public:
  ZoomList(int width_, int height_);
  void add(const Zoom&);
  std::pair<double, double> doZoom(int x_, int y_);

 private:
  double _x_center{0.0};
  double _y_center{0.0};
  double _scale{1.0};
  int _width{0};
  int _height{0};
  std::vector<Zoom> _zooms;
};
}  // namespace BM