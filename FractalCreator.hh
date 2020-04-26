#pragma once

#include <Bitmap.hh>
#include <string>

#include "Zoom.hh"
#include "RGB.hh"

namespace BM {

class FractalCreator {
 public:
  FractalCreator(int width_, int height_);
  ~FractalCreator();

  void drawFractal();
  void addZoom(const BM::Zoom&);
  bool writeBitmap(const std::string& name);

 private:
  int _width;
  int _height;
  std::unique_ptr<int[]> _histogram;
  std::unique_ptr<int[]> _fractal;
  BM::Bitmap _bitmap;
  BM::ZoomList _zoom_list;

  void calculateIterations();
};
}  // namespace BM