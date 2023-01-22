#pragma once
#include <array>
#include <cstdint>

static constexpr auto ColorRGBA_N{4};

using ColorRGBA = const std::array<uint8_t, ColorRGBA_N>;

static constexpr ColorRGBA ColorRGBA_Aqua{0, 255, 255, 255};
static constexpr ColorRGBA ColorRGBA_Lime{0, 255, 0, 255};
