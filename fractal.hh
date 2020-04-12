#pragma once

#include <cstdint>


namespace BM {

#pragma pack(2)
struct BitmapFileHeader {
  char header[2]{'B', 'W'};
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
  int16_t bits_per_pixel{24}; //3 bytes, 1 byte per color(?)
  int32_t compression{0};
  int32_t data_size{0};
  int32_t horizontal_resolution{2400};
  int32_t vertical_resolution{2400};
  int32_t colors{0};
  int32_t importantColors{0};
};

}