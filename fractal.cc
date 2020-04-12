#include "fractal.hh"

#include <iostream>

int main() {
  BM::BitmapFileHeader bitmap;
  std::cout << "Size of BitmapFileHeader is " << sizeof(BM::BitmapFileHeader) << std::endl;
  std::cout << "Size of BitmapInfoHeader is " << sizeof(BM::BitmapInfoHeader) << std::endl;
  return 0;
}
