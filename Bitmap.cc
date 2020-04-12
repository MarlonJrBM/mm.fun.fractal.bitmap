#include "Bitmap.hh"

#include <iostream>

namespace BM {
Bitmap::Bitmap(int width_, int height_)
    : _width(width_),
      _height(height_),
      _pixels(std::make_unique<std::byte[]>(width_ * height_ * ColorCount)) {
  std::cout << "Printing default-intialized pixels:" << std::endl;
  for (size_t ii = 0; ii < width_ * height_ * ColorCount; ++ii) {
    std::cout << std::to_integer<uint64_t>(_pixels[ii]) << std::endl;
  }
}
Bitmap::~Bitmap() {}

void Bitmap::setPixel(int x_, int y_, std::byte red_, std::byte green_, std::byte blue_) { return; }

bool Bitmap::write(const std::string& filename_) {
  BitmapFileHeader file_header;
  BitmapInfoHeader info_header;

  file_header.file_size =
      sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + _width * _height * ColorCount;
  file_header.data_offset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

  info_header.width = _width;
  info_header.height = _height;


  return false;
}

}  // namespace BM