#include "../../../include/engine/render/textManeger.h"
#include <cstdint>
#include <fstream>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <ios>
#include <vector>
#define STB_TRUETYPE_IMPLEMENTATION
#include "../../../include/engine/render/stb_truetype.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

vector<unsigned char> Load_TTF(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    std::cerr << "failed to open file \n" << path << std::endl;
  }
  size_t size = file.tellg();
  std::vector<unsigned char> FontBuffer(size);
  file.seekg(0);

  if (!file.read(reinterpret_cast<char *>(FontBuffer.data()), size)) {
    std::cerr << "failed to read font \n" << std::endl;
  }
  return FontBuffer;
}

void Load_stb_text(TextAtlas &tex, const std::string &path) {
  std::vector<unsigned char> FontBuffer = Load_TTF(path);
  stbtt_fontinfo font;
  if (!stbtt_InitFont(&font, FontBuffer.data(),
                      stbtt_GetFontOffsetForIndex(FontBuffer.data(), 0))) {
    std::cerr << "failed to initialize stb_truetype font" << std::endl;
  }
  tex.size = 64.0f;
  tex.scale = stbtt_ScaleForPixelHeight(&font, tex.size);

  stbtt_GetFontVMetrics(&font, &tex.acent, &tex.decent, &tex.linegap);
  tex.width = 512;
  tex.height = 512;

  std::vector<unsigned char> atlas(tex.width * tex.height);
  stbtt_pack_context pc;
  stbtt_PackBegin(&pc, atlas.data(), tex.width, tex.height, 0, 1, nullptr);
  stbtt_PackFontRange(&pc, FontBuffer.data(), 0, tex.size, 32, 95, tex.chars);
  stbtt_PackEnd(&pc);

  glGenTextures(1, &tex.AtlasID);
  glBindTexture(GL_TEXTURE_2D, tex.AtlasID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, tex.width, tex.height, 0, GL_RED,
               GL_UNSIGNED_BYTE, atlas.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Text::Init_text() {
  Load_stb_text(monoFont, "/usr/share/fonts/TTF/DejaVuSansMono-Bold.ttf");
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text::MakeString(std::string t, float x, float y,
                      std::vector<float> &buffer,
                      std::vector<unsigned int> &bufferind,
                      unsigned int &id_offset, TextAtlas &at) {

  for (auto &ch : t) {
    stbtt_aligned_quad q;
    stbtt_GetPackedQuad(at.chars, at.width, at.height, ch - 32, &x, &y, &q, 1);

    buffer.push_back(q.x0);
    buffer.push_back(q.y0);
    buffer.push_back(q.s0);
    buffer.push_back(q.t0);

    buffer.push_back(q.x1);
    buffer.push_back(q.y0);
    buffer.push_back(q.s1);
    buffer.push_back(q.t0);

    buffer.push_back(q.x1);
    buffer.push_back(q.y1);
    buffer.push_back(q.s1);
    buffer.push_back(q.t1);

    buffer.push_back(q.x0);
    buffer.push_back(q.y1);
    buffer.push_back(q.s0);
    buffer.push_back(q.t1);
    bufferind.push_back(id_offset);
    bufferind.push_back(id_offset + 1);
    bufferind.push_back(id_offset + 2);
    bufferind.push_back(id_offset + 2);
    bufferind.push_back(id_offset + 3);
    bufferind.push_back(id_offset);
    id_offset += 4;
    x = x + 64.0f;
  }
}

void Text::BuildFrame() {}
void Text::flushFrame() {}
