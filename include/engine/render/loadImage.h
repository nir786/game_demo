#pragma once

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
typedef struct {
  GLuint id;
  int width;
  int height;

} Atlas;
struct Sprite {
  float u0, v0;
  float u1, v1;
};
struct Vertex {
  float x, y;
  float u, v;
};
struct QuadIndecies {
  unsigned int u0, u1, u2;
  unsigned int v0, v2, v3;
};
struct QuadVert {
  Vertex p1, p2, p3;
  Vertex p4, p5, p6;
};

class ImageLoader {
public:
  Atlas backround_atlas, player_atlas, player_animation_atlas;
  static ImageLoader &getInstance() {
    static ImageLoader instance;
    return instance;
  }
  void Init_Atlas(Atlas &atlas, const char *); // load from set path
  Sprite GetUVs(int x, int y, int w, int h, int atlasW, int atlasH);
  void MakeQuad(float x, float y, float w, float h, const Sprite &uv,
                std::vector<float> &buffer);
  void MakeQuadIndices(unsigned int id, std::vector<unsigned int> &buffer);

private:
  ImageLoader() = default;
};
