#pragma once

namespace BM {
struct RGB {
  double red{0.0};
  double green{0.0};
  double blue{0.0};
};

inline RGB operator-(const RGB& this_, const RGB& that_) {
  return RGB { this_.red - that_.red, this_.green - that_.green, this_.blue - that_.blue };
}
}  // namespace BM