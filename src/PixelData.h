#pragma once
#include "ColorRGBA.h"
#include <GL/gl.h>
#include <array>
#include <imgui.h>
#include <vector>

class PixelData {
public:
  // Constructor
  PixelData();

  // Destructor
  ~PixelData();

  // Resize
  void resize(std::size_t w, std::size_t h);

  // Load Texture
  void loadTexture();

  // Unload Texture
  void unloadTexture();

  // Fill
  void fill(const ColorRGBA &rgba = ColorRGBA_Aqua);

  // Fill
  void fill(const std::vector<std::size_t> &indexes,
            const ColorRGBA &rgba = ColorRGBA_Lime);

  inline GLuint glID() const { return _id; }
  inline ImTextureID imID() const { return (ImTextureID)(intptr_t)glID(); }

private:
  std::size_t _width{};
  std::size_t _height{};
  std::vector<uint8_t> _blob;
  GLuint _id{};
};
