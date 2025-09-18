#pragma once

#include "../../../imgui/backends/imgui_impl_glfw.h"
#include "../../../imgui/backends/imgui_impl_opengl3.h"
#include "../../../imgui/imgui.h"
#include "../../engine/render/loadImage.h"
#include "../../engine/render/shaderManager.h"
#include "../window/window.h"
#include "stb_truetype.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <iostream>
#include <string>
#include <vector>
struct TextAtlas {
  GLuint AtlasID;
  float size;
  float scale;
  int acent, decent, linegap;
  int width, height;
  stbtt_packedchar chars[96];
};
struct textComponenet {
  uint8_t loc_buffer;
  int x, y;
  int r, g, b, a;
  std::string tex;
  textComponenet(int x, int y, int r, int g, int b, int a, std::string tex)
      : x(x), y(y), r(r), g(g), b(b), a(a), tex(tex) {}
};
class Text {
public:
  static Text &getInstance() {
    static Text instance;
    return instance;
  }
  TextAtlas monoFont;
  void Init_text();

  void MakeString(std::string t, float x, float y, std::vector<float> &buffer,
                  std::vector<unsigned int> &bufferind, unsigned int &id_offset,
                  TextAtlas &atlas_text);

  void BuildFrame();
  void flushFrame();

private:
  Text() = default;
};
