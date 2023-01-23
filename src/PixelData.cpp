#include "PixelData.h"

PixelData::PixelData() {
  resize(4, 4);
  fill(ColorRGBA_Aqua);
  loadTexture();
}

PixelData::~PixelData() { unloadTexture(); }

void PixelData::resize(std::size_t w, std::size_t h) {
  _width = w;
  _height = h;
  _blob.resize(_width * _height * ColorRGBA_N, 0);
  _blob.shrink_to_fit();
}

void PixelData::loadTexture() {
  unloadTexture();
  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, _blob.data());
}

void PixelData::unloadTexture() {
  if (_id) {
    glDeleteTextures(1, &_id);
    _id = {};
  }
}

void PixelData::fill(const ColorRGBA &rgba) {
  for (std::size_t i = 0; i != _blob.size(); i = i + ColorRGBA_N) {
    _blob[i] = rgba[0];
    _blob[i + 1] = rgba[1];
    _blob[i + 2] = rgba[2];
    _blob[i + 3] = rgba[3];
  }
}

void PixelData::fill(const std::vector<std::size_t> &indexes,
                     const ColorRGBA &rgba) {
  std::size_t i{};
  for (const auto &ind : indexes) {
    i = ind * ColorRGBA_N;
    _blob[i] = rgba[0];
    _blob[i + 1] = rgba[1];
    _blob[i + 2] = rgba[2];
    _blob[i + 3] = rgba[3];
  }
}
