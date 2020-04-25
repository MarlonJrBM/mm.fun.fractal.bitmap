#include "FractalCreator.hh"

#include <iostream>

#include "Bitmap.hh"

namespace BM {

FractalCreator::FractalCreator(Bitmap& bitmap_) : _bitmap(bitmap_) {}
FractalCreator::~FractalCreator() {}

void FractalCreator::calculateIteration() {}
void FractalCreator::drawFractal() {}
void FractalCreator::addZoom() {}
int FractalCreator::writeBitmap(const std::string& file_name_) {
  if (!_bitmap.write(file_name_)) {
    return 1;
  }
  return 0;
}

}  // namespace BM