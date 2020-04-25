#pragma once

#include <string>

namespace BM {
class Bitmap;

class FractalCreator {
 public:
  FractalCreator(Bitmap&);
  ~FractalCreator();

  void calculateIteration();
  void drawFractal();
  void addZoom();
  int writeBitmap(const std::string& name);

  private:
  BM::Bitmap& _bitmap;
};
}  // namespace BM