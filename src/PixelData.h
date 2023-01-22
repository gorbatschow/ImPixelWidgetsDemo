#pragma once
#include "ColorRGBA.h"
#include <GL/gl.h>
#include <array>
#include <imgui.h>
#include <vector>

class PixelData {
public:
  // Constructor
  PixelData() {
    resize(4, 4);
    fill(ColorRGBA_Aqua);
    loadTexture();
  }

  // Destructor
  ~PixelData() { unloadTexture(); }

  // Resize
  void resize(std::size_t w, std::size_t h) {
    _width = w;
    _height = h;
    _blob.resize(_width * _height * ColorRGBA_N, 0);
    _blob.shrink_to_fit();
  }

  // Load Texture
  void loadTexture() {
    unloadTexture();
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, _blob.data());
  }

  // Unload Texture
  void unloadTexture() {
    if (_id) {
      glDeleteTextures(1, &_id);
      _id = {};
    }
  }

  // Fill
  void fill(const ColorRGBA &rgba = ColorRGBA_Aqua) {
    for (std::size_t i = 0; i != _blob.size(); i = i + ColorRGBA_N) {
      _blob[i] = rgba[0];
      _blob[i + 1] = rgba[1];
      _blob[i + 2] = rgba[2];
      _blob[i + 3] = rgba[3];
    }
  }

  // Fill
  void fill(const std::vector<std::size_t> &indexes,
            const ColorRGBA &rgba = ColorRGBA_Lime) {
    std::size_t i{};
    for (const auto &ind : indexes) {
      i = ind * ColorRGBA_N;
      _blob[i] = rgba[0];
      _blob[i + 1] = rgba[1];
      _blob[i + 2] = rgba[2];
      _blob[i + 3] = rgba[3];
    }
  }

  inline GLuint glID() const { return _id; }
  inline ImTextureID imID() const { return (ImTextureID)(intptr_t)glID(); }

private:
  std::size_t _width{};
  std::size_t _height{};
  std::vector<uint8_t> _blob;
  GLuint _id{};
};
