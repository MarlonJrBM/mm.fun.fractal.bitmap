#include "Bitmap.hh"

#include <fstream>
#include <iostream>

namespace BM {
Bitmap::Bitmap(int width_, int height_)
    : _width(width_),
      _height(height_),
      _pixels(std::make_unique<uint8_t[]>(width_ * height_ * ColorCount)) {}
Bitmap::~Bitmap() {}

void Bitmap::setPixel(int x_, int y_, uint8_t red_, uint8_t green_, uint8_t blue_) {
  uint8_t* pixel = _pixels.get();

  pixel += (_width * x_ * 3) + (y_ * 3);

  pixel[0] = blue_;
  pixel[1] = green_;
  pixel[2] = red_;

  return;
}

bool Bitmap::write(const std::string& filename_) {
  BitmapFileHeader file_header;
  BitmapInfoHeader info_header;

  file_header.file_size =
      sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (_width * _height * ColorCount);
  file_header.data_offset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

  info_header.width = _width;
  info_header.height = _height;

  std::ofstream file;

  file.open(filename_, std::ios::out | std::ios::binary);
  std::cout << "Creating file " << filename_ << std::endl;
  if (!file) {
    return false;
  }

  file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
  file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));
  file.write(reinterpret_cast<const char*>(_pixels.get()), _width * _height * ColorCount);

  file.close();
  if (!file) {
    return false;
  }

  return true;
}

}  // namespace BM