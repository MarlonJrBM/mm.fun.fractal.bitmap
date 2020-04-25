#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

namespace BM {

#pragma pack(2)
struct BitmapFileHeader {
  char header[2]{'B', 'M'};
  int32_t file_size{0};
  int32_t reserved{0};
  int32_t data_offset{0};
};
#pragma pack()

struct BitmapInfoHeader {
  int32_t header_size{40};
  int32_t width{0};
  int32_t height{0};
  int16_t planes{1};
  int16_t bits_per_pixel{24};  // 3 bytes, 1 byte per color(?)
  int32_t compression{0};
  int32_t data_size{0};
  int32_t horizontal_resolution{2400};
  int32_t vertical_resolution{2400};
  int32_t colors{0};
  int32_t importantColors{0};
};

static_assert(sizeof(BitmapFileHeader) == 14, "BitmapFileHeader struct needs to have 14 bytes");
static_assert(sizeof(BitmapInfoHeader) == 40, "BitmapInfoHeader struct needs to have 40 bytes");

class Bitmap {
 public:
  Bitmap(int width_, int height_);
  virtual ~Bitmap();

  void setPixel(int x_, int y_, uint8_t red_, uint8_t green_, uint8_t blue_);
  bool write(const std::string& filename);

 private:
  int _width{0};
  int _height{0};
  std::unique_ptr<uint8_t[]> _pixels{nullptr};
  static constexpr size_t ColorCount{3};
};



}  // namespace BM