#include "Zoom.hh"

#include <iostream>

namespace BM {
ZoomList::ZoomList(int width_, int height_) : _width(width_), _height(height_) {}

void ZoomList::add(const Zoom& zoom_) {
    _zooms.push_back(zoom_);

    _x_center += (zoom_.x - _width/2)*_scale;
    _y_center += -(zoom_.y - _height/2)*_scale;

    _scale *= zoom_.scale;

}

std::pair<double, double> ZoomList::doZoom(int x_, int y_) {
    double x_fractal = (x_ - _width/2)*_scale + _x_center;
    double y_fractal = (y_ - _height/2)*_scale + _y_center;

    return std::pair<double, double>{x_fractal, y_fractal};
}

}  // namespace BM