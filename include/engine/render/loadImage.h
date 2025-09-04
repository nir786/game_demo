#pragma once

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
typedef struct {
  GLuint id;
  int width;
  int height;

} Atlas;

class ImageLoader {
public:
  Atlas backround_atlas, player_atlas, player_animation_atlas;
  static ImageLoader &getInstance() {
    static ImageLoader instance;
    return instance;
  }
  void Init_Atlas(Atlas &atlas, const char *); // load from set path

private:
  ImageLoader() = default;
};
